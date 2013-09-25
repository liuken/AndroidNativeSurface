#define LOG_TAG "Surface"
#include <utils/Log.h>

#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <media/ICrypto.h>
#include <media/IMediaPlayerService.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/AString.h>
#include <media/stagefright/DataSource.h>
#include <media/stagefright/MediaCodec.h>
#include <media/stagefright/MediaCodecList.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/NuMediaExtractor.h>
#include <gui/ISurfaceComposer.h>
#include <gui/SurfaceComposerClient.h>
#include <ui/DisplayInfo.h>

using namespace android;

static sp<SurfaceComposerClient> composerClient;
static sp<SurfaceControl> control;
static sp<Surface> surface;

int main(int argc, char* argv[])
{
	composerClient = new SurfaceComposerClient;
	
	sp<IBinder> display(SurfaceComposerClient::getBuiltInDisplay(ISurfaceComposer::eDisplayIdMain));
        DisplayInfo info;
        SurfaceComposerClient::getDisplayInfo(display, &info);
        ssize_t displayWidth = info.w;
        ssize_t displayHeight = info.h;

        printf("display is %ld x %ld\n", displayWidth, displayHeight);

	control = composerClient->createSurface(
                String8("A Surface"),
                400,
                400,
                PIXEL_FORMAT_RGB_565,
                0);
	
	SurfaceComposerClient::openGlobalTransaction();
        control->setLayer(21015);
	control->setAlpha(0.8);
	control->setMatrix(0.5, 0, 0, 0.5);
        control->show();
        SurfaceComposerClient::closeGlobalTransaction();

        surface = control->getSurface();
	//ANativeWindow *window = surface.get();
	//native_window_set_buffers_geometry(window, 400, 400, HAL_PIXEL_FORMAT_YV12); 

	Surface::SurfaceInfo sinfo;
	surface->lock(&sinfo);
	memset(sinfo.bits, 0xff, sinfo.w*sinfo.h);
	memset(sinfo.bits+sinfo.w*sinfo.h, 0xf, sinfo.w*sinfo.h);
	surface->unlockAndPost();

	sleep(10);

	return 0;
}
