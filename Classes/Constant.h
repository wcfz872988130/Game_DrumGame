#pragma once
/*
 * ��������
 */
static const char* SPLASH_SCENE = "scenes/Splash-scene.csb";
static const char* HOME_SCENE   = "scenes/Home-scene.csb";
static const char* GUIDE_SCENE  = "scenes/Guide-scene.csb";
static const char* GAME_SCENE   = "scenes/Game-scene.csb";

const std::string json_file_path = "Json/test.json";

float left_circle_radius;
cocos2d::Vec2 left_circle_center;
float right_circle_radius;
cocos2d::Vec2 right_circle_center;

const int FRESHHAND_ARRAY_LENGTH = 319;
const int SIMPLE_ARRAY_LENGTH = 697;
const int NORMAL_ARRAY_LENGTH = 950;

const float gate_accz = -0.995;
const float gate_interval = 0.200;
const float accz_delta=0.020;

const float time_offset=0.8;

float timeArray[NORMAL_ARRAY_LENGTH];
/*{ 4.900, 5.491, 5.772, 5.918, 6.203,
7.203, 7.774, 8.057, 8.203, 8.488,
9.488, 10.059, 10.342, 10.488, 10.773,
11.773, 12.344, 12.627, 12.773, 13.058,
14.06, 14.631, 15.063, 15.346, 15.775,
16.346, 16.917, 17.349, 17.632, 18.06,
18.634, 19.205, 19.63, 19.917, 20.346,
20.92, 21.493, 21.919, 22.202, 22.631,
23.205, 23.779, 24.056, 24.204, 24.488,
25.49, 26.061, 26.345, 26.49, 26.773,
27.773, 28.344, 28.628, 28.773, 29.056,
30.056, 30.627, 30.911, 31.057, 31.344,
32.347, 32.917, 33.346, 33.63, 34.058,
34.632, 35.203, 35.631, 35.915, 36.347,
36.921, 37.488, 37.92, 38.204, 38.632,
39.206, 39.78, 40.208, 40.492, 40.924,
41.523, 41.951, 42.348, 42.916, 43.2,
43.775, 44.203, 44.628, 45.057, 45.487,
46.062, 46.49, 46.887, 47.455, 47.739,
48.346, 48.772, 49.202, 49.628, 50.058,
50.633, 51.059, 51.485, 52.06, 52.348,
52.916, 53.342, 53.768, 54.343, 54.631,
55.199, 55.625, 56.051, 56.626, 56.914,
57.482, 57.908, 58.334, 58.909, 59.197,
60.065, 60.346, 60.63, 60.917, 61.205,
62.352, 62.633, 62.917, 63.204, 63.492,
64.639, 64.92, 65.204, 65.491, 65.779,
66.926, 67.207, 67.491, 67.778, 68.066,
69.206, 69.777, 70.348, 70.919, 71.49,
72.061, 72.632, 73.203, 73.774, 74.345,
74.916, 75.487, 76.058, 76.629, 77.2,
77.771, 78.35, 78.919, 79.49, 79.917,
80.346, 80.634, 81.203, 81.774, 82.201,
82.63, 82.918, 83.487, 84.058, 84.485,
84.914, 85.202, 85.771, 86.342, 86.769,
87.198, 87.488, 88.059, 88.63, 89.201,
89.772, 90.343, 90.914, 91.485, 92.056,
92.627, 93.198, 93.769, 94.34, 94.911,
95.482, 96.053, 96.286 };*/