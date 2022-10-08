void readGyro(){
    gyro.read();
    // 각가속도의 절댓값
    GX = abs((int)gyro.g.x); 
    GY = abs((int)gyro.g.y);
    GZ = abs((int)gyro.g.z);
    if (GX >= 2000 || GY >= 2000 || GZ >= 2000){ //dps가 어느 방향이든 2000이 넘으면 fallbaby값이 true가 됨
        babyState = "Fall";
        Serial.println("Fall event!!");
    }else {
        babyState = "Not Fall";
    }
}
