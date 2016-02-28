#include "Game.hpp"

#include <systems/RenderSystem.hpp>
#include <systems/MovementSystem.hpp>

#include <utils/Random.hpp>

#include <glm/glm.hpp>

#include <graphic/Cubemap.hpp>
#include <graphic/CubemapParams.hpp>
#include <graphic/Program.hpp>
#include <graphic/ProgramParams.hpp>
#include <graphic/Mesh.hpp>
#include <graphic/MeshParams.hpp>

Game::Game()
    : renderSystem(&visibilityComponents, &movementComponents)
    , movementSystem(&movementComponents)
    , renderer(meshStore, programStore, cubemapStore)
{
}

void Game::load(const char* rootPath)
{
    // TODO move to a loader?
    cubemapStore.insert("stormyday", {
        .right  = "lib/res/textures/environments/stormyday/cubemap/right.png",
        .left   = "lib/res/textures/environments/stormyday/cubemap/left.png",
        .bottom = "lib/res/textures/environments/stormyday/cubemap/bottom.png",
        .top    = "lib/res/textures/environments/stormyday/cubemap/top.png",
        .back   = "lib/res/textures/environments/stormyday/cubemap/back.png",
        .front  = "lib/res/textures/environments/stormyday/cubemap/front.png" });
    cubemapStore.insert("stormyday-irradiance-map", {
        .right  = "lib/res/textures/environments/stormyday/irradiance-map/right.png",
        .left   = "lib/res/textures/environments/stormyday/irradiance-map/left.png",
        .bottom = "lib/res/textures/environments/stormyday/irradiance-map/bottom.png",
        .top    = "lib/res/textures/environments/stormyday/irradiance-map/top.png",
        .back   = "lib/res/textures/environments/stormyday/irradiance-map/back.png",
        .front  = "lib/res/textures/environments/stormyday/irradiance-map/front.png" });
    cubemapStore.insert("archipelago", {
        .right  = "lib/res/textures/environments/archipelago/cubemap/right.png",
        .left   = "lib/res/textures/environments/archipelago/cubemap/left.png",
        .bottom = "lib/res/textures/environments/archipelago/cubemap/bottom.png",
        .top    = "lib/res/textures/environments/archipelago/cubemap/top.png",
        .back   = "lib/res/textures/environments/archipelago/cubemap/back.png",
        .front  = "lib/res/textures/environments/archipelago/cubemap/front.png" });
    cubemapStore.insert("archipelago-irradiance-map", {
        .right  = "lib/res/textures/environments/archipelago/irradiance-map/right.png",
        .left   = "lib/res/textures/environments/archipelago/irradiance-map/left.png",
        .bottom = "lib/res/textures/environments/archipelago/irradiance-map/bottom.png",
        .top    = "lib/res/textures/environments/archipelago/irradiance-map/top.png",
        .back   = "lib/res/textures/environments/archipelago/irradiance-map/back.png",
        .front  = "lib/res/textures/environments/archipelago/irradiance-map/front.png" });

    programStore.insert("shadow_volume", {
        .vertexShader   = "lib/src/shaders/shadow_volume.vert",
        .geometryShader = "lib/src/shaders/shadow_volume.geom",
        .fragmentShader = "lib/src/shaders/shadow_volume.frag" });
    programStore.insert("shadow_imprint", {
        .vertexShader   = "lib/src/shaders/shadow_imprint.vert",
        .fragmentShader = "lib/src/shaders/shadow_imprint.frag" });
    programStore.insert("filling", {
        .vertexShader   = "lib/src/shaders/filling.vert",
        .fragmentShader = "lib/src/shaders/filling.frag" });
    programStore.insert("geometry_buffer", {
        .vertexShader   = "lib/src/shaders/geometry_buffer.vert",
        .fragmentShader = "lib/src/shaders/geometry_buffer.frag" });
    programStore.insert("deferred_shading", {
        .vertexShader   = "lib/src/shaders/deferred_shading.vert",
        .fragmentShader = "lib/src/shaders/deferred_shading.frag" });

    meshStore.insert("twisted_torus", {
        .object          = "lib/res/objects/twisted-torus.obj",
        .diffuseTexture  = "lib/res/textures/surfaces/old_tiles/diffuse.png",
        .metallicTexture = "lib/res/textures/surfaces/old_tiles/metallicness.png",
        .roughTexture    = "lib/res/textures/surfaces/old_tiles/roughness.png",
        .normalTexture   = "lib/res/textures/surfaces/old_tiles/normal.png" });
    meshStore.insert("plan", {
        .object          = "lib/res/objects/plan.obj",
        .diffuseTexture  = "lib/res/textures/surfaces/worn_plaster/diffuse.png",
        .metallicTexture = "lib/res/textures/surfaces/worn_plaster/metallicness.png",
        .roughTexture    = "lib/res/textures/surfaces/worn_plaster/roughness.png",
        .normalTexture   = "lib/res/textures/surfaces/worn_plaster/normal.png" });

    renderer.setup({
        .cubemapId                = cubemapStore.getId("stormyday"),
        .shadowVolumeProgramId    = programStore.getId("shadow_volume"),
        .shadowImprintProgramId   = programStore.getId("shadow_imprint"),
        .fillingProgramId         = programStore.getId("filling"),
        .geometryBufferProgramId  = programStore.getId("geometry_buffer"),
        .deferredShadingProgramId = programStore.getId("deferred_shading")
    });

    setupWorld();
    addEntity();
}

void Game::update(float seconds)
{
    movementSystem.update(seconds - previousUpdateSeconds);
    previousUpdateSeconds = seconds;
}

void Game::draw()
{
    renderSystem.update(renderer);
}

void Game::reload()
{
    // TODO... reload
}

void Game::setupWorld()
{
    ecs::id entity = entities.addEntity();
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshId = meshStore.getId("plan");
    visibilityComponents.getComponent(entity)->scale = glm::vec3(80, 80, 1);
}

void Game::addEntity()
{
    ecs::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshId = meshStore.getId("twisted_torus");
    visibilityComponents.getComponent(entity)->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    movementComponents.getComponent(entity)->direction = glm::vec3(0.f, -1.f, 0.f);
    movementComponents.getComponent(entity)->position.x = 0.0f;
    movementComponents.getComponent(entity)->position.y = -2.0f;
    movementComponents.getComponent(entity)->position.z = 2.0f;
}
