#include <pspkernel.h>
#include <pspgu.h>

PSP_MODULE_INFO("gutest", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU | THREAD_ATTR_USER);

#define BUFFER_WIDTH 512
#define BUFFER_HEIGHT 272
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT BUFFER_HEIGHT

char list[0x20000] __attribute__((aligned(64)));

void initGu(){
    sceGuInit();

    //Set up buffers
	sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUFFER_WIDTH);
	sceGuDispBuffer(SCREEN_WIDTH,SCREEN_HEIGHT,(void*)0x88000,BUFFER_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUFFER_WIDTH);

    //Set up viewport
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Set some stuff
    sceGuDepthRange(65535, 0); //Use the full buffer for depth testing - buffer is reversed order

    sceGuDepthFunc(GU_GEQUAL); //Depth buffer is reversed, so GEQUAL instead of LEQUAL
    sceGuEnable(GU_DEPTH_TEST); //Enable depth testing

    //sceGuEnable(GU_TEXTURE_2D); //Enable Textures
    //sceGuEnable(GU_CLIP_PLANES); //Enable Clipping Planes (reduces geometry)

    //sceGuEnable(GU_CULL_FACE); //Culls the back side of faces
    //sceGuFrontFace(GU_CCW); //Set our winding order

    //sceGuEnable(GU_BLEND); //Blending enabled - allows transparency
    //sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0); //If transparency is zero, we don't draw.
    //sceGuAlphaFunc(GU_GREATER, 0.0f, 0xff); //Test from greater to lesser for transparency and which is on top

    //sceGuStencilFunc(GU_ALWAYS, 1, 1); // always set 1 bit in 1 bit mask
    //sceGuStencilOp(GU_KEEP, GU_KEEP, GU_REPLACE); // keep value on failed test (fail and zfail) and replace on pass

    //sceGuTexFilter(GU_LINEAR, GU_LINEAR); //Default texture filter.

    sceGuFinish();
	//sceGuSync(0,0);
	sceGuDisplay(GU_TRUE);
}

void endGu(){
    sceGuDisplay(GU_FALSE);
	sceGuTerm();
}

void startFrame(){
    sceGuStart(GU_DIRECT, list);
}

void endFrame(){
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}

typedef struct {
    unsigned short u, v;
    unsigned short color;
    short x,y,z;
} Vertex;

void drawSquare(int x, int y, int w, int h) {

    Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

    unsigned short color = 0xFFFF00FF;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].color = color;
    vertices[1].x = x + w;
    vertices[1].y = y + h;
    vertices[1].color = color;

    //sceGuColor(0xFFFFFFFF);
    sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
}


int main() {
    initGu();
    int running = 1;
    while(running){
        startFrame();

        sceGuClearColor(0xFFFFFFFF);
        sceGuClear(GU_COLOR_BUFFER_BIT);

        drawSquare(32, 32, 64, 64);

        endFrame();
    }

    return 0;
}
