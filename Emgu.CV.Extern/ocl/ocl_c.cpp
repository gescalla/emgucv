//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2013 by EMGU. All rights reserved.
//
//----------------------------------------------------------------------------

#include "ocl_c.h"


int oclGetPlatforms(std::vector<const cv::ocl::PlatformInfo*>* oclInfoVec)
{
   return cv::ocl::getOpenCLPlatforms(*oclInfoVec);
}

int oclGetDevices(std::vector<const cv::ocl::DeviceInfo*>* oclDevices, int deviceType, const cv::ocl::PlatformInfo* platform)
{
   if (oclDevices)
      return cv::ocl::getOpenCLDevices(*oclDevices, deviceType, platform);
   else
   {
      std::vector<const cv::ocl::DeviceInfo*> infos;
      return cv::ocl::getOpenCLDevices(infos, deviceType, platform);
   }
}

void oclSetDevice(const cv::ocl::DeviceInfo* oclInfo)
{
   cv::ocl::setDevice(oclInfo);
}

void oclFinish()
{
   cv::ocl::finish();
}

void oclSetBinaryDiskCache(int mode, const char* path)
{
   cv::ocl::setBinaryDiskCache(mode, path);
}

void oclSetBinaryPath(const char *path)
{
   cv::ocl::setBinaryPath(path);
}

cv::ocl::oclMat* oclMatCreateDefault()
{
   return new cv::ocl::oclMat();
}

cv::ocl::oclMat* oclMatCreate(int rows, int cols, int type)
{
   return new cv::ocl::oclMat(rows, cols, type);
}

/*
cv::ocl::oclMat* oclMatCreateContinuous(int rows, int cols, int type)
{
   cv::ocl::oclMat* result = new cv::ocl::oclMat();
   cv::ocl::createContinuous(rows, cols, type, *result);
   return result;
}*/

cv::ocl::oclMat* oclMatCreateFromArr(CvArr* arr)
{
   cv::Mat mat = cv::cvarrToMat(arr);
   cv::ocl::oclMat* result = new cv::ocl::oclMat();
   result -> upload(mat);
   return result;
}

int oclMatGetType(cv::ocl::oclMat* oclMat)
{
   return oclMat->type();
}

emgu::size oclMatGetSize(cv::ocl::oclMat* oclMat)
{
   emgu::size s;
   s.width = oclMat->cols;
   s.height = oclMat->rows;
   return s;
}

emgu::size oclMatGetWholeSize(cv::ocl::oclMat* oclMat)
{
   emgu::size s;
   s.width = oclMat->wholecols;
   s.height = oclMat->wholerows;
   return s;
}

bool oclMatIsEmpty(cv::ocl::oclMat* oclMat)
{
   return oclMat->empty();
}

bool oclMatIsContinuous(cv::ocl::oclMat* oclMat)
{
   return oclMat->isContinuous();
}

int oclMatGetChannels(cv::ocl::oclMat* oclMat)
{
   return oclMat->channels();
}

void oclMatRelease(cv::ocl::oclMat** mat)
{
   delete *mat;
   *mat = 0;
}

//Pefroms blocking upload data to oclMat.
void oclMatUpload(cv::ocl::oclMat* oclMat, CvArr* arr)
{
   cv::Mat mat = cv::cvarrToMat(arr);
   oclMat->upload(mat);
}

//Downloads data from device to host memory. Blocking calls.
void oclMatDownload(cv::ocl::oclMat* oclMat, CvArr* arr)
{
   cv::Mat mat = cv::cvarrToMat(arr);
   int oldRows = mat.rows;
   int oldCols = mat.cols;
   int oldType = mat.type();
   
   oclMat->download(mat);
   CV_Assert(oldRows == mat.rows);
   //CV_Assert(oldCols == mat.cols);

   //char message[2000];
   //sprintf(message, "oldType = %d; newType = %d", oldType, mat.type());
   //CV_Error(0, message);

   CV_Assert(oldType == mat.type());
}

int oclCountNonZero(cv::ocl::oclMat* oclMat)
{
   return cv::ocl::countNonZero(*oclMat);
}

void oclAdd(const cv::ocl::oclMat* a, const cv::ocl::oclMat* b, cv::ocl::oclMat* c, const cv::ocl::oclMat* mask)
{
   if (mask)
   {
      cv::ocl::add(*a, *b, *c, *mask);
   }
   else
   {
      cv::ocl::add(*a, *b, *c);
   }
}

void oclAddS(const cv::ocl::oclMat* a, const CvScalar scale, cv::ocl::oclMat* c, const cv::ocl::oclMat* mask)
{
   cv::ocl::add(*a, scale, *c, mask? *mask : cv::ocl::oclMat());
}

void oclSubtract(const cv::ocl::oclMat* a, const cv::ocl::oclMat* b, cv::ocl::oclMat* c, const cv::ocl::oclMat* mask)
{
   if (mask)
   {
      cv::ocl::subtract(*a, *b, *c, *mask);
   } else
   {
      cv::ocl::subtract(*a, *b, *c);
   }
}

void oclSubtractS(const cv::ocl::oclMat* a, const CvScalar scale, cv::ocl::oclMat* c, const cv::ocl::oclMat* mask)
{
   cv::ocl::subtract(*a, scale, *c, mask ? *mask : cv::ocl::oclMat());
}

void oclMultiply(const cv::ocl::oclMat* a, const cv::ocl::oclMat* b, cv::ocl::oclMat* c, double scale)
{
   cv::ocl::multiply(*a, b ? *b : cv::ocl::oclMat(), *c, scale);
}

void oclMultiplyS(const cv::ocl::oclMat* a, const double s, cv::ocl::oclMat* c)
{
   cv::ocl::multiply(s, *a, *c);
}

void oclDivide(const cv::ocl::oclMat* a, const cv::ocl::oclMat* b, cv::ocl::oclMat* c, double scale)
{
   cv::ocl::divide(*a, b ? *b : cv::ocl::oclMat(), *c, scale);
}
/*
void oclMatDivideSR(const cv::ocl::oclMat* a, const CvScalar s, cv::ocl::oclMat* c)
{
   cv::ocl::divide(*a, s, *c, 1, c->depth());
}*/

void oclDivideSL(const double s, const cv::ocl::oclMat* b, cv::ocl::oclMat* c)
{
   cv::ocl::divide(s, *b, *c);
}

void oclAddWeighted(const cv::ocl::oclMat* src1, double alpha, const cv::ocl::oclMat* src2, double beta, double gamma, cv::ocl::oclMat* dst)
{
   cv::ocl::addWeighted(*src1, alpha, *src2, beta, gamma, *dst);
}

void oclAbsdiff(const cv::ocl::oclMat* a, const cv::ocl::oclMat* b, cv::ocl::oclMat* c)
{
   cv::ocl::absdiff(*a, *b, *c);
}

void oclAbsdiffS(const cv::ocl::oclMat* a, const CvScalar s, cv::ocl::oclMat* c)
{
   cv::ocl::absdiff(*a, s, *c);
}

void oclFlip(const cv::ocl::oclMat* a, cv::ocl::oclMat* b, int flipCode)
{
   cv::ocl::flip(*a, *b, flipCode);
}

void oclBitwiseNot(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst)
{
   cv::ocl::bitwise_not(*src, *dst);
}

void oclBitwiseAnd(const cv::ocl::oclMat* src1, const cv::ocl::oclMat* src2, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   cv::ocl::bitwise_and(*src1, *src2, *dst, mask ? *mask : cv::ocl::oclMat());
}

void oclBitwiseAndS(const cv::ocl::oclMat* src1, const cv::Scalar sc, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   cv::ocl::bitwise_and(*src1, sc, *dst,  mask ? *mask : cv::ocl::oclMat());
}

void oclBitwiseOr(const cv::ocl::oclMat* src1, const cv::ocl::oclMat* src2, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   cv::ocl::bitwise_or(*src1, *src2, *dst, mask? *mask : cv::ocl::oclMat());
}

void oclBitwiseOrS(const cv::ocl::oclMat* src1, const cv::Scalar sc, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   cv::ocl::bitwise_or(*src1, sc, *dst, mask? *mask : cv::ocl::oclMat());
}

void oclBitwiseXor(const cv::ocl::oclMat* src1, const cv::ocl::oclMat* src2, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   cv::ocl::bitwise_xor(*src1, *src2, *dst, mask? *mask : cv::ocl::oclMat());
}

void oclBitwiseXorS(const cv::ocl::oclMat* src1, const cv::Scalar sc, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   cv::ocl::bitwise_xor(*src1, sc, *dst, mask? *mask : cv::ocl::oclMat());
}

inline void normalizeAnchor(int& anchor, int ksize)
{
   if (anchor < 0)
      anchor = ksize >> 1;

   CV_Assert(0 <= anchor && anchor < ksize);
}
inline void normalizeAnchor(cv::Point* anchor, const cv::Size& ksize)
{
   normalizeAnchor(anchor->x, ksize.width);
   normalizeAnchor(anchor->y, ksize.height);
}

void oclMatGetKernel(cv::Mat& kernelMat, cv::Point* anchor, int* iterations)
{
   cv::Size ksize = kernelMat.data ? kernelMat.size() : cv::Size(3, 3);

   normalizeAnchor(anchor, ksize);

   if (kernelMat.empty())
   {
      cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1 + *iterations * 2, 1 + *iterations * 2));
      cv::swap(kernelMat, se);
      anchor->x = *iterations;
      anchor->y = *iterations;
      *iterations = 1;
   }
   else
   {
      if (*iterations > 1 && countNonZero(kernelMat) == kernelMat.rows * kernelMat.cols)
      {
         anchor->x = anchor->x * (*iterations);
         anchor->y = anchor->y * (*iterations);

         cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT,
            cv::Size(ksize.width + (*iterations - 1) * (ksize.width - 1),
            ksize.height + (*iterations - 1) * (ksize.height - 1)),
            *anchor);
         *iterations = 1;
      }
   }
}

void oclErode( const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, const CvArr* kernel, CvPoint anchor, int iterations, int borderType, CvScalar borderValue)
{

   cv::Mat kernelMat = kernel ? cv::cvarrToMat(kernel) : cv::Mat();
   cv::Point an = anchor;
   oclMatGetKernel(kernelMat, &an, &iterations);
   //char message[2000];
   //sprintf(message, "anchor = (%d, %d); iteration = %d; borderType = %d; borderValue = (%d, %d, %d, %d)", an.x, an.y, iterations, borderType, borderValue.val[0], borderValue.val[1], borderValue.val[2], borderValue.val[3]);
   //CV_Error(0, message);
   cv::ocl::erode(*src, *dst, kernelMat, an, iterations, borderType, borderValue);
}

void oclDilate( const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, const CvArr* kernel,  CvPoint anchor, int iterations, int borderType, CvScalar borderValue)
{
   cv::Mat kernelMat = kernel ? cv::cvarrToMat(kernel) : cv::Mat();
   cv::Point an = anchor;
   oclMatGetKernel(kernelMat, &an, &iterations); 
   cv::ocl::dilate(*src, *dst, kernelMat, an, iterations, borderType, borderValue);
}

void oclMorphologyEx( const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int op, const CvArr* kernel, CvPoint anchor, int iterations, int borderType, CvScalar borderValue)
{
   cv::Mat kernelMat = kernel ? cv::cvarrToMat(kernel) : cv::Mat();
   cv::Point an = anchor;
   oclMatGetKernel(kernelMat, &an, &iterations);
   cv::ocl::morphologyEx( *src, *dst, op, kernelMat, an, iterations, borderType, borderValue);
}

void oclCompare(const cv::ocl::oclMat* a, const cv::ocl::oclMat* b, cv::ocl::oclMat* c, int cmpop)
{
   cv::ocl::compare(*a, *b, *c, cmpop);
}

void oclCvtColor(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int code)
{
   cv::ocl::cvtColor(*src, *dst, code);
}

void oclMatCopy(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, const cv::ocl::oclMat* mask)
{
   src->copyTo(*dst, mask? * mask : cv::ocl::oclMat());
}

void oclMatSetTo(cv::ocl::oclMat* mat, const CvScalar s, const cv::ocl::oclMat* mask)
{
   (*mat).setTo(s, mask ? *mask : cv::ocl::oclMat());
}
void oclMatResize(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, double fx, double fy, int interpolation)
{
   cv::ocl::resize(*src, *dst, dst->size(), fx, fy, interpolation);
}

//only support single channel oclMat
void oclMinMaxLoc(const cv::ocl::oclMat* src, 
   double* minVal, double* maxVal, 
   CvPoint* minLoc, CvPoint* maxLoc, 
   const cv::ocl::oclMat* mask)
{
   cv::Point minimunLoc, maximunLoc;
   cv::ocl::oclMat maskMat = mask ? *mask : cv::ocl::oclMat();
   cv::ocl::minMaxLoc(*src, minVal, maxVal, &minimunLoc, &maximunLoc, maskMat);
   maxLoc->x = maximunLoc.x; maxLoc->y = maximunLoc.y;
   minLoc->x = minimunLoc.x; minLoc->y = minimunLoc.y;
}

void oclMatchTemplate(const cv::ocl::oclMat* image, const cv::ocl::oclMat* templ, cv::ocl::oclMat* result, int method, cv::ocl::MatchTemplateBuf* buffer)
{
   if (buffer)
      cv::ocl::matchTemplate(*image, *templ, *result, method, *buffer);
   else
   {
      cv::ocl::matchTemplate(*image, *templ, *result, method);      
   }
}

void oclPyrDown(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst)
{
   cv::ocl::pyrDown(*src, *dst);
}

void oclPyrUp(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst)
{
   cv::ocl::pyrUp(*src, *dst);
}

void oclSplit(const cv::ocl::oclMat* src, cv::ocl::oclMat** dst)
{
   int channels = src->channels();
   std::vector<cv::ocl::oclMat> dstArr(channels);
   //cv::ocl::oclMat* dstArr = new cv::ocl::oclMat[channels];
   for (int i = 0; i < channels; i++)
      dstArr[i] = *(dst[i]);
   cv::ocl::split(*src, dstArr);
   //delete[] dstArr;
}

void oclMerge(const cv::ocl::oclMat** src, cv::ocl::oclMat* dst)
{
   int channels = dst->channels();
   cv::ocl::oclMat* srcArr = new cv::ocl::oclMat[channels];
   for (int i = 0; i < channels; ++i)
      srcArr[i] = *(src[i]);
   cv::ocl::merge(srcArr, dst->channels(), *dst);
   delete[] srcArr;
}

void oclConvertTo(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, double alpha, double beta)
{
   src->convertTo(*dst, dst->type(), alpha, beta);
}

void oclFilter2D(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, const CvArr* kernel, CvPoint anchor, int borderType)
{
   cv::Mat kMat = cv::cvarrToMat(kernel);
   cv::ocl::filter2D(*src, *dst, src->depth(), kMat, anchor, borderType);
}

void oclReshape(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int cn, int rows)
{
   cv::ocl::oclMat tmp = src->reshape(cn, rows);
   dst->swap(tmp);
}

void oclSobel(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int dx, int dy, int ksize, double scale, int borderType)
{
   cv::ocl::Sobel(*src, *dst, dst->depth(), dx, dy, ksize, scale, borderType); 
}

void oclScharr(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int dx, int dy, double scale, double delta, int borderType)
{
   cv::ocl::Scharr(*src, *dst, dst->depth(), dx, dy, scale, delta, borderType);
}

void oclGaussianBlur(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, CvSize ksize, double sigma1, double sigma2, int borderType)
{
   cv::ocl::GaussianBlur(*src, *dst, ksize, sigma1, sigma2, borderType);
}

void oclLaplacian(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int ksize, double scale)
{
   cv::ocl::Laplacian(*src, *dst, src->depth(), ksize, scale);
}

void oclGemm(const cv::ocl::oclMat* src1, const cv::ocl::oclMat* src2, double alpha, 
                const cv::ocl::oclMat* src3, double beta, cv::ocl::oclMat* dst, int flags)
{
   cv::ocl::oclMat src3Mat = src3 ? *src3 : cv::ocl::oclMat();
   cv::ocl::gemm(*src1, *src2, alpha, src3Mat, beta, *dst, flags);
}

void oclCanny(const cv::ocl::oclMat* image, cv::ocl::oclMat* edges, double lowThreshold, double highThreshold, int apertureSize, bool L2gradient)
{
   cv::ocl::Canny(*image, *edges, lowThreshold, highThreshold, apertureSize, L2gradient);
}

void oclMeanStdDev(const cv::ocl::oclMat* mtx, CvScalar* mean, CvScalar* stddev)
{
   cv::Scalar meanVal, stdDevVal;
   cv::ocl::meanStdDev(*mtx, meanVal, stdDevVal);

   memcpy(mean->val, meanVal.val, sizeof(double)*4);
   memcpy(stddev->val, stdDevVal.val, sizeof(double) * 4);
}

double oclNorm(const cv::ocl::oclMat* src1, const cv::ocl::oclMat* src2, int normType)
{
   if (src2)
      return cv::ocl::norm(*src1, *src2, normType);
   else
      return cv::ocl::norm(*src1, normType);
}

void oclLUT(const cv::ocl::oclMat* src, const cv::ocl::oclMat* lut, cv::ocl::oclMat* dst)
{
   cv::ocl::LUT(*src, *lut, *dst);
}

void oclCopyMakeBorder(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int top, int bottom, int left, int right, int borderType, const CvScalar value)
{
   cv::ocl::copyMakeBorder(*src, *dst, top, bottom, left, right, borderType, value);
}

void oclMedianFilter(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int m)
{
   cv::ocl::medianFilter(*src, *dst, m);
}

void oclIntegral(const cv::ocl::oclMat* src, cv::ocl::oclMat* sum, cv::ocl::oclMat* sqrSum)
{
   if (sqrSum)
   {
      if (sum)
      {  //sqrSum && sum
         cv::ocl::integral(*src, *sum, *sqrSum);
      } else
      {
         //sqrSum && !sum
         cv::ocl::oclMat tmp;
         cv::ocl::integral(*src, tmp, *sqrSum);
      }

   } else if (sum)
   {  //!sqrSum && sum
      cv::ocl::integral(*src, *sum);
   } else 
   {
      //!sqrSum && !sum
      CV_Error(-1, "Neither sum nore sqrSum are initialized");
   }
}

void oclCornerHarris(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int blockSize, int ksize, double k, int borderType)
{
   cv::ocl::cornerHarris(*src, *dst, blockSize, ksize, k, borderType);
}

void oclBilateralFilter(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int d, double sigmaColor, double sigmaSpave, int borderType)
{
   cv::ocl::bilateralFilter(*src, *dst, d, sigmaColor, sigmaSpave, borderType);
}

void oclAdaptiveBilateralFilter(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, CvSize* ksize, double sigmaSpace, CvPoint* anchor, int borderType)
{
   cv::Size ks(ksize->width, ksize->height);
   cv::Point ap(anchor->x, anchor->y);
   cv::ocl::adaptiveBilateralFilter(*src, *dst, ks, sigmaSpace, ap, borderType);
}

void oclPow(const cv::ocl::oclMat* x, double p, cv::ocl::oclMat *y)
{
   cv::ocl::pow(*x, p, *y);
}

void oclExp(const cv::ocl::oclMat* a, cv::ocl::oclMat* b)
{
   cv::ocl::exp(*a, *b);
}

void oclLog(const cv::ocl::oclMat* a, cv::ocl::oclMat* b)
{
   cv::ocl::exp(*a, *b);
}

void oclCartToPolar(const cv::ocl::oclMat* x, const cv::ocl::oclMat* y, cv::ocl::oclMat* magnitude, cv::ocl::oclMat* angle, bool angleInDegrees)
{
   cv::ocl::cartToPolar(*x, *y, *magnitude, *angle, angleInDegrees);
}

void oclPolarToCart(const cv::ocl::oclMat* magnitude, const cv::ocl::oclMat* angle, cv::ocl::oclMat* x, cv::ocl::oclMat* y, bool angleInDegrees)
{
   cv::ocl::polarToCart(*magnitude, *angle, *x, *y, angleInDegrees);
}

void oclCalcHist(const cv::ocl::oclMat* mat_src, cv::ocl::oclMat* mat_hist)
{
   cv::ocl::calcHist(*mat_src, *mat_hist);
}

void oclEqualizeHist(const cv::ocl::oclMat* mat_src, cv::ocl::oclMat* mat_dst)
{
   cv::ocl::equalizeHist(*mat_src, *mat_dst);
}

void oclHoughCircles(const cv::ocl::oclMat* src, cv::ocl::oclMat* circles, int method, float dp, float minDist, int cannyThreshold, int votesThreshold, int minRadius, int maxRadius, int maxCircles)
{
   cv::ocl::HoughCircles(*src, *circles, method, dp,  minDist, cannyThreshold, votesThreshold, minRadius, maxRadius, maxCircles);
}

void oclHoughCirclesDownload(const cv::ocl::oclMat* d_circles, cv::Mat* h_circles)
{
   cv::ocl::HoughCirclesDownload(*d_circles, *h_circles);
}

void oclMeanShiftFiltering(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, int sp, int sr,
                              CvTermCriteria* criteria)
{
   cv::ocl::meanShiftFiltering(*src, *dst, sp, sr, *criteria);
}

void oclMeanShiftProc(const cv::ocl::oclMat* src, cv::ocl::oclMat* dstr, cv::ocl::oclMat* dstsp, int sp, int sr,
                         CvTermCriteria* criteria)
{
   cv::ocl::meanShiftProc(*src, *dstr, *dstsp, sp, sr, *criteria);
}

void oclMeanShiftSegmentation(const cv::ocl::oclMat* src, IplImage* dst, int sp, int sr, int minsize,
                                 CvTermCriteria* criteria)
{
   cv::Mat dstMat = cv::cvarrToMat(dst);
   cv::ocl::meanShiftSegmentation(*src, dstMat, sp, sr, minsize, *criteria);
}

void oclWarpAffine(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, const CvMat* M, int flags)
{
   cv::Mat mat = cv::cvarrToMat(M);
   //cv::Size size(dsize->width, dsize->height);
   cv::ocl::warpAffine(*src, *dst, mat, dst->size(), flags);
}

void oclWarpPerspective(const cv::ocl::oclMat* src, cv::ocl::oclMat* dst, const CvMat* M, int flags)
{
   cv::Mat mat = cv::cvarrToMat(M);
   //cv::Size size(dsize->width, dsize->height);
   cv::ocl::warpPerspective(*src, *dst, mat, dst->size(), flags);
}

cv::ocl::oclMat* oclMatGetSubRect(const cv::ocl::oclMat* arr, CvRect* rect)
{
   cv::Rect region(*rect);
   return new cv::ocl::oclMat(*arr, region);
}

cv::ocl::oclMat* oclMatGetRegion(cv::ocl::oclMat* other, CvSlice* rowRange, CvSlice* colRange)
{
   cv::Range row(*rowRange);
   cv::Range col(*colRange);
   return new cv::ocl::oclMat(*other, row, col);
}

void oclCLAHE(cv::ocl::oclMat* src, cv::ocl::oclMat* dst, double clipLimit, emgu::size* tileGridSize)
{
   cv::Size s(tileGridSize->width, tileGridSize->height);
   cv::Ptr<cv::CLAHE> clahe = cv::ocl::createCLAHE(clipLimit, s);
   clahe->apply(*src, *dst);
}

//----------------------------------------------------------------------------
//
//  OclHOGDescriptor
//
//----------------------------------------------------------------------------

void oclHOGDescriptorGetPeopleDetector64x128(std::vector<float>* vector)
{
   std::vector<float> v = cv::ocl::HOGDescriptor::getPeopleDetector64x128();
   v.swap(*vector);
}

void oclHOGDescriptorGetPeopleDetector48x96(std::vector<float>* vector)
{
   std::vector<float> v = cv::ocl::HOGDescriptor::getPeopleDetector48x96();
   v.swap(*vector);
}

cv::ocl::HOGDescriptor* oclHOGDescriptorCreateDefault() { return new cv::ocl::HOGDescriptor; }

cv::ocl::HOGDescriptor* oclHOGDescriptorCreate(
   cv::Size* _winSize, 
   cv::Size* _blockSize, 
   cv::Size* _blockStride,
   cv::Size* _cellSize, 
   int _nbins, 
   double _winSigma,
   double _L2HysThreshold, 
   bool _gammaCorrection, 
   int _nlevels)
{
   return new cv::ocl::HOGDescriptor(*_winSize, *_blockSize, *_blockStride, *_cellSize, _nbins, _winSigma, _L2HysThreshold, _gammaCorrection, _nlevels);
}

void oclHOGSetSVMDetector(cv::ocl::HOGDescriptor* descriptor, std::vector<float>* vector) 
{ 
   descriptor->setSVMDetector(*vector); 
}

void oclHOGDescriptorRelease(cv::ocl::HOGDescriptor** descriptor) 
{ 
   delete *descriptor;
   *descriptor = 0;
}

void oclHOGDescriptorDetectMultiScale(
   cv::ocl::HOGDescriptor* descriptor, 
   cv::ocl::oclMat* img, 
   CvSeq* foundLocations,
   double hitThreshold, 
   CvSize winStride,
   CvSize padding, 
   double scale,
   int groupThreshold)
{
   cvClearSeq(foundLocations);

   std::vector<cv::Rect> rects;
   
   //char message[2000];
   //sprintf(message, "winstride = (%d, %d); padding = (%d, %d)", winStride.width, winStride.height, padding.width, padding.height);
   //CV_Error(0, message);
   
   descriptor->detectMultiScale(*img, rects, hitThreshold, winStride, padding, scale, groupThreshold);
   if (!rects.empty())
      cvSeqPushMulti(foundLocations, &rects[0], static_cast<int>(rects.size()));
}


//----------------------------------------------------------------------------
//
//  oclMatchTemplateBuf
//
//----------------------------------------------------------------------------
cv::ocl::MatchTemplateBuf* oclMatchTemplateBufCreate()
{
   return new cv::ocl::MatchTemplateBuf();
}
void oclMatchTemplateBufRelease(cv::ocl::MatchTemplateBuf** buffer)
{
   delete *buffer;
   *buffer = 0;
}

//----------------------------------------------------------------------------
//
//  oclCascadeClassifier
//
//----------------------------------------------------------------------------
cv::ocl::OclCascadeClassifier* oclCascadeClassifierCreate(const char* filename)
{
   cv::ocl::OclCascadeClassifier* classifier =  new cv::ocl::OclCascadeClassifier();
   classifier->load(filename);
   return classifier;
}

void oclCascadeClassifierRelease(cv::ocl::OclCascadeClassifier** classifier)
{
   delete *classifier;
   *classifier = 0;
}

//----------------------------------------------------------------------------
//
//  OclPyrLKOpticalFlow
//
//----------------------------------------------------------------------------
cv::ocl::PyrLKOpticalFlow* oclPyrLKOpticalFlowCreate(emgu::size winSize, int maxLevel, int iters, bool useInitialFlow)
{
   cv::ocl::PyrLKOpticalFlow* flow = new cv::ocl::PyrLKOpticalFlow();
   
   flow->winSize = cv::Size(winSize.width, winSize.height);
   flow->maxLevel = maxLevel;
   flow->iters = iters;
   flow->useInitialFlow = useInitialFlow;
   return flow;
}

void oclPyrLKOpticalFlowSparse(
   cv::ocl::PyrLKOpticalFlow* flow, 
   const cv::ocl::oclMat* prevImg, 
   const cv::ocl::oclMat* nextImg, 
   const cv::ocl::oclMat* prevPts, 
   cv::ocl::oclMat* nextPts,
   cv::ocl::oclMat* status, 
   cv::ocl::oclMat* err)
{
   flow->sparse(*prevImg, *nextImg, *prevPts, *nextPts, *status, err);
}

void oclPyrLKOpticalFlowDense(
   cv::ocl::PyrLKOpticalFlow* flow, 
   const cv::ocl::oclMat* prevImg, 
   const cv::ocl::oclMat* nextImg,
   cv::ocl::oclMat* u, 
   cv::ocl::oclMat* v, 
   cv::ocl::oclMat* err)
{
   flow->dense(*prevImg, *nextImg, *u, *v, err);
}

void oclPyrLKOpticalFlowRelease(cv::ocl::PyrLKOpticalFlow** flow)
{
   delete *flow;
   *flow = 0;
}

//----------------------------------------------------------------------------
//
//  OpticalFlowDual_TVL1_OCL
//
//----------------------------------------------------------------------------
cv::ocl::OpticalFlowDual_TVL1_OCL*  oclOpticalFlowDualTVL1Create()
{
   return new cv::ocl::OpticalFlowDual_TVL1_OCL();
}
void oclOpticalFlowDualTVL1Compute(cv::ocl::OpticalFlowDual_TVL1_OCL* flow, cv::ocl::oclMat* i0, cv::ocl::oclMat* i1, cv::ocl::oclMat* flowx, cv::ocl::oclMat* flowy)
{
   (*flow)(*i0, *i1, *flowx, *flowy);
}
void oclOpticalFlowDualTVL1Release(cv::ocl::OpticalFlowDual_TVL1_OCL** flow)
{
   delete * flow;
   *flow = 0;
}

//----------------------------------------------------------------------------
//
//  Ocl Stereo
//
//----------------------------------------------------------------------------
cv::ocl::StereoBM_OCL* oclStereoBMCreate(int preset, int ndisparities, int winSize)
{
   return new cv::ocl::StereoBM_OCL(preset, ndisparities, winSize);
}

void oclStereoBMFindStereoCorrespondence(cv::ocl::StereoBM_OCL* stereo, const cv::ocl::oclMat* left, const cv::ocl::oclMat* right, cv::ocl::oclMat* disparity)
{
   (*stereo)(*left, *right, *disparity);
}

void oclStereoBMRelease(cv::ocl::StereoBM_OCL** stereoBM)
{
   delete *stereoBM;
   *stereoBM = 0;
}

cv::ocl::StereoConstantSpaceBP* oclStereoConstantSpaceBPCreate(int ndisp, int iters, int levels, int nr_plane)
{
   return new cv::ocl::StereoConstantSpaceBP(ndisp, iters, levels, nr_plane, CV_32F);
}

void oclStereoConstantSpaceBPFindStereoCorrespondence(cv::ocl::StereoConstantSpaceBP* stereo, const cv::ocl::oclMat* left, const cv::ocl::oclMat* right, cv::ocl::oclMat* disparity)
{
   (*stereo)(*left, *right, *disparity);
}

void oclStereoConstantSpaceBPRelease(cv::ocl::StereoConstantSpaceBP** stereo)
{
   delete *stereo;
   *stereo = 0;
}

//----------------------------------------------------------------------------
//
//  OclBruteForceMatcher
//
//----------------------------------------------------------------------------
cv::ocl::BFMatcher_OCL* oclBruteForceMatcherCreate(int distType) 
{
   return new cv::ocl::BFMatcher_OCL(distType);
}

void oclBruteForceMatcherRelease(cv::ocl::BFMatcher_OCL** matcher) 
{
   delete *matcher;
   *matcher = 0;
}

void oclBruteForceMatcherAdd(cv::ocl::BFMatcher_OCL* matcher, const cv::ocl::oclMat* trainDescs)
{
   std::vector< cv::ocl::oclMat > mats;
   mats.push_back( *trainDescs );
   matcher->add(mats);
}

void oclBruteForceMatcherKnnMatchSingle(
                                  cv::ocl::BFMatcher_OCL* matcher,
                                  const cv::ocl::oclMat* queryDescs, const cv::ocl::oclMat* trainDescs,
                                  cv::ocl::oclMat* trainIdx, cv::ocl::oclMat* distance, 
                                  int k, const cv::ocl::oclMat* mask)
{
   cv::ocl::oclMat emptyMat;
   mask = mask ? mask : &emptyMat;
   /*
   if (k == 2)
   {  //special case for k == 2;
      cv::ocl::oclMat idxMat = trainIdx->reshape(2, 1);
      cv::ocl::oclMat distMat = distance->reshape(2, 1);
      matcher->knnMatchSingle(*queryDescs, *trainDescs, 
         idxMat, distMat, 
         emptyMat, k, *mask);
      CV_Assert(idxMat.channels() == 2);
      CV_Assert(distMat.channels() == 2);
      CV_Assert(idxMat.data == trainIdx->data);
      CV_Assert(distMat.data == distance->data);
   } else*/
      matcher->knnMatchSingle(*queryDescs, *trainDescs, *trainIdx, *distance, emptyMat, k, *mask);
}


//----------------------------------------------------------------------------
//
//  Vector of VectorOfOclPlatformInfo
//
//----------------------------------------------------------------------------
std::vector<const cv::ocl::PlatformInfo*>* VectorOfOclPlatformInfoCreate()
{
   return new std::vector<const cv::ocl::PlatformInfo*>();
}

std::vector<const cv::ocl::PlatformInfo*>* VectorOfOclPlatformInfoCreateSize(int size)
{
   return new std::vector<const cv::ocl::PlatformInfo*>();
}

int VectorOfOclPlatformInfoGetSize(std::vector<const cv::ocl::PlatformInfo*>* v)
{
   return v->size();
}

void VectorOfOclPlatformInfoClear(std::vector<const cv::ocl::PlatformInfo*>* v)
{
   v->clear();
}

void VectorOfOclPlatformInfoRelease(std::vector<const cv::ocl::PlatformInfo*>* v)
{
   delete v;
}

const cv::ocl::PlatformInfo* VectorOfOclPlatformInfoGetStartAddress(std::vector<const cv::ocl::PlatformInfo*>* v)
{
   return v->empty() ? NULL : (*v)[0];
}

const cv::ocl::PlatformInfo* VectorOfOclPlatformInfoGetItem(std::vector<const cv::ocl::PlatformInfo*>* v, int index)
{
   return (*v)[index];
}

//----------------------------------------------------------------------------
//
//  Vector of VectorOfOclDeviceInfo
//
//----------------------------------------------------------------------------
std::vector<const cv::ocl::DeviceInfo*>* VectorOfOclDeviceInfoCreate()
{
   return new std::vector<const cv::ocl::DeviceInfo*>();
}

std::vector<const cv::ocl::DeviceInfo*>* VectorOfOclDeviceInfoCreateSize(int size)
{
   return new std::vector<const cv::ocl::DeviceInfo*>();
}

int VectorOfOclDeviceInfoGetSize(std::vector<const cv::ocl::DeviceInfo*>* v)
{
   return v->size();
}

void VectorOfOclDeviceInfoClear(std::vector<const cv::ocl::DeviceInfo*>* v)
{
   v->clear();
}

void VectorOfOclDeviceInfoRelease(std::vector<const cv::ocl::DeviceInfo*>* v)
{
   delete v;
}

const cv::ocl::DeviceInfo* VectorOfOclDeviceInfoGetStartAddress(std::vector<const cv::ocl::DeviceInfo*>* v)
{
   return v->empty() ? NULL : (*v)[0];
}

const cv::ocl::DeviceInfo* VectorOfOclDeviceInfoGetItem(std::vector<const cv::ocl::DeviceInfo*>* v, int index)
{
   return (*v)[index];
}

//----------------------------------------------------------------------------
//
//  OclPlatformInfo
//
//----------------------------------------------------------------------------

void oclPlatformInfoGetProperties(
   cv::ocl::PlatformInfo* oclPlatformInfo,
   const char** platformProfile,
   const char** platformVersion,
   const char** platformName,
   const char** platformVendor,
   const char** platformExtensions,

   int* platformVersionMajor,
   int* platformVersionMinor
   )
{
   *platformProfile = oclPlatformInfo->platformProfile.c_str();
   *platformVersion = oclPlatformInfo->platformVersion.c_str();
   *platformName = oclPlatformInfo->platformName.c_str();
   *platformVendor = oclPlatformInfo->platformVendor.c_str();
   *platformExtensions = oclPlatformInfo->platformExtensons.c_str();

   *platformVersionMajor = oclPlatformInfo->platformVersionMajor;
   *platformVersionMinor = oclPlatformInfo->platformVersionMinor;

}

std::vector<const cv::ocl::DeviceInfo*>* oclPlatformInfoGetDevices(cv::ocl::PlatformInfo* oclPlatformInfo)
{
   return &(oclPlatformInfo->devices);
}

//----------------------------------------------------------------------------
//
//  OclDeviceInfo
//
//----------------------------------------------------------------------------
void oclDeviceInfoGetProperty(cv::ocl::DeviceInfo* oclDeviceInfo, 
   int* type, 
   const char** profile, 
   const char** version,
   const char** name, 
   const char** vendor, 
   int* vendorId,
   const char** driverVersion, 
   const char** extensions,
   
   int* maxWorkGroupSize,
   int* maxComputeUnits,
   int* localMemorySize,
   int* maxMemAllocSize,
   int* deviceVersionMajor,
   int* deviceVersionMinor,
   int* haveDoubleSupport,
   int* isUnifiedMemory,
   const char** compilationExtraOptions
   )
{
   *type = oclDeviceInfo->deviceType;
   *profile = oclDeviceInfo->deviceProfile.c_str();
   *version = oclDeviceInfo->deviceVersion.c_str();
   *name = oclDeviceInfo->deviceName.c_str();
   *vendor = oclDeviceInfo->deviceVendor.c_str();
   *vendorId = oclDeviceInfo->deviceVendorId;
   *driverVersion = oclDeviceInfo->deviceDriverVersion.c_str();
   *extensions = oclDeviceInfo->deviceExtensions.c_str();

   *maxWorkGroupSize = static_cast<int>( oclDeviceInfo->maxWorkGroupSize );
   *maxComputeUnits = static_cast<int>( oclDeviceInfo->maxComputeUnits );
   *localMemorySize = static_cast<int> (oclDeviceInfo->localMemorySize );
   *maxMemAllocSize = static_cast<int> (oclDeviceInfo->maxMemAllocSize );
   *deviceVersionMajor = oclDeviceInfo->deviceVersionMajor;
   *deviceVersionMinor = oclDeviceInfo->deviceVersionMinor;
   *haveDoubleSupport = oclDeviceInfo->haveDoubleSupport ? 1 : 0;
   *isUnifiedMemory = oclDeviceInfo->isUnifiedMemory ? 1: 0;

   *compilationExtraOptions = oclDeviceInfo->compilationExtraOptions.c_str();
}

const cv::ocl::PlatformInfo* oclDeviceInfoGetPlatform(cv::ocl::DeviceInfo* oclDeviceInfo)
{
   return oclDeviceInfo->platform;
}


