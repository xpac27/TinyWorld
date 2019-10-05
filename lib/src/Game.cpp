#include "Game.hpp"

#include <systems/RenderSystem.hpp>
#include <systems/MovementSystem.hpp>

#include <utils/Random.hpp>
#include <utils/Path.hpp>

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
    Path root(rootPath);

    // TODO move to a loader?
    cubemapStore.insert("stormyday", {
        .right  = root.get("res/textures/environments/stormyday/cubemap/right.png").data(),
        .left   = root.get("res/textures/environments/stormyday/cubemap/left.png").data(),
        .bottom = root.get("res/textures/environments/stormyday/cubemap/bottom.png").data(),
        .top    = root.get("res/textures/environments/stormyday/cubemap/top.png").data(),
        .back   = root.get("res/textures/environments/stormyday/cubemap/back.png").data(),
        .front  = root.get("res/textures/environments/stormyday/cubemap/front.png").data() });
    cubemapStore.insert("stormyday-irradiance-map", {
        .right  = root.get("res/textures/environments/stormyday/irradiance-map/right.png").data(),
        .left   = root.get("res/textures/environments/stormyday/irradiance-map/left.png").data(),
        .bottom = root.get("res/textures/environments/stormyday/irradiance-map/bottom.png").data(),
        .top    = root.get("res/textures/environments/stormyday/irradiance-map/top.png").data(),
        .back   = root.get("res/textures/environments/stormyday/irradiance-map/back.png").data(),
        .front  = root.get("res/textures/environments/stormyday/irradiance-map/front.png").data() });
    cubemapStore.insert("archipelago", {
        .right  = root.get("res/textures/environments/archipelago/cubemap/right.png").data(),
        .left   = root.get("res/textures/environments/archipelago/cubemap/left.png").data(),
        .bottom = root.get("res/textures/environments/archipelago/cubemap/bottom.png").data(),
        .top    = root.get("res/textures/environments/archipelago/cubemap/top.png").data(),
        .back   = root.get("res/textures/environments/archipelago/cubemap/back.png").data(),
        .front  = root.get("res/textures/environments/archipelago/cubemap/front.png").data() });
    cubemapStore.insert("archipelago-irradiance-map", {
        .right  = root.get("res/textures/environments/archipelago/irradiance-map/right.png").data(),
        .left   = root.get("res/textures/environments/archipelago/irradiance-map/left.png").data(),
        .bottom = root.get("res/textures/environments/archipelago/irradiance-map/bottom.png").data(),
        .top    = root.get("res/textures/environments/archipelago/irradiance-map/top.png").data(),
        .back   = root.get("res/textures/environments/archipelago/irradiance-map/back.png").data(),
        .front  = root.get("res/textures/environments/archipelago/irradiance-map/front.png").data() });

    programStore.insert("shadow_volume", {
        .vertexShader   = root.get("res/shaders/shadow_volume.vert").data(),
        .geometryShader = root.get("res/shaders/shadow_volume.geom").data(),
        .fragmentShader = root.get("res/shaders/shadow_volume.frag").data() });
    programStore.insert("shadow_imprint", {
        .vertexShader   = root.get("res/shaders/shadow_imprint.vert").data(),
        .fragmentShader = root.get("res/shaders/shadow_imprint.frag").data() });
    programStore.insert("filling", {
        .vertexShader   = root.get("res/shaders/filling.vert").data(),
        .fragmentShader = root.get("res/shaders/filling.frag").data() });
    programStore.insert("geometry_buffer", {
        .vertexShader   = root.get("res/shaders/geometry_buffer.vert").data(),
        .fragmentShader = root.get("res/shaders/geometry_buffer.frag").data() });
    programStore.insert("deferred_shading", {
        .vertexShader   = root.get("res/shaders/deferred_shading.vert").data(),
        .fragmentShader = root.get("res/shaders/deferred_shading.frag").data() });

    meshStore.insert("twisted_torus", {
        .object          = root.get("res/objects/twisted-torus.obj").data(),
        .diffuseTexture  = root.get("res/textures/surfaces/old_tiles/diffuse.png").data(),
        .metallicTexture = root.get("res/textures/surfaces/old_tiles/metallicness.png").data(),
        .roughTexture    = root.get("res/textures/surfaces/old_tiles/roughness.png").data(),
        .normalTexture   = root.get("res/textures/surfaces/old_tiles/normal.png").data() });
    meshStore.insert("plan", {
        .object          = root.get("res/objects/plan.obj").data(),
        .diffuseTexture  = root.get("res/textures/surfaces/worn_plaster/diffuse.png").data(),
        .metallicTexture = root.get("res/textures/surfaces/worn_plaster/metallicness.png").data(),
        .roughTexture    = root.get("res/textures/surfaces/worn_plaster/roughness.png").data(),
        .normalTexture   = root.get("res/textures/surfaces/worn_plaster/normal.png").data() });

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
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshId = meshStore.getId("plan");
    visibilityComponents.getComponent(entity)->scale = glm::vec3(80, 80, 1);
    movementComponents.getComponent(entity)->direction = glm::vec3(0.f, -1.f, 0.f);
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
    movementComponents.getComponent(entity)->spinSpeed = 0.5f;
}
