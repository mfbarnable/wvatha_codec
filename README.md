# wvatha_codec


/*
We're going to allocate memory to the component AVFormatContext that will hold information about the format (container).

AVFormatContext *pFormatContext = avformat_alloc_context();

Now we're going to open the file and read its header and fill the AVFormatContext with minimal information about the format (notice that usually the codecs are not opened). The function used to do this is avformat_open_input. It expects an AVFormatContext, a filename and two optional arguments: the AVInputFormat (if you pass NULL, FFmpeg will guess the format) and the AVDictionary (which are the options to the demuxer).

avformat_open_input(&pFormatContext, filename, NULL, NULL);

We can print the format name and the media duration:

printf("Format %s, duration %lld us", pFormatContext->iformat->long_name, pFormatContext->duration);


To access the streams, we need to read data from the media. The function avformat_find_stream_info does that. Now, the pFormatContext->nb_streams will hold the amount of streams and the pFormatContext->streams[i] will give us the i stream (an AVStream).

avformat_find_stream_info(pFormatContext,  NULL);


Now we'll loop through all the streams.

for (int i = 0; i < pFormatContext->nb_streams; i++)
{
  //
}

For each stream, we're going to keep the AVCodecParameters, which describes the properties of a codec used by the stream i.

AVCodecParameters *pLocalCodecParameters = pFormatContext->streams[i]->codecpar;

With the codec properties we can look up the proper CODEC querying the function avcodec_find_decoder and find the registered decoder for the codec id and return an AVCodec, the component that knows how to enCOde and DECode the stream.

AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

Now we can print information about the codecs.

// specific for video and audio
if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
  printf("Video Codec: resolution %d x %d", pLocalCodecParameters->width, pLocalCodecParameters->height);
} else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
  printf("Audio Codec: %d channels, sample rate %d", pLocalCodecParameters->channels, pLocalCodecParameters->sample_rate);
}
// general
printf("\tCodec %s ID %d bit_rate %lld", pLocalCodec->long_name, pLocalCodec->id, pLocalCodecParameters->bit_rate);

*/