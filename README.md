Laplacian-of-Gaussians for scale-space blob detection
=====================================================

This is a C++ implementation of the [Laplacian-of-Gaussians]() method for
blob detection. This implementation distinguishes itself from existing 
implementations, such as in scikit-image or opencv, in two aspects:
- Instead of a sampled Gaussian kernel, it uses the correct discrete analog of
the continuous Gaussian from the perspective of scale-space theory. This kernel, which I will refer to 
as the *discrete Gaussian kernel*, is based on modified Bessel functions 
(see [here](https://en.wikipedia.org/wiki/Scale_space_implementation#The_discrete_Gaussian_kernel).)

The implementation requires you to have OpenCV installed. See
[here](https://docs.opencv.org/4.6.0/d7/d9f/tutorial_linux_install.html) for Linux
or [here](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html) for Windows.

This library provides two C++ functions:
- ``discreteGaussian``: Convolves an n-dimensional array with a discrete Gaussian kernel.
- ``laplacianOfGaussians``: Performs blob detection on an n-dimensional array (representing a time-series, image, video, ...)
  with the Laplacian-of-Gaussians method, using the discrete Gaussian kernel for the scale-space representation.


Installation
-----



Usage
-----

```
#include <opencv2/opencv.hpp>
#include "blobs.h"
#include <cstdlib>
```


TODO:
-----

1. Install opencv and test your installation (plot something). DONE
2. Implement N-dimensional convolution with Bessel kernel. DONE
3. Test. DONE
4. Implement Laplacian-of-Gaussians method. DONE
   1. Make a blob-class. DONE
   2. Make a scale-space representation function. DONE
   3. Make a normalized Laplacian function. DONE.
   4. Implement LoG. DONE
      1. Implement a method for finding strict local maxima/minima in 3d. DONE.
      2. Implement a method for intersection detection. DONE.
      3. Combine into LoG for finding bright blobs. DONE
      4. Extend so that LoG identifies both bright and dark blobs. DONE
5. Implement paintBlobs-function.
   1. Implement and test. DONE
   2. Solve the color problem (when you give paintBlobs a grayscale image). DONE
6. Refactor code. DONE
   1. Improve comments. DONE
   2. Make LoG safer. If you give it a non-grayscale image, it should raise an error or convert. DONE.
7. Find more convincing examples. DONE
8. Write a mini-tutorial in the README.
9. Create and test library.
10. Set repository to "public".


Possible future features:
-------------------------

- Additional speedup through downsampling (pyramid).
- Implementation of further blob detection methods (difference of Gaussians, determinant of Hessians, etc.).
- Shape-adaptation: Instead of only identifying circles, detect blobs as rotated ellipses.
