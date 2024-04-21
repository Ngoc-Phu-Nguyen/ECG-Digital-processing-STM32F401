# ECG-Digital-processing-STM32F401
Apply DSP for the signal ECG and analyze it by using FFT 

Hi dude, this is some messed stuffs I did with ECG((

**Part of the ECG Signal**

![](https://mozanunal.com/images/ekg15.jpg)

### Cleaning Noise using IIR and FIR filter

**Scope image of the output signal of the ECG circuit**
![ECG_20 12](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/18486202-8a03-4a4f-860e-a0fe898360dc)


The red one is the raw signal EMG with noises, there are 50/60Hz noise, low-high frequency noise. 
The blue one is the signal affer using filter.

**Raw ECG**
![50Hz_ecg](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/686873fe-c7a4-4336-a2e4-5d628e7dc44b)





**0 - 850Hz Frequency Spectrum**

Using FFT to see how the noise of signal is. In this case I am using ADC with rate of **1718Hz**, lenght of buffer FFT is **2048**. We will get the buffer amplitude-frequence with 1024 points. And each interval response to 1718/2048(Bin width) = 0.84Hz. Hence, the range frequency is around 0.84*1024 = 850Hz.  

![FFT_ECG](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/f92cfadc-2617-439d-a3fe-b362a7b6bd61)

**Sampling rate**
![Sampling_No FFT ](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/24faf78a-73c7-424d-bad0-bef9279a29cb)


In the this figure, you can see at 50Hz there is a huge amplitude. And we have to cancel it by using notch filter(IIR filter type). The scale time in the figure above is 3ms for each 0.84Hz. I did it to easier observe. 


**50 Hz Band Stop Filter**

A digital IIR filter is designed to filter out a 50 Hz frequency component. I built a RLC simple fitler. Using a circuit continuous RLC you can get the frequency transfrom function H(s). Hence, we cna get the cutoff frequency, the width of stop band.
Notice that by using DPS, the cutoff frequency will change a little bit, ups on the rate sampling. Its math, I dont know well:v. I will put the MathCad file above. 

![notch fitler](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/69b9a29d-ff17-4496-b505-1450bf45a47a)


After the filtering, the frequency domain components are examined again. The noise component at 50 Hz is removed from the signal. Check in those figures above. 


The next filter is designed to remove high-frequency noise from the signal. For this purpose, a 0-100 Hz low pass filter is designed.

**0 - 100 Hz Low Pass Filter**

![LPF](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/46cc2384-f57a-40c9-9e2d-d38ab7f11c61)



Finally, A simple moving average filter is applied to the signal. The next figure is the final result of our ECG project. After the filtering operations, most of the ECG components are cleaner and now it is easier to extract ECG components from the signal.

**20 Point Simple Moving Average Filtered Signal**

![ecg2](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/83b75d12-743c-4507-878a-2008ff889cf6)

**Time Domain Result**

The time-domain result of the filters. As you can see from this figure, the time domain components of the ECG is cleaner.

![ecg1](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/c006e620-0d1f-4dbd-a066-a37b0176434c)

**Idea for code**

![Ideal for code drawio](https://github.com/Black-Blue-russia/Digital-ECG-signal-with-STM32F401/assets/65806300/fb7410d2-b3ab-43e9-8b73-9b20ec29295b)

