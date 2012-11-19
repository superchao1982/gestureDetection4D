#pragma once

#define BUFFER_SIZE 150

//use every n-th hand update
#define FEATURE_VECTOR_FREQUENCY 1
#define WINDOW_NAME "GestureDetection4D"
#define SVM_MODEL_FILE "../../SVM_Model.txt"
#define SVM_PRE_MODEL_FILE "../../SVM_Pre_Model.txt"
#define DEBUG_FLAG
#define USE_PRE_SVM 0


const double BUFFER_WINDOWS[] = {0.5,1.};