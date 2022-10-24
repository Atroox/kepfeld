/**
* OpenCV gyakorlat
* Küszöbölés: iteratív módon
* Annak a küszöbértéknek a meghatározása, ahol az elõtér az egész képnek valahány % lesz.
*/

#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

///
/// Létrehozunk egy hisztogrammot a világosságértékek alapján
///
void createHisto(const cv::Mat img, cv::Mat& histo) {

	vector<Mat> kepek;       
	kepek.push_back(img); // egy képet használunk
	
	vector<int> csatornak;         
	csatornak.push_back(0); // annak az egy képnek a 0. csatornáját használjuk
	
	vector<int> hiszto_meretek; 
	hiszto_meretek.push_back(256);  //minden világosságkódot külön számolunk

	vector<float> hiszto_tartomanyok;
	hiszto_tartomanyok.push_back(0.0f); //hol kezdõdik a tartomány
	hiszto_tartomanyok.push_back(255);  //meddig tart	
   
	//accumlate: marad false (nullázza a hisztogrammot)
	calcHist(kepek, csatornak, noArray(), histo, hiszto_meretek, hiszto_tartomanyok, false);
}


int main() {

	//Input: szürkeskálás kép (vagy eleve szürkeskálában olvassuk be vagy a cvtColor-ral átalakítunk egy szineset)
	Mat img = imread("scanned3.png", IMREAD_GRAYSCALE);

	assert(!img.empty());

	cv::Mat histo;
	createHisto(img, histo);
	
	//ha nem tudod mit ad vissza, kérd le a méretet
	//cout << histo.size() << endl;
	
	//ha nem tudod, hogy milyen kép kerül vissza, kérd le a típust (interface.h-ban vannak a defek)
	//cout << histo.type() << endl;  
	
	float osszes = img.cols * img.rows; //összes képpont száma
	float hatter = 0.10f; 

	Mat dest;
	float s = 0;
	float th = 0;
	for (int i = 0; i < histo.rows; ++i) {
		s += histo.at<float>(i);
		if ( s / osszes > hatter ) {
			th = i;
			break;
		}
	}
	threshold(img, dest, th, 255, THRESH_BINARY_INV);

	imshow("arany", dest);
	waitKey();

	return 0;
}
