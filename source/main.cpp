#include <3ds.h>
#include <stdio.h>

void shutdown3DS()
{
	Handle ptmSysmHandle = 0;
	Result result = srvGetServiceHandle(&ptmSysmHandle, "ptm:sysm");
	if (result != 0)
		return;

	u32 *commandBuffer = getThreadCommandBuffer();
	commandBuffer[0] = 0x040700C0; //ptm:sysm::ShutdownAsync
	commandBuffer[1] = 0;
	commandBuffer[2] = 0;
	commandBuffer[3] = 0;

	svcSendSyncRequest(ptmSysmHandle);
	svcCloseHandle(ptmSysmHandle);
}

int main(int argc, char **argv) {
	hidScanInput();
	
	// If any key is pressed, cancel the shutdown.
	if (hidKeysDown() != 0)
		goto done;

	shutdown3DS();

done:
	// Hack: the 3ds crashes ("An error has occcurred.") for some reason
	// without one iteration of the main loop.
	aptMainLoop();
	return 0;
}
