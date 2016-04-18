#include <3ds.h>

// http://3dbrew.org/wiki/PTM:ShutdownAsync
void PTM_ShutdownAsync(void) {

	Handle ptmSysmHandle = 0;
	Result result = srvGetServiceHandle(&ptmSysmHandle, "ptm:sysm");
	if (result != 0) {
		return;
	}

	u32 *commandBuffer = getThreadCommandBuffer();
	commandBuffer[0] = 0x040700C0;
	commandBuffer[1] = 0x00000000;
	commandBuffer[2] = 0x00000000;
	commandBuffer[3] = 0x00000000;

	svcSendSyncRequest(ptmSysmHandle);
	svcCloseHandle(ptmSysmHandle);
}

int main(int argc, char **argv) {

	// Initialize services
	ptmSysmInit();

	// without one iteration of the APT main loop.
	aptMainLoop();

	// Shutdown 3DS
	PTM_ShutdownAsync();

	// Exit services
	ptmSysmExit();
	return 0;
}
