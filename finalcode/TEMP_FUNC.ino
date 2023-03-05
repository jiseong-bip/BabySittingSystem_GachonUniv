void readTemp(){
    Rtemp = mlx.readObjectTempC() * 36/46;
    Serial.println(Rtemp);
}
