Calculating Optical Flow
==============================================

Calculate the optical flow of 2 given images with different matching criterias and a given block size (radius) around all pixels.

Calling Arguments
=================
-help

-imgL=[Path]

-imgR=[Path]

-match=[0-2]

-blockS=[uint]

-maxF=[uint]

Filter Type (for -match=)
==========================
0: SSD 

1: ASD

2: Cross Correlation