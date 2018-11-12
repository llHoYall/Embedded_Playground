# ALSA

ALSA를 사용한 오디오 프로그래밍.

ALSA는 amixer, alsamixer, alsactl, aplay 등의 유틸리티를 제공한다.

* 현재 시스템의 사운드에 대한 정보를 보여준다.
	> $ cat /dev/sndstat
* 현재 시스템에서 지원하는 인터페이스들을 보여준다.
	> $ cat /proc/asound/devices
* 시스템에 연결된 오디오 디바이스를 보여준다.
	> $ cat /proc/asound/cards
* ALSA의 현재 상태를 보여준다.
	> $ cat /var/lib/alsa/asound.state
* RaspberryPi의 speaker를 test한다. White noise가 나온다.
	> $ speaker-test
* `-c#` 옵션을 추가하면 녹음을 한다.
	> $ amixer -c#

## Installation

> $ sudo apt-get install libasound2-dev

## API

[ALSA API](http://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#ga8340c7dc0ac37f37afe5e7c21d6c528b)

### Opens a PCM.

```c
int snd_pcm_open(
  snd_pcm_t** pcmp,    // returned PCM handle
  const char* name,    // ASCII identifier of the PCM handle
  snd_pcm_stream_t stream,    // wanted stream
  int mode    // open mode (SND_PCM_NONBLOCK, SND_PCM_ASYNC)
)
```

### Prepare PCM for use.

```c
int snd_pcm_prepare(
  snd_pcm_t* pcm    // PCM handle
)
```

### Write inrerleaved frames to a PCM.

```c
snd_pcm_sframes_t snd_pcm_writei(
  snd_pcm_t** pcm,    // PCM handle
  const void* buffer,    // frames containing buffer
  snd_pcm_uframes_t size    // frames to be written
)
```

### Stop a PCM dropping pending frames.

```c
int snd_pcm_drop(
  snd_pcm_t* pcm    // PCM handle
)
```

### Close PCM handle

```c
int snd_pcm_close(
  snd_pcm_t* pcm    // PCM handle
)
```

## Example

### Dependencies

* asound library (`-lasound`)
* Math library (`-lm`)

```c
/* playback.c */

#include <sdtio.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#inlcude <sys/ioctl.h>
#include <asla/asoundlib.h>    // /usr/include/alsa

#define FREQ 44100    // 44.1KHz sampling rate
#define BITS 2    // 16bit qunatization
#define MODE 1    // mono channel
#define DURATION 5.0    // sec
#define FRAGMENT 8
#define BUFSIZE (int)(FREQ * BITS * MODE * DURATION)

int setupDSP(snd_pcm_t* _dev, int _bufSize, int _fmt, int _sampleRate, int _ch);

int main(int argc, char* argv[]) {
  snd_pcm_t*handle_audio;
  char* snd_dev_out = "plughw:0,0";
  if (snd_pcm_open(&handle_audio, snd_dev_out, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
    perror("Could not open output audio device");
    return -1;
  }

  if (setupDSP(handle_audio, BUFSIZE, SND_PCM_FORMAT_S16_LE, FREQ, MODE) < 0) {
    perror("Could not set output audio device");
    return -1;
  }

  int i;
  double t;
  double total = DURATION;
  short buf[BUFSIZE];
  int freq = 440;
  int frames;
  printf("Make Sine Wave!!!\n");
  for (i = 0; i < BUFSIZE; ++i) {
    t = (total / BUFSIZE) * i;
    buf[i] = SHRT_MAX * sin(int(2.0 * M_PI * freq * t));
  }
  frames = BUFSIZE / (MODE * BITS);

  int count = 1;
  while (count--) {
    snd_pcm_prepare(handle_audio);
    snd_pcm_writei(handle_audio, buf, frames);
  }

  snd_pcm_drop(handle_audio);

  snd_pcm_close(handle_audio);

  return 0;
}

int setupDSP(snd_pcm_t* _dev, int _bufSize, int _fmt, int_sampleRate, int _ch) {
  snd_pcm_hw_params_t* hw_params;
  snd_pcm_uframes_t frames;
  int fragments = FRAGMENT;
  int bits = (_fmt == SND_PCM_FORMAT_S16_LE) ? 2 : 1;

  if (snd_pcm_hw_params_malloc(&hw_params) < 0) {
    perror("Could not allocate parameter");
    return -1;
  }

  if (snd_pcm_hw_params_any(_dev, hw_params) < 0) {
    perror("Could not initialize parameter");
    return -1;
  }

  if (snd_pcm_hw_params_set_access(_dev, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
    perror("Could not set access type");
    return -1;
    }

  if (snd_pcm_hw_params_set_format(_dev, hw_params, _fmt) < 0) {
    perror("Could not set sample format");
    return -1;
  }

  if (snd_pcm_hw_params_set_rate_near(_dev, hw_params, &_sampleRate, 0) < 0) {
    perror("Could not set sample rate");
    return -1;
  }

  if (snd_pcm_hw_params_set_channels(_dev, hw_params, _ch) < 0) {
    perror("Could not set channel count");
    return -1;
  }

  if (snd_pcm_hw_params_set_periods_near(_dev, hw_params, &fragments, 0) < 0) {
    perror("Could not set fragments");
    return -1;
  }

  frames = (_bufSize * fragments) / _ch * bits;
  if (snd_pcm_hw_params_set_buffer_size_near(_dev, hw_params, &frames) < 0) {
    perror("Could not set buffer size");
    return -1;
  }
  _bufSize = frames * _ch * bits / fragments;

  if (snd_pcm_hw_params(_dev, hw_params) < 0) {
    perror("Could not set HW params");
    return -1;
  }

  return 0;
}
```

```c
/* capture.c */

int main(int argc, char* argv[]) {
  snd_pcm_t*handle_audio;
  if (snd_pcm_open(&handle_audio, ..., SND_PCM_STREAM_CAPTURE, 0)) < 0) {
    perror("Could not open input audio device");
    return -1;
  }

  snd_pcm_hw_params_t* hw_params;
  if (snd_pcm_hw_params_malloc(&hw_params) < 0) {
    perror("Could not allocate parameter");
    return -1;
  }

  if (snd_pcm_hw_params_any(handle_audio, hw_params) < 0) {
    perror("Could not initialize parameter");
    return -1;
  }

  if (snd_pcm_hw_params_set_access(handle_audio, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
    perror("Could not set access type");
    return -1;
    }

  if (snd_pcm_hw_params_set_format(handle_audio, hw_params, SND_PCM_FORMAT_S16_LE) < 0) {
    perror("Could not set sample format");
    return -1;
  }

  if (snd_pcm_hw_params_set_rate_near(handle_audio, hw_params, FREQ, 0) < 0) {
    perror("Could not set sample rate");
    return -1;
  }

  if (snd_pcm_hw_params_set_channels(handle_audio, hw_params, MODE) < 0) {
    perror("Could not set channel count");
    return -1;
  }

  if (snd_pcm_hw_params(handle_audio, hw_params) < 0) {
    perror("Could not set HW params");
    return -1;
  }

  snd_pcm_hw_params_free(hw_params);

  snd_pcm_prepare(handle_audio);

  snd_pcm_readi(handle_audio, buf, frames);

  return 0;
}
```

```c
/* alsa_mixer.c */

#include <stdio.h>
#include <alsa/asoundlib.h>

int main(int argc, char* argv[]) {
  snd_mixer_t* mixer;
  snd_mixer_elem_t* elem;
  snd_mixer_selem_id_t* id;
  int status;
  long maxVal = 100;
  long minVal = 0;
  long outVal = 50;

  static const char* mix_name = "PCM";
  static const char* card = "default";
  static int mix_index = 0;

  snd_mixer_open(&mixer, 0);
  snd_mixer_attach(mixer, card);
  snd_mixer_selem_register(mixer, NULL, NULL);
  snd_mixer_load(mixer);
  snd_mixer_selem_id_alloca(&id);
  snd_mixer_selem_id_set_index(id, mix_index);
  snd_mixer_selem_id_set_name(id, mix_name);
  elem = snd_mixer_find_selem(mixer, id);
  outVal = (outVal * (maxVal - minVal) / (long)(100 - 1)) + minVal;
  snd_mixer_selem_set_playback_volume_range(elem, minVal, maxVal);
  snd_mixer_selem_set_playback_volume_all(elem, outVal);
  snd_mixer_selem_get_playback_volume_range(elem, &minVal, &maxVal);
  fprintf(stderr, "Set volume %i(%d/%d)\n", outVal, maxVal, minVal);
  snd_mixer_close(mixer);

  return 0;
}
```
