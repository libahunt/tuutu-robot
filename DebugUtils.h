/*************************************************************************************
Serial debugging functions
DP means Serial.print(), DPL means Serial.println()
but only if DEBUG is defined
based on http://forum.arduino.cc/index.php?PHPSESSID=t751ftglgpibikp8fa2h70o8s4&topic=46900.msg338653#msg338653 
*************************************************************************************/

#ifdef DEBUG
  #define DP(str) \
    Serial.print(str); \
    Serial.print(" ");
  #define DPL(str) \
    Serial.println(str);
#else
  #define DP(str)
  #define DPL(str)
#endif
