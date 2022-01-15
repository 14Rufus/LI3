#ifndef __review_h_
#define __review_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "user.h"
#include "business.h"

typedef struct reviewInfo* Review;

Review createReview(char* id, char* user_id, char* business_id, char* stars, char* useful, char* funny, char* cool, char* date, char* text);

char* getIdReview(Review review);

char* getReviewUserId(Review review);

char* getReviewBusinessId(Review review);

float getReviewStars(Review review);

int getReviewUseful(Review review);

int getReviewFunny(Review review);

int getReviewCool(Review review);

char* getReviewData(Review review);

char* getReviewText(Review review);

int wordInText(Review review, char* word);

void freeReview(Review review);

#endif