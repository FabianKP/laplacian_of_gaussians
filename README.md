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
5. Implement Laplacian-of-Gaussians method. DONE
   1. Make a blob-class. DONE
   2. Make a scale-space representation function. DONE
   3. Make a normalized Laplacian function. DONE.
   4. Implement LoG. DONE
      1. Implement a method for finding strict local maxima/minima in 3d. DONE.
      2. Implement a method for intersection detection. DONE.
      3. Combine into LoG for finding bright blobs. DONE
      4. Extend so that LoG identifies both bright and dark blobs. DONE
6. Implement paintBlobs-function.
   1. Implement and test. DONE
   2. Solve the color problem (when you give paintBlobs a grayscale image). DONE
7. Refactor code.
   1. Improve comments. DONE
   2. Make LoG safer. If you give it a non-grayscale image, it should raise an error or convert.
8. Find more convincing examples (LoG performs bad on almonds-image.)
9. Create doxygen-documentation and put it somewhere in the repository.
10. Create and test library.
11. Set repository to "public".

Optional improvements:
---
- Handcode kernel for Laplacian (current implementation is based on Sobel operator).

Possible future features:
-------------------------

- Implement the other methods in Lindeberg's 2013 paper.
- Shape-adaptation.
