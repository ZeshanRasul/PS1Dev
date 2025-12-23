#include <stdlib.h>
#include <LIBETC.H>
#include "joypad.h"
#include "display.h"
#include "camera.h"
#include "globals.h"
#include "utils.h"
#include "object.h"

Camera camera;
Object object;

void Setup(void)
{
    ScreenInit();

    CdInit();

    JoyPadInit();

    ResetNextPrim(GetCurrBuff());

    setVector(&camera.position, 0, -600, -900);
    camera.lookat = (MATRIX){0};

    LoadObjectPRM(&object, "\\ALLSH.PRM;1");
}

void Update(void)
{
    EmptyOT(GetCurrBuff());

    JoyPadUpdate();

    if (JoyPadCheck(PAD1_LEFT))
    {
        object.rotation.vy += 15;
    }

    if (JoyPadCheck(PAD1_RIGHT))
    {
        object.rotation.vy -= 15;
    }

    LookAt(&camera, &camera.position, &object.position, &(VECTOR){0, -ONE, 0});

    RenderObject(&object, &camera);
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
