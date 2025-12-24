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

void Setup(void)
{
    u_short shipstarttexture;

    ScreenInit();

    CdInit();

    JoyPadInit();

    ResetNextPrim(GetCurrBuff());

    setVector(&camera.position, 0, -600, -900);
    camera.lookat = (MATRIX){0};

    shipstarttexture = GetTextureCount();
    LoadObjectCMP("\\ALLSH.CMP;1");
    ships = LoadObjectPRM("\\ALLSH.PRM;1", shipstarttexture);

}

void Update(void)
{
    u_short i;

    EmptyOT(GetCurrBuff());

    JoyPadUpdate();

    if (JoyPadCheck(PAD1_LEFT))
    {
        if (shipindex > 0)
        {
            shipindex--;
        }
    }

    if (JoyPadCheck(PAD1_RIGHT))
    {
        if (shipindex < 7)
        {
            shipindex++;
        }
    }

    ship = ships;

    for (i = 0; i < shipindex; i++)
    {
        ship = ship->next;
    }

    LookAt(&camera, &camera.position, &ship->position, &(VECTOR){0, -ONE, 0});

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
