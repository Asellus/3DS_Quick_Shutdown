#include <3ds.h>
#include <stdio.h>

// http://3dbrew.org/wiki/NSS:ShutdownAsync
void NSS_ShutdownAsync(void)
{
	Handle nssHandle = 0;
	Result result = srvGetServiceHandle(&nssHandle, "ns:s");
	if (result != 0)
		return;

	u32 *commandBuffer = getThreadCommandBuffer();
	commandBuffer[0] = 0x000E0000;

	svcSendSyncRequest(nssHandle);
	svcCloseHandle(nssHandle);
}

int main(int argc, char **argv) 
{
	NSS_ShutdownAsync();

	// Hack: the 3ds crashes ("An error has occcurred.") for some reason
	// without one iteration of the APT main loop.
	aptMainLoop();
	return 0;
}
