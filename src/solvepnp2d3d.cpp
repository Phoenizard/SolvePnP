#include <solvepnp2d3d.h>

vector<Point2f> SubPuber::processImg(Mat rawImage)
{
    QRCodeDetector qrDecoder = QRCodeDetector();
    vector<Point2f> bbox;
    qrDecoder.detect(rawImage,bbox);
    if(!bbox.empty()) {
        ROS_INFO("Get it");
        // cout << bbox << endl;
        string tag[4] = {"A","B","C","D"};
        for(int i=0;i<4;++i){
            line(rawImage, bbox[i], bbox[(i+1)%4], Scalar(124,252,0),4,8);
            putText(rawImage, tag[i],bbox[i],FONT_HERSHEY_DUPLEX,2,Scalar(0,0,255),2,8);
        }
    }else {
        ROS_INFO("No Code");
    }
    return bbox;
}

void SubPuber::solvePnP2_3(vector<Point2f> pnt2d, vector<Point3f> obj3d, Mat rVec, Mat tVec)
{
    const Mat cameraMatrix = (Mat_<double>(3, 3) <<
        268.5118713378906, 0.0,               320.0,
        0.0,               268.5118713378906, 240.0,
        0.0,               0.0,               1.0
    );
    const Mat distCoeffs = (Mat_<double>(5, 1) << 0, 0, 0, 0, 0);
    solvePnP(obj3d, pnt2d, cameraMatrix, distCoeffs, rVec, tVec, false, SOLVEPNP_ITERATIVE);
    //cout << endl << "RVec" << rVec << endl;
    cout << "tVec" << endl << tVec << endl;
    cout << "==============" << endl;
}