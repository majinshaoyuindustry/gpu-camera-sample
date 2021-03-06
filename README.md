# gpu-camera-sample
Camera sample application with realtime GPU image processing

<p><a target="_blank" href="https://www.fastcompression.com/blog/gpu-software-machine-vision-cameras.htm">
<img src="https://www.fastcompression.com/img/blog/machine-vision/gpu-software-machine-vision-cameras.png" alt="gpu software machine vision genicam" style="max-width:100%"/></a></p>

That software is based on the following image processing pipeline for camera applications that includes:
* Raw image capture (8-bit, 12-bit packed/unpacked, 16-bit)
* Import to GPU
* Raw data convert and unpack
* Linearization curve
* Bad Pixel Correction 
* Dark frame subtraction 
* Flat-Field Correction
* White Balance
* Exposure Correction (brightness control)
* Debayer with HQLI (5&times;5 window), DFPD (11&times;11), MG (23&times;23) algorithms
* Wavelet-based denoiser
* Gamma (linear, sRGB)
* JPEG / MJPEG encoding
* Output to monitor
* Export from GPU to CPU memory
* Storage of compressed data to SSD or streaming via FFmpeg RTSP

Processing is done on NVIDIA GPU to speedup the performance. The software could also work with raw images in PGM format and you can utilize these images for testing or if you don't have a camera or if your camera is not supported. More info about that project you can find <a href="https://www.fastcompression.com/blog/gpu-software-machine-vision-cameras.htm" target="_blank">here</a>.

From the benchmarks on <strong>NVIDIA GeForce RTX 2080ti</strong> we can see that GPU-based raw image processing is very fast and it could offer high image quality at the same time. The total performance could reach <strong>4 GPix/s</strong> for color cameras. The performance strongly depends on complexity of the pipeline. Multiple GPU solutions could significanly improve the performance.

Currently the software is working with <a href="https://www.ximea.com" target="_blank">XIMEA</a> cameras via XIMEA SDK. Via GenICam the software can work with <a href="https://www.ximea.com" target="_blank">XIMEA</a>, <a href="https://www.baslerweb.com" target="_blank">Basler</a>, <a href="https://www.jai.com" target="_blank">JAI</a>, <a href="https://dahengimaging.com/" target="_blank">Daheng Imaging</a> cameras. Soon we are going to add support for <a href="https://www.imperx.com" target="_blank">Imperx</a>, Baumer and FLIR cameras. You can add support for desired cameras by yourself. The software is working with demo version of Fastvideo SDK, that is why you can see a watermark on the screen. To get a Fastvideo SDK license for develoment and for deployment, please contact <a href="https://www.fastcompression.com/" target="_blank">Fastvideo company</a>.

## How to build gpu-camera-sample

### Requirements for Windows

* Camera SDK or GenICam package + camera vendor GenTL producer (.cti). Сurrently XIMEA, Basler, JAI, Daheng Imaging cameras are supported
* Fastvideo SDK (demo) ver.0.15.0.0
* NVIDIA CUDA-10.1
* Qt ver.5.13.1
* Compiler MSVC 2017

### Requirements for Linux

* Ubuntu 18.04 (x64 or Arm64)
* Camera SDK or GenICam package + camera vendor GenTL producer (.cti). Currently XIMEA, Basler, JAI, Daheng Imaging cameras are supported
* Fastvideo SDK (demo) ver.0.15.0.0
* NVIDIA CUDA-10.1 for x64 platform
* NVIDIA CUDA-10.0 for ARM64 platform
* Qt 5 (qtbase5-dev)
``` console
sudo apt-get install qtbase5-dev qtbase5-dev-tools qtcreator
```
* Compiler gcc 7.4
* FFmpeg libraries
``` console 
sudo apt-get install  libavutil-dev libavcodec-dev libavdevice-dev libavfilter-dev libavformat-dev libavresample-dev
```


### Build instructions

* Obtain source code: 
``` console
git clone https://github.com/fastvideo/gpu-camera-sample.git 
```

For Windows users

* Create OtherLibs folder in the project root folder. This folder will contains external libraries, used in gpu-camera-sample application.
* Download Fastvideo SDK from <a href="https://drive.google.com/open?id=1p21TXXC7SCw5PdDVEhayRdMQEN6X11ge">Fastvideo SDK (demo) for Windows-7/10, 64-bit</a> (valid till March 23, 2020), unpack it into \<Project root\>\OtherLibs\fastvideoSDK folder.
* If you need direct XIMEA camera support, download XiAPI from https://www.ximea.com/support/documents/4. Install downloaded package (by default into C:\XIMEA). Copy API folder from XIAPI installation folder into \<Project root\>\OtherLibs folder.
* If you need GenICam support
   * Download GenICamTM Package Version 2019.11 (https://www.emva.org/wp-content/uploads/GenICam_Package_2019.11.zip).
   * Unpack it to a temporary folder and cd to Reference Implementation folder.
   * Create \<Project root\>\OtherLibs\GenICam folder.
   * Unpack GenICam_V3_2_0-Win64_x64_VC141-Release-SDK.zip into \<Project root\>\OtherLibs\GenICam folder.
   * Unpack GenICam_V3_2_0-Win64_x64_VC141-Release-Runtime.zip into \<Project root\>\OtherLibs\GenICam\library\CPP
* Open src\GPUCameraSample.pro in Qt Creator.
* By default the application will be built with no camera support. The only option is camera simulator which is working with PGM files. To enable XIMEA camera support, open common_defs.pri and uncomment line DEFINES += SUPPORT_XIMEA.
* Build the project.
* Binaries will be placed into \<Project root\>\GPUCameraSample_x64 folder.

For Linux users

* Create OtherLibsLinux folder in the project root folder. This folder will contains external libraries, used in gpu-camera-sample application.
* Download Fastvideo SDK x64 platform from <a href="https://drive.google.com/open?id=1GNcQtGmz-FBrKqrsSnMENMCbg44xxWQn">Fastvideo SDK (demo) for Linux Ubuntu 18.04, 64-bit</a> (valid till March 23, 2020), or Fastvideo SDK Arm64 platform from <a href="https://drive.google.com/file/d/1gBfPkazCiHLHc4piPHSJA2_Rm52CnoKD/view?usp=sharing">Fastvideo SDK (demo) for NVIDIA Jetson Nano, TX2, Xavier</a> unpack it into \<Project root\>\OtherLibsLinux\fastvideoSDK folder. Copy all files from \<Project root\>/OtherLibsLinux/fastvideoSDK/fastvideo_sdk/lib to \<Project root\>/OtherLibsLinux/fastvideoSDK/fastvideo_sdk/lib/x64 for x64 platform and to \<Project root\>/OtherLibsLinux/fastvideoSDK/fastvideo_sdk/lib/Arm64 for Arm64 platform. CD to created folder and run
``` console
ldconfig -n .
link libfastvideo_denoise.so.2 libfastvideo_denoise.so
link libfastvideo_sdk.so.18 libfastvideo_sdk.so
```
This will create required for application build symbolic links.
* If you need direct XIMEA camera support, download XiAPI from https://www.ximea.com/support/documents/4. Unpack and install downloaded package .
* If you need GenICam support
   * Download GenICamTM Package Version 2019.11 (https://www.emva.org/wp-content/uploads/GenICam_Package_2019.11.zip).
   * Unpack it to a temporary folder and cd to Reference Implementation folder.
   * Create \<Project root\>\OtherLibsLinux\GenICam folder.
   * Unpack GenICam_V3_2_0-Linux64_x64_gcc48-Runtime.tgz or GenICam_V3_2_0-Linux64_ARM_gcc49-Runtime.tgz into \<Project root\>\OtherLibsLinux\GenICam folder.
   * Unpack GenICam_V3_2_0-Linux64_x64_gcc48-SDK.tgz or GenICam_V3_2_0-Linux64_ARM_gcc49-SDK.tgz into \<Project root\>\OtherLibsLinux\GenICam\library\CPP
* Open src\GPUCameraSample.pro in Qt Creator.
* By default the application will be built with no camera support. The only option is camera simulator which is working with PGM files. To enable XIMEA camera support, open common_defs.pri and uncomment line DEFINES += SUPPORT_XIMEA.
* Build the project.
* Binaries will be placed into \<Project root\>\GPUCameraSample_Arm64 or GPUCameraSample_Linux64 folder. To run application from terminal run from application executable folder:
``` console
ldconfig -n .
export LD_LIBRARY_PATH=`pwd`
./GPUCameraSample
```


## Software architecture

gpu-camera-sample is a multithreaded application. It consists of the following threads:

* Main application thread to control app GUI and other threads.
* Image acquisition from a camera thread which controls camera data acquisition and CUDA-based image processing thread.
* CUDA-based image processing thread. Controls RAW data processing, async data writing thread, and OpenGL renderer thread.
* OpenGL rendering thread. Renders processed data into OpenGL surface.
* Async data writing thread. Writes processed JPEG/MJPEG data to SSD or streams processed video.

Here we've implemented the simplest approach for camera application. Camera driver is writing raw data to memory ring buffer, then we copy data from that ring buffer to GPU for computations. Full image processing pipeline is done on GPU, so we need just to collect processed frames at the output.

In general case, Fastvideo SDK can import/export data from/to SSD / CPU memory / GPU memory. This is done to ensure compatibility with third-party libraries on CPU and GPU. You can get more info at <a href="https://www.fastcompression.com/download/Fastvideo_SDK_manual.pdf" target="_blank">Fastvideo SDK Manual</a>.

## Using gpu-camera-sample

* Run GPUCameraSample.exe
* Press Open button on the toolbar. This will open the first camera in the system or ask to open PGM file (bayer or grayscale) if application was built with no camera support.
* Press Play button. This will start data acquisition from the camera and display it on the screen.
* Adjust zoom with Zoom slider or toggle Fit check box if requires.
* Select appropriate output format in the Recording pane (please check that output folder exists in the file system, otherwise nothing will be recorded) and press Record button to start recording to disk.
* Press Record button again to stop the recording.

## Minimum Hardware ans Software Requirements for desktop application

* Windows-7/10, Ubuntu 18.04 64-bit
* The latest NVIDIA driver
* NVIDIA GPU with Kepler architecture, 6xx series minimum
* NVIDIA GPU with 4-8 GB memory or better
* Intel Core i5 or better
* NVIDIA CUDA-10.1
* Compiler MSVC 2017 (MSVC 2015 is not compatible with CUDA-10.1) for Windows or gcc 7.4.0 for Linux

We also recommend to check PCI-Express bandwidth for Host-to-Device and Device-to-Host transfers. For GPU with Gen3 x16 it should be in the range of 10-12 GB/s. GPU memory size could be a bottleneck for image processing from high resolution cameras, so please check GPU memory usage in the software.

If you are working with images which reside on HDD, please place them on SSD or M2.

For testing purposes you can utilize the latest NVIDIA GeForce RTX 2060, 2070, 2080ti.

For continuous high performance applications we recommend professional NVIDIA Quadro and Tesla GPUs.

## Roadmap

* GPU pipeline for monochrome cameras - done
* GenICam Standard support - done
* Linux version - done
* Software for NVIDIA Jetson hardware and L4T for CUDA-10.0 (Jetson Nano, TX2, Xavier) - done
* Glass-to-Glass (G2G) test for latency measurements - done
* Support for XIMEA, Basler, JAI, Daheng Imaging cameras - done
* MJPEG streaming via FFmpeg RTSP - in progress
* Support for Imperx, Baumer, FLIR cameras
* LCP support (undistortion)
* DCP support
* H.264/H.265 encoders (NVIDIA NVENC)
* JPEG2000 encoder (Fastvideo J2K on GPU)
* Curves and Levels via 1D LUT
* Color correction with 3&times;3 matrix
* Support of other color spaces
* Transforms to Rec.601 (SD), Rec.709 (HD), Rec.2020 (4K)
* 3D LUT for HSV and RGB
* Interoperability with external FFmpeg and GStreamer

## Info

* <a href="https://www.fastcompression.com/products/sdk.htm" target="_blank">Fastvideo SDK for Image & Video Processing on GPU</a>
* <a href="https://www.fastcinemadng.com/" target="_blank">Full description of image processing pipeline on GPU for digital cinema applications</a>

## Fastvideo SDK Benchmarks

* <a href="https://www.fastcompression.com/pub/2019/Fastvideo_SDK_benchmarks.pdf" target="_blank">Fastvideo SDK Benchmarks 2019</a>
* <a href="https://www.fastcompression.com/blog/jetson-benchmark-comparison.htm" target="_blank">Jetson Benchmark Comparison for Image Processing: Nano vs TX1 vs TX2 vs Xavier</a>

## Downloads

* Download <a href="https://www.fastcinemadng.com/download/download.html" target="_blank">Fast CinemaDNG Processor</a> software for Windows, manual and test DNG footages
* Download <a href="https://drive.google.com/open?id=1p21TXXC7SCw5PdDVEhayRdMQEN6X11ge">Fastvideo SDK (demo) for Windows-7/10, 64-bit</a> (valid till March 23, 2020)
* Download <a href="https://drive.google.com/open?id=1GNcQtGmz-FBrKqrsSnMENMCbg44xxWQn">Fastvideo SDK (demo) for Linux Ubuntu 18.04, 64-bit</a> (valid till March 23, 2020)
* Download <a href="https://drive.google.com/file/d/1gBfPkazCiHLHc4piPHSJA2_Rm52CnoKD/view?usp=sharing">Fastvideo SDK (demo) for NVIDIA Jetson Nano, TX2, Xavier</a> (valid till April 12, 2020)
* Download <a href="https://www.fastcompression.com/download/Fastvideo_SDK_manual.pdf" target="_blank">Fastvideo SDK Manual</a>
