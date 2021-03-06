#include "common.h"

#include <cuda_runtime_api.h>

Image::Image(){

}

Image::Image(int w, int h, Image::TYPE tp){
	if(tp == YUV)
		setYUV(w, h);
	else if(tp == NV12)
		setNV12(w, h);
	else if(tp == RGB)
		setRGB(w, h);
	else if(tp == GRAY)
		setGray(w, h);
	else if(tp == CUDA_RGB){
		setCudaRgb(w, h);
	}else if(tp == CUDA_GRAY){
		setCudaGray(w, h);
	}
}

Image::Image(const Image &o){
	width = o.width;
	height = o.height;
	type = o.type;
	rgb = o.rgb;
	yuv = o.yuv;
}

Image::~Image(){
	releaseCudaRgbBuffer();
}

void Image::setYUV(uint8_t *data[], int linesize[], int w, int h){
	type = YUV;
	width = w;
	height = h;
	size_t size1 = static_cast<size_t>(linesize[0] * h);
	size_t size2 = static_cast<size_t>(linesize[1] * h/2);
	//size_t size3 = static_cast<size_t>(linesize[2] * h/2);
	yuv.resize(size1 + size2 * 2);

	std::copy(data[0], data[0] + size1, yuv.data());
	std::copy(data[1], data[1] + size2, yuv.data() + size1);
	std::copy(data[2], data[2] + size2, yuv.data() + size1 + size2);
}

void Image::setNV12(uint8_t *data[], int linesize[], int w, int h){
	type = NV12;
	width = w;
	height = h;
	size_t size1 = static_cast<size_t>(linesize[0] * h);
	size_t size2 = static_cast<size_t>(linesize[1]/2 * h/2);
	//size_t size3 = static_cast<size_t>(linesize[1]/2 * h/2);
	yuv.resize(size1 + size2 * 2);

	std::copy(data[0], data[0] + size1, yuv.data());
	std::copy(data[1], data[1] + size2 * 2, yuv.data() + size1);
}

bool Image::setCudaRgb(int w, int h){
	if(cudaRgb && w != width && h != height)
		releaseCudaRgbBuffer();
	type = CUDA_RGB;
	width = w;
	height = h;
	size_t sz = w * h * 3;
	cudaSize = sz;
	return cudaMalloc(&cudaRgb, sz) == cudaSuccess;
}

bool Image::setCudaGray(int w, int h)
{
	if(cudaRgb && w != width && h != height)
		releaseCudaRgbBuffer();
	type = CUDA_GRAY;
	width = w;
	height = h;
	size_t sz = w * h;
	cudaSize = sz;
	return cudaMalloc(&cudaRgb, sz) == cudaSuccess;
}

void Image::releaseCudaRgbBuffer(){
	if(cudaRgb){
		cudaFree(cudaRgb);
		cudaRgb = nullptr;
	}
	width = height = 0;
	cudaSize = 0;
}

void Image::setYUV(int w, int h){
	type = YUV;
	width = w;
	height = h;
	yuv.resize(w * h + w/2 * h/2 * 2);
}

void Image::setNV12(int w, int h){
	type = YUV;
	width = w;
	height = h;
	yuv.resize(w * h + w/2 * h/2 * 2);
}

void Image::setRGB(int w, int h){
	type = RGB;
	width = w;
	height = h;
	rgb.resize(w * h * 3);
}

void Image::setGray(int w, int h){
	type = GRAY;
	width = w;
	height = h;
	rgb.resize(w * h);
}

bool Image::empty() const{
	return width == 0 || height == 0;
}
