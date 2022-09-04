#include "MnMatcher.hpp"
#define PI 3.14159265
double angle;
int Cmax;

cv::Point2f translationVector;

void rot (Minutiae& i )
{
    i.pos +=translationVector;
    int  x =  i.pos.x ;
    int  y=  i.pos.y ;
    i.pos.x = ((x * cos(-angle)) - (y * sin(-angle)));
    i.pos.y =((y * cos(-angle)) + (x * sin(-angle)));
}
float MnMatcher::getAngle(cv::Point2f vector1, cv::Point2f vector2)
{
    float scalarProd = (vector1.x * vector2.x)+(vector1.y * vector2.y);
    float norm1 = sqrt(pow((vector1.x),2)+pow(vector1.y,2));
    float norm2 = sqrt(pow((vector2.x),2)+pow(vector2.y,2));
    float tmpCos = (scalarProd)/(norm1*norm2);
    
    float angle = acos(tmpCos) *180 / PI;
    return angle;
}

vector<cv::KeyPoint> convertEnd(const MnSet& mnSet)
{
    vector<cv::KeyPoint> keypoint2;
    for(int i = 0 ; i < mnSet.size() ; i ++)
    {
        if(mnSet.at(i).type == 1)
           {
           cv::KeyPoint a;
           a.pt = mnSet.at(i).pos;
           keypoint2.push_back(a);
           }
    }
    return keypoint2;
}

vector<cv::KeyPoint> convertBif(const MnSet& mnSet)
{
    vector<cv::KeyPoint> keypoint2;
    for(int i = 0 ; i < mnSet.size() ; i ++)
    {
        if(mnSet.at(i).type == 2)
        {
            cv::KeyPoint a;
            a.pt = mnSet.at(i).pos;
            keypoint2.push_back(a);
        }
    }
    return keypoint2;
}
bool sortByDistance(const cv::DMatch &lhs, const cv::DMatch &rhs) { return lhs.distance < rhs.distance; }


void evaluate(int keyPointEnd, int keyPointBif, int end, int bif, int threshold)
{
  double percentageEnd = ((end)*100)/keyPointEnd;
  double percentageBif = ((bif)*100)/keyPointBif;

    if(((percentageBif + percentageEnd)/2) >= threshold)
        cout << "It seems that the two fingerprint are the same " << ((percentageBif + percentageEnd)/2) << "%" <<endl;
    else
        cout << "Something wrong appens, finger print aren't the same " << ((percentageBif + percentageEnd)/2) << endl;

   }

void evaluate2(int nbPoint, int cMax, int threshold)
{
    
    if((Cmax*100)/nbPoint >= threshold)
        cout << "It seems that the two fingerprint are the same " << (Cmax*100)/nbPoint <<"%" <<  endl;
    else
        cout << "Something wrong appens, finger print aren't the same " << (Cmax*100)/nbPoint <<"%" << endl;
    
}
//----------------------------------- -----FAST METHODE -----------------------------
double MnMatcher::match1(const MnSet& mnSet1, const MnSet& mnSet2, const cv::Mat skel1,const cv::Mat skel2 ) {
    // Creation of discriptors
    cv::Ptr<cv::Feature2D> orb_descriptor;
    orb_descriptor= cv::ORB::create();
    // Convertion of minutiaes to keyPoints
    cv::Mat descriptors1End, descriptors2End,descriptors1Bif, descriptors2Bif ;
    vector<cv::KeyPoint> keypoints1End,keypoints2End, keypoints1Bif,keypoints2Bif ;
    keypoints1End = convertEnd(mnSet1);
    keypoints2End = convertEnd(mnSet2);

    keypoints1Bif = convertBif(mnSet1);
    keypoints2Bif = convertBif(mnSet2);

    
    
    
    orb_descriptor->compute(skel1, keypoints1End, descriptors1End);
    orb_descriptor->compute(skel2, keypoints2End, descriptors2End);
    orb_descriptor->compute(skel1, keypoints1Bif, descriptors1Bif);
    orb_descriptor->compute(skel2, keypoints2Bif, descriptors2Bif);

    cv::BFMatcher matcher(cv::NORM_HAMMING,true);
    
    std::vector<cv::DMatch> matchesEnd, matchesBif;
    
    matcher.match(descriptors1End, descriptors2End, matchesEnd);
    matcher.match(descriptors1Bif, descriptors2Bif, matchesBif);
    
//    for(int i = 0 ; i < matchesBif.size() ; i++)
//    {
//        cout << matchesBif[i].distance << endl;
//    }
    
    double max_distBif = 0; double min_distBif = 200;
    
    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < matchesBif.size(); i++ )
    { double dist = matchesBif[i].distance;
        if( dist < min_distBif ) min_distBif = dist;
        if( dist > max_distBif ) max_distBif = dist;
    }

    std::vector<cv::DMatch> good_matchesBif;
    if(min_distBif <= 60) min_distBif =min_distBif * 2;
    for( int i = 0; i < matchesBif.size(); i++ )
    {
       // cout <<matchesBif[i].distance << " " <<min_distBif << endl;
        if( matchesBif[i].distance <= min_distBif )
        {
            good_matchesBif.push_back( matchesBif[i]);
        }
    }


    evaluate(keypoints1End.size(), keypoints1Bif.size(),  matchesEnd.size() , matchesBif.size(),  50);
    
    cv::Mat img_matches1, img_matches2;
    drawMatches(skel1, keypoints1End, skel2, keypoints2End, matchesEnd, img_matches1);
    drawMatches(skel1, keypoints1Bif, skel2, keypoints2Bif, matchesBif, img_matches1);

   cv::imshow("match1", img_matches1);
    
    cv::waitKey();
    
    
    return 100;
}


// ------------------------------------- SLOW METHOD -----------------------------


double MnMatcher::match(const MnSet& mnSet1, const MnSet& mnSet2) {
    
    cout << "Stub: matching mnSet1 with mnSet2" << endl;
    

    // ------------------------------------ MnMatcher algorithme -----------------------------------
    Cmax = 0 ; // our Cmax
    cv::Point2f vector1, vector2 , pointA1 , pointA2 , pointB1 , pointB2;
    MnSet mnSet2testTranslated;
    
    // We go trough all points
    int size = min(mnSet1.size(), mnSet2.size());
    
    double stop = (80*mnSet1.size())/100;
    
    for(int i = 0 ; i < mnSet1.size() ; i++)
    {
        for(int j = 0 ; j < mnSet1.size() ; j++)
        {
            for(int k = 0 ; k < mnSet2.size() ; k++)
            {
                for(int h = 0 ; h < mnSet2.size() ; h++)
                {
                    
                    int tmpC =0;
                    pointA1 = mnSet1.at(i).pos; // 1st point, 1st pair (A pair)
                    pointA2 = mnSet1.at(j).pos; // 2nd point, 1st pair (A pair)
                    
                    pointB1 = mnSet2.at(k).pos; // 1st point, 2nd pair (B pair)
                    pointB2 = mnSet2.at(h).pos; // 2nd point, 2nd pair (B pair)
                    
                    translationVector= pointA1 - pointB1; // Transltion vector
                    
                    // translate our 2nd couple of points
                    pointB1 = pointB1+translationVector;
                    pointB2 = pointB2+translationVector;
                    
                    // calcul of two vector formed by our couples
                    
                    vector1 = pointA2 - pointA1;
                    vector2 = pointB2 - pointB1;
                    
                    // calcul of the rotation between our two couple of point after translation A and B
                    angle = getAngle(vector1,vector2);
                    
                    
                    mnSet2testTranslated = mnSet2;
                    
                    std::for_each (mnSet2testTranslated.begin(), mnSet2testTranslated.end(), rot);
                    
                    for(int l = 0 ; l < size ; l++)
                    {
                        if((mnSet2testTranslated.at(l).pos.x <= mnSet1.at(l).pos.x + 20 &&  mnSet2testTranslated.at(l).pos.x  >= mnSet1.at(l).pos.x - 20) &&  (mnSet2testTranslated.at(l).pos.y <=mnSet1.at(l).pos.y + 20 &&  mnSet2testTranslated.at(l).pos.y  >= mnSet1.at(l).pos.y - 20) && mnSet2testTranslated.at(l).type  == mnSet1.at(l).type)
                        {
                            tmpC++;
                        }
                        
                    }
                    
                    if(tmpC > Cmax)
                    {
                        Cmax = tmpC ; cout << Cmax << endl;
                        if(Cmax > stop)
                        {
                            goto stop;
                        }
                    }
                }
            }
        }
    }
    
stop:
    evaluate2(size,Cmax,60);
    
    return Cmax;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
