#include"html.h"

String load_pageIP()
{
String pageIP = "";
 pageIP = "<!DOCTYPE HTML>";
 pageIP += "<html>";
 pageIP += "<style>";
 pageIP += "ul {column-count: 3; column-gap: 18rem;}";
 pageIP += "</style>";

pageIP += "<p>";
pageIP += "<body>";
pageIP += EEPROM.read(500);
pageIP += ".";
pageIP += EEPROM.read(501);
pageIP += ".";
pageIP += EEPROM.read(502);
pageIP += ".";
pageIP += EEPROM.read(503);
pageIP += "</p>";
pageIP += "</body>";
pageIP += "</html>";
return pageIP;

}

String load_page()
{
  //the HTML of the web page
 String page = "";
 page = "<!DOCTYPE HTML>";
 page += "<html>";
 page += "<style>";
 page += "ul {column-count: 3; column-gap: 18rem;}";
 page += "<\/style>";

page += "<body>";

page += "<p><b>Ustawienia czasu podlewania:</b></p>";
page += "<ul class=\"checkboxes\">";
page += "<form action=\"/act\" method=\"get\">";
page += "<li><label><input type=\"checkbox\" name=\"text24\" value=\"24\" \/>0:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text1\" value=\"1\" \/>1:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text2\" value=\"2\" \/>2:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text3\" value=\"3\" \/>3:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text4\" value=\"4\" \/>4:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text5\" value=\"5\" \/>5:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text6\" value=\"6\" \/>6:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text7\" value=\"7\" \/>7:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text8\" value=\"8\" \/>8:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text9\" value=\"9\" \/>9:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text10\" value=\"10\" \/>10:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text11\" value=\"11\" \/>11:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text12\" value=\"12\" \/>12:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text13\" value=\"13\" \/>13:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text14\" value=\"14\" \/>14:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text15\" value=\"15\" \/>15:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text16\" value=\"16\" \/>16:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text17\" value=\"17\" \/>17:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text18\" value=\"18\" \/>18:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text19\" value=\"19\" \/>19:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text20\" value=\"20\" \/>20:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text21\" value=\"21\" \/>21:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text22\" value=\"22\" \/>22:00<\/label><\/li>";
page += "<li><label><input type=\"checkbox\" name=\"text23\" value=\"23\" \/>23:00<\/label><\/li>";
page += "<\/ul>";

page += "<p>Czas podlewania";
page += "<select name=\"czas\">";
page += "<option>10s</option>";
page += "<option>20s</option>";
page += "<option selected>30s</option>";
page += "<option>40s</option>";
page += "<option>50s</option>";
page += "<option>60s</option>";
page += "</select>";
page += "</p>";

page += "<p><input type=\"submit\" value=\"Submit\"></p>";
page +=  "<p></br> </p>";
page += "<p><b>Ustawione parametry podlewania:</b></p>";
for (int i = 0; i < 8; i++)
{
    int z = EEPROM.read(350 + i);
    if (z != 100)
    {
        page += "<p>Godzina podlewania: ";
        page += z;
        page += ":00</p>";
    }
}
page +=  "<p>Czas podlewania: ";
page += EEPROM.read(0);//time_water;
page += " sekund</p>";
page +=  "<p></br></p>";
page += "</form>";
page += "<form action=\"/res\" method=\"get\">";
page += "<p><a class=\"button\" href=\"res\"><button>Restart</button></a>";
page += "<p><b>Kiedy podlewano:</b></p>";
int print_line = EEPROM.read(299);
for (int e = 0; e < 10; e++)
{
    print_line--;
    if (print_line < 0) print_line = 9;
    page += "<p>";
    for(int i = 0; i < 19; i++)
    {
         page += (char) EEPROM.read(20*print_line + (i+2));
         if (i == 9 or i == 10)
             page += " ";
    }
    page += "</p>"; 
}
page += "</body>";
page += "<\/html>";
return page;
}
 
