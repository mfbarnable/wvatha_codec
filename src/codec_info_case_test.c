#include "codec_info.h"
#include <libavformat/avformat.h>


wvatha_err
get_codec_info_ffile_with_absent_header() {
    /*handle the path for ios and android too.*/
    AVFormatContext *p_format_ctx = avformat_alloc_context();
    avformat_open_input(&p_format_ctx, )
    // The stream must be closed with avformat_close_input().
}