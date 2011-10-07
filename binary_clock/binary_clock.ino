//определим выводы светодиодов подключаемых к arduino 
  int led0 = 0;
  int led1 = 1;
  int led2 = 2;
  int led3 = 3;
  int led4 = 4;
  int led5 = 5;
  int led6 = 6;
  int led7 = 7;
  int led8 = 8;
  int led10 = 10;
  int led11 = 11;
  int led12 = 12;
  int led13 = 13;
  
//выводы кнопок
  int buttonHour = 0;
  int buttonMinute = 1;
  int buttonAlarm = 2;
  int buttonOnOff = 3;
//вывод динамика
  int speakerPin = 9;
  
  //считанные с аналоговых разьемов значения
  int hourValue, minuteValue, alarmValue, ledsOnOffValue;

  //сохраняем время
  int secondClock = 0, minuteClock = 0, hourClock = 0;
  //сохраняем время будильника
  int secondAlarm = 0, minuteAlarm = 0, hourAlarm = 0;
 
 //Для вывода младшего рязряда минут и часов
  int lowNumMinuteClock, lowNumHourClock;
 //тоже самое, только для будильника
  int lowNumMinuteAlarm, lowNumHourAlarm;
  //предыдущее значение времени
  unsigned long oldTime = 0;
  //по значению в них видно нажата кнопка или нет
  int minuteButtValue = 0, hourButtValue = 0;
  //режим часов или будильника
  boolean modeClock = true, modeAlarm = false;
  //активирован ли будильник
  boolean alarmOnOff = false;
  
  //для динамика
  int length = 28; 
  int tempo = 300;
  char notes[] = "caagafcccaahgCCddhhagffaagaf "; 
  int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
  

  void setup()
  {
    pinMode(led0, OUTPUT);  pinMode(led1, OUTPUT);  pinMode(led2, OUTPUT);  
    pinMode(led3, OUTPUT);  pinMode(led4, OUTPUT); pinMode(led5, OUTPUT); 
    pinMode(led6, OUTPUT);  pinMode(led7, OUTPUT);  pinMode(led8, OUTPUT);
    pinMode(led10, OUTPUT);  pinMode(led11, OUTPUT);  pinMode(led12, OUTPUT);  
    pinMode(led13, OUTPUT);
    
    pinMode(speakerPin, OUTPUT);
  }


void timing()
  {
    if (millis()-oldTime >= 1000)
    {
      oldTime = millis();
      secondClock++;
    }
    if (secondClock >= 60) { minuteClock++; secondClock = 0; }
    if (minuteClock >= 60) { hourClock++;   minuteClock = 0; }
    if (hourClock >= 24)   { hourClock = 0; minuteClock = 0; }  
    
    if (minuteAlarm >= 60) { minuteAlarm = 0; }
    if (hourAlarm >= 24)   { hourAlarm = 0; }  
    //надо посчитать остаток от деления на 10
    //для получения младшых разрядов чисел минут и часов
    
    lowNumMinuteAlarm = minuteAlarm%10;
    lowNumHourAlarm = hourAlarm%10;
    
    lowNumMinuteClock = minuteClock%10;
    lowNumHourClock = hourClock%10;
  }
  
void lightOnLed(boolean modeClock)
{    
      //Переменные для хранения значений секунд, минут и часов для непосредственно вывода
    int second = 0, minute = 0, hour = 0;
    int lowNumMinute, lowNumHour;
    if (modeClock == false)
    {
      hour = hourAlarm;
      minute = minuteAlarm;
      lowNumHour = lowNumHourAlarm;
      lowNumMinute = lowNumMinuteAlarm;
    }else
    {
      hour = hourClock;
      minute = minuteClock;
      lowNumHour = lowNumHourClock;
      lowNumMinute = lowNumMinuteClock;
    }
    ledsOnOffValue = analogRead(buttonOnOff);
    // зажигаем светодиодики, если нажата кнопка, иначе гасим их
    if ((ledsOnOffValue < 1000 && modeAlarm == true && alarmOnOff == true) || (ledsOnOffValue < 1000 && modeClock == true))
    {
      //отображение часов
      //верхний ряд светодиодов, первый справа
      if(hour >= 10 && hour < 20) {digitalWrite(led0, HIGH);}
      else { digitalWrite(led0,LOW);}
      
      //второй справа светодиод
      if(hour >= 20 && hour < 24) {digitalWrite(led1, HIGH);} 
      else {digitalWrite(led1,LOW);}
      
      //Нижний ряд светодиодов, первый светодиод справа
      if (lowNumHour==1 || lowNumHour==3 || lowNumHour==5 || lowNumHour==7 || lowNumHour==9){ digitalWrite(led2, HIGH);}
      else {digitalWrite(led2, LOW);}
      
      //второй светодиод справа
      if (lowNumHour==2 || lowNumHour==3 || lowNumHour==6 || lowNumHour==7){digitalWrite(led3, HIGH);}
      else {digitalWrite(led3, LOW);}
      
      //третий светодиод справа
      if (lowNumHour==4 || lowNumHour==5 || lowNumHour==6 || lowNumHour==7){ digitalWrite(led4, HIGH);}
      else{ digitalWrite(led4, LOW);}
      
      //четвертый светодиод справа
      if (lowNumHour==8 || lowNumHour==9){digitalWrite(led5, HIGH);}
      else{digitalWrite(led5, LOW);}
      
      //отображение минут
      //верхний ряд светодиодов, первый справа светодиод
      if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >=50 && minute < 60)) {digitalWrite(led6, HIGH);} 
      else {digitalWrite(led6,LOW);}
      //второй справа светодиод
      if(minute >= 20 && minute < 40) {digitalWrite(led7, HIGH);} 
      else {digitalWrite(led7,LOW);}
      //третий светодиод справа
      if(minute >= 40 && minute < 60) {digitalWrite(led8, HIGH);} 
      else {digitalWrite(led8,LOW);}
      
      //нижний ряд светодиодов, первый справа
      if (lowNumMinute==1 || lowNumMinute==3 || lowNumMinute==5 || lowNumMinute==7 || lowNumMinute==9) {digitalWrite(led10, HIGH);}  
      else {digitalWrite(led10, LOW);}
      //второй справа светодиод
      if (lowNumMinute==2 || lowNumMinute==3 || lowNumMinute==6 || lowNumMinute==7) {digitalWrite(led11, HIGH);}  
      else {digitalWrite(led11, LOW);}
      //третий справа светодиод
      if (lowNumMinute==4 || lowNumMinute==5 || lowNumMinute==6 || lowNumMinute==7){digitalWrite(led12, HIGH);}  
      else { digitalWrite(led12, LOW);}
      //четвертый справа светодиод
      if (lowNumMinute==8 || lowNumMinute==9){digitalWrite(led13, HIGH);}  
      else {digitalWrite(led13, LOW);}
    }else
    {
       for(int i=0;i<=13;i++){  digitalWrite(i, LOW); }
    }
}

void readButtons()
{
    alarmValue = analogRead(buttonAlarm);
    //обрабатываем нажатие на кнопку переключения режимов
    if (alarmValue < 1000)
    {
      if (modeClock == true)
      {
        modeClock = false;
        modeAlarm = true;
        tone(speakerPin, 1900);
        delay(200);
        noTone(speakerPin);
        
        //после переключения режимов, обнуляем все сигналы на цифровых выходах
        for(int i=0;i<=13;i++)  { digitalWrite(i, LOW); }
        delay(200);
      } else
      {
        modeClock = true;
        modeAlarm = false;
        //после переключения режимов, обнуляем все сигналы на цифровых выходах
        for(int i=0;i<=13;i++) { digitalWrite(i, LOW);}
        delay(200);
      }
       
    }
    //считывание нажатий на кнопjr изменения часов и минут
    hourValue = analogRead(buttonHour);
    minuteValue = analogRead(buttonMinute);
    //в режиме будильника при нажатии на кнопки увеличения минут и часов включают или выключают будильник()
    if (hourValue < 1000 && minuteValue < 1000)
    {
      if (alarmOnOff == false) {alarmOnOff = true;}else {alarmOnOff = false;}
    }
    //обработка нажатия на кнопку прибавления часов
    if (modeClock == true)
    {
      if (hourValue < 1000)
      {
        hourClock = hourClock + 1;
        delay(200);
      }
      //нажатие на кнопку прибавления минут
      
      if (minuteValue < 1000)
      {
        minuteClock = minuteClock + 1;;
        delay(200);
      }
    }else 
    //увеличиваем значение минут и часов будильника
    {
      if (hourValue < 1000)
      {
        hourAlarm = hourAlarm + 1;
        delay(200);
      }
      //нажатие на кнопку прибавления минут
      
      if (minuteValue < 1000)
      {
        minuteAlarm = minuteAlarm + 1;;
        delay(200);
      } 
    }
}

void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);      
  }
}

void playNote(char note, int duration) 
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // проиграть тон, соответствующий ноте
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);

    }
  }
}

void playAlarm()
{
  if ((secondClock == secondAlarm && minuteClock == minuteAlarm && hourClock == hourAlarm && alarmOnOff == true))
  {  
      for (int i = 0; i < length; i++) 
      {
        playNote(notes[i], beats[i] * tempo);
        delay(tempo / 4); 
        //считаываем значение с кнопки переключения режимов, (при проигрывании мелодии она будет выключать будильник)
        alarmValue = analogRead(buttonAlarm);
        if (alarmValue < 1000)
        {
          alarmOnOff = false;
          goto exit; 
        }
      }
     //прибавляем длительность мелодии к времени, чтобы не сбить его
     secondClock=secondClock+10;
     //если пользователь не выключил будильник сам, тогда мелодия повторится на следующей минуте
     minuteAlarm++;
  }
exit:return;
}

//главный цикл, вызов всех процедур
void loop()
{
    timing();
    lightOnLed(modeClock);
    readButtons(); 
    playAlarm();
}
