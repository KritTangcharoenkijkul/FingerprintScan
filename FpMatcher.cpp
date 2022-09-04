#include "FpMatcher.hpp"

//----------------------------------------------------------------------
double FpMatcher::match(const cv::Mat& fpImg1, const cv::Mat& fpImg2) {
    MnSet mnSet1, mnSet2;
    cv::Mat mask1, mask2;
    cv::Mat img1,img2;
    cv::Mat enhanced1,enhanced2;
    cv::Mat binaryImg1, binaryImg2;
    

    int x;
    cout << "Press 1 for the fast but not accurate way, or 2 for the slower one but more accurate" << endl;
    cin >> x;

    
    cout << "Sengmentation" << endl;
    if (fpImg1.rows == 300) {
        fpSegmentator.segment2(fpImg1, mask1, img1);
        fpSegmentator.segment2(fpImg2, mask2, img2);
    }
    else {
        fpSegmentator.segment(fpImg1, mask1, img1);
        fpSegmentator.segment(fpImg2, mask2, img2);
    }
    cv::imshow("seg", img1);

    cout << "Enhancement" << endl;
    

    

    cout << "Mn extraction" << endl;
    
    binarizer.binarize(img1,binaryImg1);
    binarizer.binarize(img2,binaryImg2);
    cv::imshow("Binarized", binaryImg1);

    fpEnhancer.enhance(binaryImg1, enhanced1);
    fpEnhancer.enhance(binaryImg2, enhanced2);
    
    cv::imshow("Enhancement", enhanced1);

    cv::Mat skeletonizedImg1 = binaryImg1.clone();
    skeletonizer.skeletonize(skeletonizedImg1);
    
    cv::Mat skeletonizedImg2 = binaryImg2.clone();
    skeletonizer.skeletonize(skeletonizedImg2);
    
    cv::imshow("Skeleton", skeletonizedImg1);
    cv::imshow("Skeleton2", skeletonizedImg2);
    
    
    mnExtractor.extract(skeletonizedImg1, mnSet1);
    mnExtractor.extract(skeletonizedImg2, mnSet2);
    cout << "Mn matching" << endl;
   // cv::waitKey();
        double similarity;
    switch(x) {
        case 1 :
            similarity =mnMatcher.match1(mnSet1, mnSet2, skeletonizedImg1,skeletonizedImg1);
            break;       // and exits the switch
        case 2 :
            similarity = mnMatcher.match(mnSet1, mnSet2);
            break;
    }
    
    return similarity;


}
//----------------------------------------------------------------------
