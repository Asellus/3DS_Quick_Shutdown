#include <3ds.h>
#include <stdio.h>

void shutdown3DS()
{
	Handle ptmSysmHandle = 0;
	Result result = srvGetServiceHandle(&ptmSysmHandle, "ns:s");
	if (result != 0)
		return;

	// http://3dbrew.org/wiki/NSS:ShutdownAsync

	u32 *commandBuffer = getThreadCommandBuffer();
	commandBuffer[0] = 0x000E0000;

	svcSendSyncRequest(ptmSysmHandle);
	svcCloseHandle(ptmSysmHandle);
}

int main(int argc, char **argv) {
	hidScanInput();
	
#ifndef ALWAYS_SHUTDOWN
	// If any key is pressed, cancel the shutdown.
	if (hidKeysDown() != 0)
		goto done;
#endif
	shutdown3DS();

done:
	// Hack: the 3ds crashes ("An error has occcurred.") for some reason
	// without one iteration of the main loop.
	aptMainLoop();
	return 0;
}
