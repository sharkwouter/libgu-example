#include <pspkernel.h>
#include <pspgu.h>

PSP_MODULE_INFO("gutest", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU | THREAD_ATTR_USER);

int main() {
    sceGuInit();
}
