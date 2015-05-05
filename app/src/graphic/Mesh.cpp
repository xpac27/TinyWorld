#include "Mesh.hpp"
#include "graphic/Material.hpp"
#include "utils/OBJParser.hpp"
#include "helpers/Debug.hpp"
#include <assert.h>
#include <stdio.h>
#include <png.h>

using namespace std;

Mesh::Mesh(const char *filename)
{
    OBJParser(vertexes, uvs, normals, indexes, materials).load(filename);
    totalIndexes = GLsizei(indexes.size());

    loadVAO();
    loadTextures();
}

void Mesh::draw()
{
    if (diffuses.size() > 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuses[0]);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::outline()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_LINE_LOOP, totalIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::loadVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(4, VAB);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[TEX_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * uvs.size(), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VAB[NOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAB[IND_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes[0]) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::loadTextures()
{
    for (auto m : materials) {
        diffuses.push_back(loadTexture(m.map_Kd.data()));
    }
}

GLuint Mesh::loadTexture(const char *filename)
{
    //open file as binary
    string filepath = "app/res/";
    filepath += filename;
    FILE *fp = fopen(filepath.data(), "r");
    assert(fp);

    //read the header
    png_byte header[8];
    fread(header, 1, 8, fp);
    assert(png_sig_cmp(header, 0, 8) == 0);

    //create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_ptr);

    //create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    assert(info_ptr);

    //create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    assert(end_info);

    //variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 width, height;

    png_init_io(png_ptr, fp); //init png reading
    png_set_sig_bytes(png_ptr, 8); //let libpng know you already read the first 8 bytes
    png_read_info(png_ptr, info_ptr); // read all the info up to the image data
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL); // get info about png
    png_read_update_info(png_ptr, info_ptr); // Update the png info struct.
    png_size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr); // Row size in bytes.

    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];
    assert(image_data);

    //row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[height];
    assert(row_pointers);

    // set the individual row_pointers to point at the correct offsets of image_data
    for (unsigned int i = 0; i < height; ++i) row_pointers[height - 1 - i] = image_data + i * rowbytes;

    //read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    //Now generate the OpenGL texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    float color[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    float pixels[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GLint(width), GLint(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    delete[] row_pointers;
    fclose(fp);

    return texture;
}
