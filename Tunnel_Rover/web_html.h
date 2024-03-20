char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Group-14--->>Lambogini</title>
    <style>
        html {
            font-family: Arial;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
        }

        p { font-size: 3.0rem; }
        .units { font-size: 1.2rem; }
        .dht-labels{
            font-size: 1.5rem;
            vertical-align:middle;
            padding-bottom: 15px;
        }
        .but{

            margin:20px;
            background-color:  darkcyan ;
            border: none;
            color: white;
            width:100px;
            height:100px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 20px;
            cursor: pointer;

        }
        body{
            background-color: rgba(114,72,124,0.96);


        }
        button {
            background-color: #797D7F;
            border: none;
            color: white;

            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;

            cursor: pointer;
            border-radius: 50%;

        }
        .right {
            transform: rotate(-45deg);
            -webkit-transform: rotate(-45deg);
        }

        .left {
            transform: rotate(135deg);
            -webkit-transform: rotate(135deg);
        }

        .up {
            transform: rotate(-135deg);
            -webkit-transform: rotate(-135deg);
        }

        .down {
            transform: rotate(45deg);
            -webkit-transform: rotate(45deg);
        }
        .arrow {
            border: solid black;
            border-width: 0 5px 5px 0;
            display: inline-block;
            padding: 3px;
        }
        label{
            font-size:30px;
        }

        .slider {
            -webkit-appearance: none;
            width: 100%;
            height: 15px;
            border-radius: 5px;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
            background-color: #FFD65C;
        }

        .slider:hover {
            opacity: 1;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #F4F6F7 ;
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #F4F6F7 ;
            cursor: pointer;
        }

        label{
            text-align: center;
            text-transform: uppercase;
        }
        hr{
            color: darkred;
            height: 5px;
        }
        .dht{
            width: auto;
            height: auto;
        }
        .control{
            width: 50%;
            height: 500px;
            float: left;
            background-color: #003249;
        }
        .light{
            width: 50%;
            height: 500px;
            float: right;
            background-color: coral;

        }
        .all_controllers{
            width: auto;

        }
        .range{
            background-color: peru;
        }
        .temp_humi{
            background-color: chocolate;
        }



    </style>


</head>

<body>

<div class="all_controllers">
    <div class="control">
        <button class="but" onclick="window.location='http://'+location.hostname+'/forward'" ><i class="arrow up"></i></button>
        <br>
        <button class="but" onclick="window.location='http://'+location.hostname+'/left'" ><i class="arrow left"></i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/stop'" >stop</button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/right'" ><i class="arrow right"></i></button>
        <br>
        <button class="but" onclick="window.location='http://'+location.hostname+'/backward'" ><i class="arrow down"></i></button>
    </div>
    <div class="light">
        <p><u>Light</u></p>
        <button class="but" onclick="window.location='http://'+location.hostname+'/lighton'" >On</button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/lightoff'" >Off</button>


        <div class="temp_humi">
            <p>
                <span class="dht-labels">Temperature</span>
                <span id="temperature">%TEMPERATURE%</span>
                <sup class="units">&deg;C</sup>
            </p>
            <p>
                <span class="dht-labels">Humidity</span>
                <span id="humidity">%HUMIDITY%</span>
                <sup class="units">%</sup>
            </p>

        </div>
    </div>


</div>


    <div>
        <br><br><br>
        <p><u>Camera Adjustment</u></p><br>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam00'" ><i>0</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam15'" ><i>15</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam30'" ><i>30</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam45'" ><i>45</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam60'" ><i>60</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam75'" ><i>75</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam90'" ><i>90</i></button>
        <br>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam105'" ><i>105</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam120'" ><i>120</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam135'" ><i>135</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam150'" ><i>150</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam165'" ><i>165</i></button>
        <button class="but" onclick="window.location='http://'+location.hostname+'/cam180'" ><i>180</i></button>

    </div>


<div class="range">


    <h2><span class="suspension"><p><u>Suspension</u></p></span></h2>
    <p><span id="textSliderValue_1">%Suspension%</span></p>
<input type="range" onchange="updateSliderPWM_1(this)" id="suspension" min="0" max="180" value="90"  class="slider">
<hr>


</div>


<script>

    function updateSliderPWM_1(element) {
        var sliderValue_1 = document.getElementById("suspension").value;
        document.getElementById("textSliderValue_1").innerHTML = sliderValue_1;
        console.log(sliderValue_1);
        var xhr_1 = new XMLHttpRequest();
        xhr_1.open("GET", "/slider_1?value="+sliderValue_1, true);
        xhr_1.send();
    }

    setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("temperature").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/temperature", true);
        xhttp.send();
    }, 1000 ) ;

    setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("humidity").innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/humidity", true);
        xhttp.send();
    }, 1000 ) ;


</script>

</body>
</html>

)=====";
