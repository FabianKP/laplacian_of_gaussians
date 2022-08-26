Laplacian-of-Gaussians for scale-space blob detection
=====================================================

This is a C++ implementation of the [Laplacian-of-Gaussians]() method for
blob detection. This implementation distinguishes itself from existing 
implementations, such as in scikit-image or opencv, in two aspects:
- Instead of a sampled Gaussian kernel, it uses the correct discrete analog of
the continuous Gaussian from the perspective of scale-space theory. This kernel, which I will refer to 
as the *discrete Gaussian kernel*, is based on modified Bessel functions 
(see [here](https://en.wikipedia.org/wiki/Scale_space_implementation#The_discrete_Gaussian_kernel).)
- It allows for the use of anisotropic convolution kernels. That is, it allows for convolution kernels that are
not symmetric in all directions.

This library provides two efficient C++ functions:
- ``discreteGaussian``: Convolves an n-dimensional array with a discrete Gaussian kernel.
- ``laplacianOfGaussians``: Performs blob detection on an n-dimensional array (representing a time-series, image, video, ...)
  with the Laplacian-of-Gaussians method, using the discrete Gaussian kernel for the scale-space representation.


For a mathematical description of the method and its background, see [here]().

TODO:
-----

1. Write mathematical design doc. POSTPONED.
2. Install opencv and test your installation (plot something). DONE
3. Implement N-dimensional convolution with Bessel kernel. DONE
4. Test. DONE
5. Implement Laplacian-of-Gaussians method.
   1. Make a blob-class. DONE
   2. Make a scale-space representation function. DONE
   3. Make a normalized Laplacian function. DONE.
   4. Implement LoG.
      1. Implement a method for finding strict local maxima/minima in 3d. DONE.
      2. Implement a method for intersection detection. DONE.
      3. Combine into LoG.
6. Optimize code (minimize copying).

Issues:
---
Currently, there is the small issue that OpenCV SUCKS!!! Dilation and erosion seem to not
work for 3D-arrays. So, I guess I will have to find a different library to do all the 3D-things.

Optional improvements:
---
- Handcode kernel for Laplacian (current implementation is based on Sobel operator).

Possible future features:
-------------------------

- Implement the other methods in Lindeberg's 2013 paper.
