#include <stdlib.h>
#include <LIBETC.H>
#include "joypad.h"
#include "display.h"
#include "camera.h"
#include "globals.h"
#include "utils.h"
#include "object.h"
#include "texture.h"
#include <stdlib.h>

Camera camera;

Object *ships;
Object *ship;

u_short shipindex = 0;

Object *sceneobjs;
Object *sceneobj;

u_short objectcount;

u_short angle;

int holdingright = 0;
int holdingleft = 0;

void Setup(void)
{
    u_short shipstarttexture;
    u_short scenestarttexture;

    ScreenInit();

    CdInit();

    JoyPadInit();

    ResetNextPrim(GetCurrBuff());

    shipstarttexture = GetTextureCount();
    LoadObjectCMP("\\ALLSH.CMP;1");

    scenestarttexture = GetTextureCount();
    LoadObjectCMP("\\TRACK02\\SCENE.CMP;1");

    ships = LoadObjectPRM("\\ALLSH.PRM;1", shipstarttexture);

    sceneobjs = LoadObjectPRM("\\TRACK02\\SCENE.PRM;1", scenestarttexture);

    ship = GetObjectByIndex(ships, shipindex);

    setVector(&ship->position, 32599, -347, -45310);

    setVector(&camera.position, ship->position.vx, ship->position.vy - 100, ship->position.vz - 1000);
    camera.lookat = (MATRIX){0};
}

void Update(void)
{
    u_short i;

    EmptyOT(GetCurrBuff());

    JoyPadUpdate();

    if (JoyPadCheck(PAD1_LEFT))
    {
        camera.position.vx -= 100;
    }

    if (JoyPadCheck(PAD1_RIGHT))
    {
        camera.position.vx += 100;
    }

    if (JoyPadCheck(PAD1_UP))
    {
        camera.position.vz += 100;
    }

    if (JoyPadCheck(PAD1_DOWN))
    {
        camera.position.vz -= 100;
    }

    LookAt(&camera, &camera.position, &ship->position, &(VECTOR){0, -ONE, 0});

    RenderSceneObjects(sceneobjs, &camera);

    RenderObject(ship, &camera);
}

void Render(void)
{
    DisplayFrame();
}

int main(void)
{
    Setup();

    while (1)
    {
        Update();
        Render();
    }

    return 0;
}
