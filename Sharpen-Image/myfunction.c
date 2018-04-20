	// 308142389 Limor Levi

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

#define UPPER_BOUND 255
#define DOWN_BOUND 0

/** I delete the other struct because we can do the same operations by using only addresses
    I combine all the functions from the original code in one function because it is time consuming*/

void myfunction(Image *image, char *srcImgpName, char *blurRsltImgName,char *sharpRsltImgName) {
    // use variable from type 'register int' is much more efficient from 'int'
    register int nPower2 = n * n;

    // malloc ( 3 * nPower2 ) - instead of multiply with 3 , I used shift
    pixel *src = malloc( ((nPower2)<<1) + nPower2);

    // step : blur the image 
    // do function "charsToPixels" here =  copy the image to a pixels array -> calling to function is time consuming

    Image img = *image; //working with local variable is faster than pointer (not access to memory)

    // use variable from type 'register int' is much more efficient from 'int'
    register int row, col, rowN = 0, rowN_col = 0, three_rowN_col = 0;

    for (row = 0; row < n; ++row) {
        for (col = 0; col < n; col += 4) {
            src[rowN_col].red = img.data[three_rowN_col];
            src[rowN_col].green = img.data[++three_rowN_col];
            src[rowN_col].blue = img.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;

            src[rowN_col].red = img.data[three_rowN_col];
            src[rowN_col].green = img.data[++three_rowN_col];
            src[rowN_col].blue = img.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;

            src[rowN_col].red = img.data[three_rowN_col];
            src[rowN_col].green = img.data[++three_rowN_col];
            src[rowN_col].blue = img.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;

            src[rowN_col].red = img.data[three_rowN_col];
            src[rowN_col].green = img.data[++three_rowN_col];
            src[rowN_col].blue = img.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;
        }
	//instead of multiply (n * i) - I add n to rowN in the end of each iteration
        rowN += n;
    }

    // next step : apply the kernel over each pixel in the image
    // use variable from type 'register int' is much more efficient from 'int'
    register int index0 = 0, index1, index2, sum_red, sum_green, sum_blue, three_dim = n + n + n, index3 = three_dim + 3, i, j, k, upBound = n - 1;

    for (i = 1; i < upBound; ++i) {
        for (j = 1; j < upBound; ++j) {
            sum_red = 0;
            sum_blue = 0;
            sum_green = 0;
            // apply the kernel
            for (k = 0; k <= 2; ++k) {
                index1 = index0 + 1;
                index2 = index0 + 2;
		
		//sum all the values of the RGB colors into the counters sum_red, sum_greean, sum_blue
                sum_red += ((int) src[index0].red) + ((int) src[index1].red) + ((int) src[index2].red);
                sum_green += ((int) src[index0].green) + ((int) src[index1].green) + ((int) src[index2].green);
                sum_blue += ((int) src[index0].blue) + ((int) src[index1].blue) + ((int) src[index2].blue);

		//instead of multiply index0 in n in each iteration - I add n to index0 in the end of the loops
                index0 += n;
            }
            index0 -= (three_dim - 1);
            // put the result in the image in [i,j] - calculate the avarage of the 9 pixels , as described in the instructions
            image->data[index3] = ((sum_red) * 0xE38F) >> 19; // divide by 9 - using shifts is more efficient
            image->data[++index3] = ((sum_green) * 0xE38F) >> 19; //divide by 9 - using shifts is more efficient
            image->data[++index3] = ((sum_blue) * 0xE38F) >> 19; // divide by 9 - using shifts is more efficient
            ++index3;
        }
        index0 += 2;
        index3 += 6;
    }
    // write the image to the file
    writeBMP(image, srcImgpName, blurRsltImgName);

    // next step : sharp the image that was blured
    // do function "charsToPixels" here =  copy the image to a pixels array -> calling to function is time consuming

    Image img2 = *image; //working with local variable is faster than pointer (not access to memory)
    rowN = 0;
    rowN_col = 0;
    three_rowN_col = 0;
    for (row = 0; row < n; ++row) {
        for (col = 0; col < n; col += 4) {
            src[rowN_col].red = img2.data[three_rowN_col];
            src[rowN_col].green = img2.data[++three_rowN_col];
            src[rowN_col].blue = img2.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;

            src[rowN_col].red = img2.data[three_rowN_col];
            src[rowN_col].green = img2.data[++three_rowN_col];
            src[rowN_col].blue = img2.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;

            src[rowN_col].red = img2.data[three_rowN_col];
            src[rowN_col].green = img2.data[++three_rowN_col];
            src[rowN_col].blue = img2.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;

            src[rowN_col].red = img2.data[three_rowN_col];
            src[rowN_col].green = img2.data[++three_rowN_col];
            src[rowN_col].blue = img2.data[++three_rowN_col];
            ++rowN_col;
            ++three_rowN_col;
        }
	//instead of multiply (n * i) - I add n to rowN in the end of each iteration
        rowN += n;
    }

	//next step
    index0 = 0, index3 = three_dim + 3;
    for (i = 1; i < upBound; ++i) {
        for (j = 1; j < upBound; ++j) {
            sum_red = 0;
            sum_blue = 0;
            sum_green = 0;
            for (k = 0; k <= 2; ++k) {
                index1 = index0 + 1;
                index2 = index0 + 2;
		//instead of multiply the sums by (-1) , I substruct them from zero
                sum_red -= ((int) src[index0].red) + ((int) src[index1].red) + ((int) src[index2].red);
                sum_green -= ((int) src[index0].green) + ((int) src[index1].green) + ((int) src[index2].green);
                sum_blue -= ((int) src[index0].blue) + ((int) src[index1].blue) + ((int) src[index2].blue);

		//instead of multiply index0 in n in each iteration - I add n to index0 in the end of the loops
                index0 += n;
            }
            index0 -= (three_dim - 1);
            index1 = index0 + n;

            // add (the center pixel * 10) to the sums
            sum_red += 10 * ((int) src[index1].red);
            sum_green += 10 * ((int) src[index1].green);
            sum_blue += 10 * ((int) src[index1].blue);

	    /** I use if conditions instead of min/max functions or MACRO command in order to make sure that : 
                sum_red,sum_green and sum_blue are in the range [0,255] . using if statements is faster than calling to functions **/
	    if(sum_red < DOWN_BOUND){
            	sum_red = DOWN_BOUND;
            } else if(sum_red >UPPER_BOUND) {
            	sum_red = UPPER_BOUND;
            }


            if(sum_green < DOWN_BOUND){
            	sum_green = DOWN_BOUND;
            } else if(sum_green >UPPER_BOUND) {
            	sum_green = UPPER_BOUND;
            }


            if(sum_blue < DOWN_BOUND){
            	sum_blue = DOWN_BOUND;
            } else if(sum_blue >UPPER_BOUND) {
            	sum_blue = UPPER_BOUND;
            }

	    // put the result in the image in [i,j]
            image->data[index3] = sum_red;
            image->data[++index3] = sum_green;
            image->data[++index3] = sum_blue;
            ++index3;
        }
        index0 += 2;
        index3 += 6;
    }
    free(src);
    // write the image to the file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}

