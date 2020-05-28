; Copyright (c) 2018, Google Inc.
;
; Permission to use, copy, modify, and/or distribute this software for any
; purpose with or without fee is hereby granted, provided that the above
; copyright notice and this permission notice appear in all copies.
;
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
; WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
; MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
; SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
; WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
; OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
; CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

; 32-bit Windows adds underscores to C functions, while 64-bit Windows does not.
%ifidn __OUTPUT_FORMAT__, win32
%xdefine _ACCESS_DESCRIPTION_free _ %+ XCRYPTO_PREFIX %+ _ACCESS_DESCRIPTION_free
%xdefine _ACCESS_DESCRIPTION_it _ %+ XCRYPTO_PREFIX %+ _ACCESS_DESCRIPTION_it
%xdefine _ACCESS_DESCRIPTION_new _ %+ XCRYPTO_PREFIX %+ _ACCESS_DESCRIPTION_new
%xdefine _AES_CMAC _ %+ XCRYPTO_PREFIX %+ _AES_CMAC
%xdefine _AES_cbc_encrypt _ %+ XCRYPTO_PREFIX %+ _AES_cbc_encrypt
%xdefine _AES_cfb128_encrypt _ %+ XCRYPTO_PREFIX %+ _AES_cfb128_encrypt
%xdefine _AES_ctr128_encrypt _ %+ XCRYPTO_PREFIX %+ _AES_ctr128_encrypt
%xdefine _AES_decrypt _ %+ XCRYPTO_PREFIX %+ _AES_decrypt
%xdefine _AES_ecb_encrypt _ %+ XCRYPTO_PREFIX %+ _AES_ecb_encrypt
%xdefine _AES_encrypt _ %+ XCRYPTO_PREFIX %+ _AES_encrypt
%xdefine _AES_ofb128_encrypt _ %+ XCRYPTO_PREFIX %+ _AES_ofb128_encrypt
%xdefine _AES_set_decrypt_key _ %+ XCRYPTO_PREFIX %+ _AES_set_decrypt_key
%xdefine _AES_set_encrypt_key _ %+ XCRYPTO_PREFIX %+ _AES_set_encrypt_key
%xdefine _AES_unwrap_key _ %+ XCRYPTO_PREFIX %+ _AES_unwrap_key
%xdefine _AES_unwrap_key_padded _ %+ XCRYPTO_PREFIX %+ _AES_unwrap_key_padded
%xdefine _AES_wrap_key _ %+ XCRYPTO_PREFIX %+ _AES_wrap_key
%xdefine _AES_wrap_key_padded _ %+ XCRYPTO_PREFIX %+ _AES_wrap_key_padded
%xdefine _ASN1_ANY_it _ %+ XCRYPTO_PREFIX %+ _ASN1_ANY_it
%xdefine _ASN1_BIT_STRING_check _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_check
%xdefine _ASN1_BIT_STRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_free
%xdefine _ASN1_BIT_STRING_get_bit _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_get_bit
%xdefine _ASN1_BIT_STRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_it
%xdefine _ASN1_BIT_STRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_new
%xdefine _ASN1_BIT_STRING_set _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_set
%xdefine _ASN1_BIT_STRING_set_bit _ %+ XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_set_bit
%xdefine _ASN1_BMPSTRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_BMPSTRING_free
%xdefine _ASN1_BMPSTRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_BMPSTRING_it
%xdefine _ASN1_BMPSTRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_BMPSTRING_new
%xdefine _ASN1_BOOLEAN_it _ %+ XCRYPTO_PREFIX %+ _ASN1_BOOLEAN_it
%xdefine _ASN1_ENUMERATED_free _ %+ XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_free
%xdefine _ASN1_ENUMERATED_get _ %+ XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_get
%xdefine _ASN1_ENUMERATED_it _ %+ XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_it
%xdefine _ASN1_ENUMERATED_new _ %+ XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_new
%xdefine _ASN1_ENUMERATED_set _ %+ XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_set
%xdefine _ASN1_ENUMERATED_to_BN _ %+ XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_to_BN
%xdefine _ASN1_FBOOLEAN_it _ %+ XCRYPTO_PREFIX %+ _ASN1_FBOOLEAN_it
%xdefine _ASN1_GENERALIZEDTIME_adj _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_adj
%xdefine _ASN1_GENERALIZEDTIME_check _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_check
%xdefine _ASN1_GENERALIZEDTIME_free _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_free
%xdefine _ASN1_GENERALIZEDTIME_it _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_it
%xdefine _ASN1_GENERALIZEDTIME_new _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_new
%xdefine _ASN1_GENERALIZEDTIME_print _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_print
%xdefine _ASN1_GENERALIZEDTIME_set _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_set
%xdefine _ASN1_GENERALIZEDTIME_set_string _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_set_string
%xdefine _ASN1_GENERALSTRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALSTRING_free
%xdefine _ASN1_GENERALSTRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALSTRING_it
%xdefine _ASN1_GENERALSTRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_GENERALSTRING_new
%xdefine _ASN1_IA5STRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_IA5STRING_free
%xdefine _ASN1_IA5STRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_IA5STRING_it
%xdefine _ASN1_IA5STRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_IA5STRING_new
%xdefine _ASN1_INTEGER_cmp _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_cmp
%xdefine _ASN1_INTEGER_dup _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_dup
%xdefine _ASN1_INTEGER_free _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_free
%xdefine _ASN1_INTEGER_get _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_get
%xdefine _ASN1_INTEGER_it _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_it
%xdefine _ASN1_INTEGER_new _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_new
%xdefine _ASN1_INTEGER_set _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_set
%xdefine _ASN1_INTEGER_set_uint64 _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_set_uint64
%xdefine _ASN1_INTEGER_to_BN _ %+ XCRYPTO_PREFIX %+ _ASN1_INTEGER_to_BN
%xdefine _ASN1_NULL_free _ %+ XCRYPTO_PREFIX %+ _ASN1_NULL_free
%xdefine _ASN1_NULL_it _ %+ XCRYPTO_PREFIX %+ _ASN1_NULL_it
%xdefine _ASN1_NULL_new _ %+ XCRYPTO_PREFIX %+ _ASN1_NULL_new
%xdefine _ASN1_OBJECT_create _ %+ XCRYPTO_PREFIX %+ _ASN1_OBJECT_create
%xdefine _ASN1_OBJECT_free _ %+ XCRYPTO_PREFIX %+ _ASN1_OBJECT_free
%xdefine _ASN1_OBJECT_it _ %+ XCRYPTO_PREFIX %+ _ASN1_OBJECT_it
%xdefine _ASN1_OBJECT_new _ %+ XCRYPTO_PREFIX %+ _ASN1_OBJECT_new
%xdefine _ASN1_OCTET_STRING_NDEF_it _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_NDEF_it
%xdefine _ASN1_OCTET_STRING_cmp _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_cmp
%xdefine _ASN1_OCTET_STRING_dup _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_dup
%xdefine _ASN1_OCTET_STRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_free
%xdefine _ASN1_OCTET_STRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_it
%xdefine _ASN1_OCTET_STRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_new
%xdefine _ASN1_OCTET_STRING_set _ %+ XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_set
%xdefine _ASN1_PRINTABLESTRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLESTRING_free
%xdefine _ASN1_PRINTABLESTRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLESTRING_it
%xdefine _ASN1_PRINTABLESTRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLESTRING_new
%xdefine _ASN1_PRINTABLE_free _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_free
%xdefine _ASN1_PRINTABLE_it _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_it
%xdefine _ASN1_PRINTABLE_new _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_new
%xdefine _ASN1_PRINTABLE_type _ %+ XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_type
%xdefine _ASN1_SEQUENCE_ANY_it _ %+ XCRYPTO_PREFIX %+ _ASN1_SEQUENCE_ANY_it
%xdefine _ASN1_SEQUENCE_it _ %+ XCRYPTO_PREFIX %+ _ASN1_SEQUENCE_it
%xdefine _ASN1_SET_ANY_it _ %+ XCRYPTO_PREFIX %+ _ASN1_SET_ANY_it
%xdefine _ASN1_STRING_TABLE_add _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_TABLE_add
%xdefine _ASN1_STRING_TABLE_cleanup _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_TABLE_cleanup
%xdefine _ASN1_STRING_TABLE_get _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_TABLE_get
%xdefine _ASN1_STRING_cmp _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_cmp
%xdefine _ASN1_STRING_copy _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_copy
%xdefine _ASN1_STRING_data _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_data
%xdefine _ASN1_STRING_dup _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_dup
%xdefine _ASN1_STRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_free
%xdefine _ASN1_STRING_get0_data _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_get0_data
%xdefine _ASN1_STRING_get_default_mask _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_get_default_mask
%xdefine _ASN1_STRING_length _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_length
%xdefine _ASN1_STRING_length_set _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_length_set
%xdefine _ASN1_STRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_new
%xdefine _ASN1_STRING_print _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_print
%xdefine _ASN1_STRING_print_ex _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_print_ex
%xdefine _ASN1_STRING_print_ex_fp _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_print_ex_fp
%xdefine _ASN1_STRING_set _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_set
%xdefine _ASN1_STRING_set0 _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_set0
%xdefine _ASN1_STRING_set_by_NID _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_set_by_NID
%xdefine _ASN1_STRING_set_default_mask _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_set_default_mask
%xdefine _ASN1_STRING_set_default_mask_asc _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_set_default_mask_asc
%xdefine _ASN1_STRING_to_UTF8 _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_to_UTF8
%xdefine _ASN1_STRING_type _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_type
%xdefine _ASN1_STRING_type_new _ %+ XCRYPTO_PREFIX %+ _ASN1_STRING_type_new
%xdefine _ASN1_T61STRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_T61STRING_free
%xdefine _ASN1_T61STRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_T61STRING_it
%xdefine _ASN1_T61STRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_T61STRING_new
%xdefine _ASN1_TBOOLEAN_it _ %+ XCRYPTO_PREFIX %+ _ASN1_TBOOLEAN_it
%xdefine _ASN1_TIME_adj _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_adj
%xdefine _ASN1_TIME_check _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_check
%xdefine _ASN1_TIME_diff _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_diff
%xdefine _ASN1_TIME_free _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_free
%xdefine _ASN1_TIME_it _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_it
%xdefine _ASN1_TIME_new _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_new
%xdefine _ASN1_TIME_print _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_print
%xdefine _ASN1_TIME_set _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_set
%xdefine _ASN1_TIME_set_string _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_set_string
%xdefine _ASN1_TIME_to_generalizedtime _ %+ XCRYPTO_PREFIX %+ _ASN1_TIME_to_generalizedtime
%xdefine _ASN1_TYPE_cmp _ %+ XCRYPTO_PREFIX %+ _ASN1_TYPE_cmp
%xdefine _ASN1_TYPE_free _ %+ XCRYPTO_PREFIX %+ _ASN1_TYPE_free
%xdefine _ASN1_TYPE_get _ %+ XCRYPTO_PREFIX %+ _ASN1_TYPE_get
%xdefine _ASN1_TYPE_new _ %+ XCRYPTO_PREFIX %+ _ASN1_TYPE_new
%xdefine _ASN1_TYPE_set _ %+ XCRYPTO_PREFIX %+ _ASN1_TYPE_set
%xdefine _ASN1_TYPE_set1 _ %+ XCRYPTO_PREFIX %+ _ASN1_TYPE_set1
%xdefine _ASN1_UNIVERSALSTRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_UNIVERSALSTRING_free
%xdefine _ASN1_UNIVERSALSTRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_UNIVERSALSTRING_it
%xdefine _ASN1_UNIVERSALSTRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_UNIVERSALSTRING_new
%xdefine _ASN1_UTCTIME_adj _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_adj
%xdefine _ASN1_UTCTIME_check _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_check
%xdefine _ASN1_UTCTIME_cmp_time_t _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_cmp_time_t
%xdefine _ASN1_UTCTIME_free _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_free
%xdefine _ASN1_UTCTIME_it _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_it
%xdefine _ASN1_UTCTIME_new _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_new
%xdefine _ASN1_UTCTIME_print _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_print
%xdefine _ASN1_UTCTIME_set _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_set
%xdefine _ASN1_UTCTIME_set_string _ %+ XCRYPTO_PREFIX %+ _ASN1_UTCTIME_set_string
%xdefine _ASN1_UTF8STRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_UTF8STRING_free
%xdefine _ASN1_UTF8STRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_UTF8STRING_it
%xdefine _ASN1_UTF8STRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_UTF8STRING_new
%xdefine _ASN1_VISIBLESTRING_free _ %+ XCRYPTO_PREFIX %+ _ASN1_VISIBLESTRING_free
%xdefine _ASN1_VISIBLESTRING_it _ %+ XCRYPTO_PREFIX %+ _ASN1_VISIBLESTRING_it
%xdefine _ASN1_VISIBLESTRING_new _ %+ XCRYPTO_PREFIX %+ _ASN1_VISIBLESTRING_new
%xdefine _ASN1_digest _ %+ XCRYPTO_PREFIX %+ _ASN1_digest
%xdefine _ASN1_generate_nconf _ %+ XCRYPTO_PREFIX %+ _ASN1_generate_nconf
%xdefine _ASN1_generate_v3 _ %+ XCRYPTO_PREFIX %+ _ASN1_generate_v3
%xdefine _ASN1_get_object _ %+ XCRYPTO_PREFIX %+ _ASN1_get_object
%xdefine _ASN1_item_d2i _ %+ XCRYPTO_PREFIX %+ _ASN1_item_d2i
%xdefine _ASN1_item_d2i_bio _ %+ XCRYPTO_PREFIX %+ _ASN1_item_d2i_bio
%xdefine _ASN1_item_d2i_fp _ %+ XCRYPTO_PREFIX %+ _ASN1_item_d2i_fp
%xdefine _ASN1_item_digest _ %+ XCRYPTO_PREFIX %+ _ASN1_item_digest
%xdefine _ASN1_item_dup _ %+ XCRYPTO_PREFIX %+ _ASN1_item_dup
%xdefine _ASN1_item_ex_d2i _ %+ XCRYPTO_PREFIX %+ _ASN1_item_ex_d2i
%xdefine _ASN1_item_ex_free _ %+ XCRYPTO_PREFIX %+ _ASN1_item_ex_free
%xdefine _ASN1_item_ex_i2d _ %+ XCRYPTO_PREFIX %+ _ASN1_item_ex_i2d
%xdefine _ASN1_item_ex_new _ %+ XCRYPTO_PREFIX %+ _ASN1_item_ex_new
%xdefine _ASN1_item_free _ %+ XCRYPTO_PREFIX %+ _ASN1_item_free
%xdefine _ASN1_item_i2d _ %+ XCRYPTO_PREFIX %+ _ASN1_item_i2d
%xdefine _ASN1_item_i2d_bio _ %+ XCRYPTO_PREFIX %+ _ASN1_item_i2d_bio
%xdefine _ASN1_item_i2d_fp _ %+ XCRYPTO_PREFIX %+ _ASN1_item_i2d_fp
%xdefine _ASN1_item_ndef_i2d _ %+ XCRYPTO_PREFIX %+ _ASN1_item_ndef_i2d
%xdefine _ASN1_item_new _ %+ XCRYPTO_PREFIX %+ _ASN1_item_new
%xdefine _ASN1_item_pack _ %+ XCRYPTO_PREFIX %+ _ASN1_item_pack
%xdefine _ASN1_item_sign _ %+ XCRYPTO_PREFIX %+ _ASN1_item_sign
%xdefine _ASN1_item_sign_ctx _ %+ XCRYPTO_PREFIX %+ _ASN1_item_sign_ctx
%xdefine _ASN1_item_unpack _ %+ XCRYPTO_PREFIX %+ _ASN1_item_unpack
%xdefine _ASN1_item_verify _ %+ XCRYPTO_PREFIX %+ _ASN1_item_verify
%xdefine _ASN1_mbstring_copy _ %+ XCRYPTO_PREFIX %+ _ASN1_mbstring_copy
%xdefine _ASN1_mbstring_ncopy _ %+ XCRYPTO_PREFIX %+ _ASN1_mbstring_ncopy
%xdefine _ASN1_object_size _ %+ XCRYPTO_PREFIX %+ _ASN1_object_size
%xdefine _ASN1_primitive_free _ %+ XCRYPTO_PREFIX %+ _ASN1_primitive_free
%xdefine _ASN1_primitive_new _ %+ XCRYPTO_PREFIX %+ _ASN1_primitive_new
%xdefine _ASN1_put_eoc _ %+ XCRYPTO_PREFIX %+ _ASN1_put_eoc
%xdefine _ASN1_put_object _ %+ XCRYPTO_PREFIX %+ _ASN1_put_object
%xdefine _ASN1_tag2bit _ %+ XCRYPTO_PREFIX %+ _ASN1_tag2bit
%xdefine _ASN1_tag2str _ %+ XCRYPTO_PREFIX %+ _ASN1_tag2str
%xdefine _ASN1_template_free _ %+ XCRYPTO_PREFIX %+ _ASN1_template_free
%xdefine _ASN1_template_new _ %+ XCRYPTO_PREFIX %+ _ASN1_template_new
%xdefine _AUTHORITY_INFO_ACCESS_free _ %+ XCRYPTO_PREFIX %+ _AUTHORITY_INFO_ACCESS_free
%xdefine _AUTHORITY_INFO_ACCESS_it _ %+ XCRYPTO_PREFIX %+ _AUTHORITY_INFO_ACCESS_it
%xdefine _AUTHORITY_INFO_ACCESS_new _ %+ XCRYPTO_PREFIX %+ _AUTHORITY_INFO_ACCESS_new
%xdefine _AUTHORITY_KEYID_free _ %+ XCRYPTO_PREFIX %+ _AUTHORITY_KEYID_free
%xdefine _AUTHORITY_KEYID_it _ %+ XCRYPTO_PREFIX %+ _AUTHORITY_KEYID_it
%xdefine _AUTHORITY_KEYID_new _ %+ XCRYPTO_PREFIX %+ _AUTHORITY_KEYID_new
%xdefine _BASIC_CONSTRAINTS_free _ %+ XCRYPTO_PREFIX %+ _BASIC_CONSTRAINTS_free
%xdefine _BASIC_CONSTRAINTS_it _ %+ XCRYPTO_PREFIX %+ _BASIC_CONSTRAINTS_it
%xdefine _BASIC_CONSTRAINTS_new _ %+ XCRYPTO_PREFIX %+ _BASIC_CONSTRAINTS_new
%xdefine _BIO_append_filename _ %+ XCRYPTO_PREFIX %+ _BIO_append_filename
%xdefine _BIO_callback_ctrl _ %+ XCRYPTO_PREFIX %+ _BIO_callback_ctrl
%xdefine _BIO_clear_flags _ %+ XCRYPTO_PREFIX %+ _BIO_clear_flags
%xdefine _BIO_clear_retry_flags _ %+ XCRYPTO_PREFIX %+ _BIO_clear_retry_flags
%xdefine _BIO_copy_next_retry _ %+ XCRYPTO_PREFIX %+ _BIO_copy_next_retry
%xdefine _BIO_ctrl _ %+ XCRYPTO_PREFIX %+ _BIO_ctrl
%xdefine _BIO_ctrl_get_read_request _ %+ XCRYPTO_PREFIX %+ _BIO_ctrl_get_read_request
%xdefine _BIO_ctrl_get_write_guarantee _ %+ XCRYPTO_PREFIX %+ _BIO_ctrl_get_write_guarantee
%xdefine _BIO_ctrl_pending _ %+ XCRYPTO_PREFIX %+ _BIO_ctrl_pending
%xdefine _BIO_do_connect _ %+ XCRYPTO_PREFIX %+ _BIO_do_connect
%xdefine _BIO_eof _ %+ XCRYPTO_PREFIX %+ _BIO_eof
%xdefine _BIO_f_ssl _ %+ XCRYPTO_PREFIX %+ _BIO_f_ssl
%xdefine _BIO_find_type _ %+ XCRYPTO_PREFIX %+ _BIO_find_type
%xdefine _BIO_flush _ %+ XCRYPTO_PREFIX %+ _BIO_flush
%xdefine _BIO_free _ %+ XCRYPTO_PREFIX %+ _BIO_free
%xdefine _BIO_free_all _ %+ XCRYPTO_PREFIX %+ _BIO_free_all
%xdefine _BIO_get_data _ %+ XCRYPTO_PREFIX %+ _BIO_get_data
%xdefine _BIO_get_fd _ %+ XCRYPTO_PREFIX %+ _BIO_get_fd
%xdefine _BIO_get_fp _ %+ XCRYPTO_PREFIX %+ _BIO_get_fp
%xdefine _BIO_get_init _ %+ XCRYPTO_PREFIX %+ _BIO_get_init
%xdefine _BIO_get_mem_data _ %+ XCRYPTO_PREFIX %+ _BIO_get_mem_data
%xdefine _BIO_get_mem_ptr _ %+ XCRYPTO_PREFIX %+ _BIO_get_mem_ptr
%xdefine _BIO_get_new_index _ %+ XCRYPTO_PREFIX %+ _BIO_get_new_index
%xdefine _BIO_get_retry_flags _ %+ XCRYPTO_PREFIX %+ _BIO_get_retry_flags
%xdefine _BIO_get_retry_reason _ %+ XCRYPTO_PREFIX %+ _BIO_get_retry_reason
%xdefine _BIO_get_shutdown _ %+ XCRYPTO_PREFIX %+ _BIO_get_shutdown
%xdefine _BIO_gets _ %+ XCRYPTO_PREFIX %+ _BIO_gets
%xdefine _BIO_hexdump _ %+ XCRYPTO_PREFIX %+ _BIO_hexdump
%xdefine _BIO_indent _ %+ XCRYPTO_PREFIX %+ _BIO_indent
%xdefine _BIO_int_ctrl _ %+ XCRYPTO_PREFIX %+ _BIO_int_ctrl
%xdefine _BIO_mem_contents _ %+ XCRYPTO_PREFIX %+ _BIO_mem_contents
%xdefine _BIO_meth_free _ %+ XCRYPTO_PREFIX %+ _BIO_meth_free
%xdefine _BIO_meth_new _ %+ XCRYPTO_PREFIX %+ _BIO_meth_new
%xdefine _BIO_meth_set_create _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_create
%xdefine _BIO_meth_set_ctrl _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_ctrl
%xdefine _BIO_meth_set_destroy _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_destroy
%xdefine _BIO_meth_set_gets _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_gets
%xdefine _BIO_meth_set_puts _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_puts
%xdefine _BIO_meth_set_read _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_read
%xdefine _BIO_meth_set_write _ %+ XCRYPTO_PREFIX %+ _BIO_meth_set_write
%xdefine _BIO_method_type _ %+ XCRYPTO_PREFIX %+ _BIO_method_type
%xdefine _BIO_new _ %+ XCRYPTO_PREFIX %+ _BIO_new
%xdefine _BIO_new_bio_pair _ %+ XCRYPTO_PREFIX %+ _BIO_new_bio_pair
%xdefine _BIO_new_connect _ %+ XCRYPTO_PREFIX %+ _BIO_new_connect
%xdefine _BIO_new_fd _ %+ XCRYPTO_PREFIX %+ _BIO_new_fd
%xdefine _BIO_new_file _ %+ XCRYPTO_PREFIX %+ _BIO_new_file
%xdefine _BIO_new_fp _ %+ XCRYPTO_PREFIX %+ _BIO_new_fp
%xdefine _BIO_new_mem_buf _ %+ XCRYPTO_PREFIX %+ _BIO_new_mem_buf
%xdefine _BIO_new_socket _ %+ XCRYPTO_PREFIX %+ _BIO_new_socket
%xdefine _BIO_next _ %+ XCRYPTO_PREFIX %+ _BIO_next
%xdefine _BIO_number_read _ %+ XCRYPTO_PREFIX %+ _BIO_number_read
%xdefine _BIO_number_written _ %+ XCRYPTO_PREFIX %+ _BIO_number_written
%xdefine _BIO_pending _ %+ XCRYPTO_PREFIX %+ _BIO_pending
%xdefine _BIO_pop _ %+ XCRYPTO_PREFIX %+ _BIO_pop
%xdefine _BIO_printf _ %+ XCRYPTO_PREFIX %+ _BIO_printf
%xdefine _BIO_ptr_ctrl _ %+ XCRYPTO_PREFIX %+ _BIO_ptr_ctrl
%xdefine _BIO_push _ %+ XCRYPTO_PREFIX %+ _BIO_push
%xdefine _BIO_puts _ %+ XCRYPTO_PREFIX %+ _BIO_puts
%xdefine _BIO_read _ %+ XCRYPTO_PREFIX %+ _BIO_read
%xdefine _BIO_read_asn1 _ %+ XCRYPTO_PREFIX %+ _BIO_read_asn1
%xdefine _BIO_read_filename _ %+ XCRYPTO_PREFIX %+ _BIO_read_filename
%xdefine _BIO_reset _ %+ XCRYPTO_PREFIX %+ _BIO_reset
%xdefine _BIO_rw_filename _ %+ XCRYPTO_PREFIX %+ _BIO_rw_filename
%xdefine _BIO_s_connect _ %+ XCRYPTO_PREFIX %+ _BIO_s_connect
%xdefine _BIO_s_fd _ %+ XCRYPTO_PREFIX %+ _BIO_s_fd
%xdefine _BIO_s_file _ %+ XCRYPTO_PREFIX %+ _BIO_s_file
%xdefine _BIO_s_mem _ %+ XCRYPTO_PREFIX %+ _BIO_s_mem
%xdefine _BIO_s_socket _ %+ XCRYPTO_PREFIX %+ _BIO_s_socket
%xdefine _BIO_set_close _ %+ XCRYPTO_PREFIX %+ _BIO_set_close
%xdefine _BIO_set_conn_hostname _ %+ XCRYPTO_PREFIX %+ _BIO_set_conn_hostname
%xdefine _BIO_set_conn_int_port _ %+ XCRYPTO_PREFIX %+ _BIO_set_conn_int_port
%xdefine _BIO_set_conn_port _ %+ XCRYPTO_PREFIX %+ _BIO_set_conn_port
%xdefine _BIO_set_data _ %+ XCRYPTO_PREFIX %+ _BIO_set_data
%xdefine _BIO_set_fd _ %+ XCRYPTO_PREFIX %+ _BIO_set_fd
%xdefine _BIO_set_flags _ %+ XCRYPTO_PREFIX %+ _BIO_set_flags
%xdefine _BIO_set_fp _ %+ XCRYPTO_PREFIX %+ _BIO_set_fp
%xdefine _BIO_set_init _ %+ XCRYPTO_PREFIX %+ _BIO_set_init
%xdefine _BIO_set_mem_buf _ %+ XCRYPTO_PREFIX %+ _BIO_set_mem_buf
%xdefine _BIO_set_mem_eof_return _ %+ XCRYPTO_PREFIX %+ _BIO_set_mem_eof_return
%xdefine _BIO_set_nbio _ %+ XCRYPTO_PREFIX %+ _BIO_set_nbio
%xdefine _BIO_set_retry_read _ %+ XCRYPTO_PREFIX %+ _BIO_set_retry_read
%xdefine _BIO_set_retry_special _ %+ XCRYPTO_PREFIX %+ _BIO_set_retry_special
%xdefine _BIO_set_retry_write _ %+ XCRYPTO_PREFIX %+ _BIO_set_retry_write
%xdefine _BIO_set_shutdown _ %+ XCRYPTO_PREFIX %+ _BIO_set_shutdown
%xdefine _BIO_set_ssl _ %+ XCRYPTO_PREFIX %+ _BIO_set_ssl
%xdefine _BIO_set_write_buffer_size _ %+ XCRYPTO_PREFIX %+ _BIO_set_write_buffer_size
%xdefine _BIO_should_io_special _ %+ XCRYPTO_PREFIX %+ _BIO_should_io_special
%xdefine _BIO_should_read _ %+ XCRYPTO_PREFIX %+ _BIO_should_read
%xdefine _BIO_should_retry _ %+ XCRYPTO_PREFIX %+ _BIO_should_retry
%xdefine _BIO_should_write _ %+ XCRYPTO_PREFIX %+ _BIO_should_write
%xdefine _BIO_shutdown_wr _ %+ XCRYPTO_PREFIX %+ _BIO_shutdown_wr
%xdefine _BIO_snprintf _ %+ XCRYPTO_PREFIX %+ _BIO_snprintf
%xdefine _BIO_test_flags _ %+ XCRYPTO_PREFIX %+ _BIO_test_flags
%xdefine _BIO_up_ref _ %+ XCRYPTO_PREFIX %+ _BIO_up_ref
%xdefine _BIO_vfree _ %+ XCRYPTO_PREFIX %+ _BIO_vfree
%xdefine _BIO_vsnprintf _ %+ XCRYPTO_PREFIX %+ _BIO_vsnprintf
%xdefine _BIO_wpending _ %+ XCRYPTO_PREFIX %+ _BIO_wpending
%xdefine _BIO_write _ %+ XCRYPTO_PREFIX %+ _BIO_write
%xdefine _BIO_write_all _ %+ XCRYPTO_PREFIX %+ _BIO_write_all
%xdefine _BIO_write_filename _ %+ XCRYPTO_PREFIX %+ _BIO_write_filename
%xdefine _BN_BLINDING_convert _ %+ XCRYPTO_PREFIX %+ _BN_BLINDING_convert
%xdefine _BN_BLINDING_free _ %+ XCRYPTO_PREFIX %+ _BN_BLINDING_free
%xdefine _BN_BLINDING_invalidate _ %+ XCRYPTO_PREFIX %+ _BN_BLINDING_invalidate
%xdefine _BN_BLINDING_invert _ %+ XCRYPTO_PREFIX %+ _BN_BLINDING_invert
%xdefine _BN_BLINDING_new _ %+ XCRYPTO_PREFIX %+ _BN_BLINDING_new
%xdefine _BN_CTX_end _ %+ XCRYPTO_PREFIX %+ _BN_CTX_end
%xdefine _BN_CTX_free _ %+ XCRYPTO_PREFIX %+ _BN_CTX_free
%xdefine _BN_CTX_get _ %+ XCRYPTO_PREFIX %+ _BN_CTX_get
%xdefine _BN_CTX_new _ %+ XCRYPTO_PREFIX %+ _BN_CTX_new
%xdefine _BN_CTX_start _ %+ XCRYPTO_PREFIX %+ _BN_CTX_start
%xdefine _BN_GENCB_call _ %+ XCRYPTO_PREFIX %+ _BN_GENCB_call
%xdefine _BN_GENCB_set _ %+ XCRYPTO_PREFIX %+ _BN_GENCB_set
%xdefine _BN_MONT_CTX_copy _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_copy
%xdefine _BN_MONT_CTX_free _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_free
%xdefine _BN_MONT_CTX_new _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_new
%xdefine _BN_MONT_CTX_new_consttime _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_new_consttime
%xdefine _BN_MONT_CTX_new_for_modulus _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_new_for_modulus
%xdefine _BN_MONT_CTX_set _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_set
%xdefine _BN_MONT_CTX_set_locked _ %+ XCRYPTO_PREFIX %+ _BN_MONT_CTX_set_locked
%xdefine _BN_abs_is_word _ %+ XCRYPTO_PREFIX %+ _BN_abs_is_word
%xdefine _BN_add _ %+ XCRYPTO_PREFIX %+ _BN_add
%xdefine _BN_add_word _ %+ XCRYPTO_PREFIX %+ _BN_add_word
%xdefine _BN_asc2bn _ %+ XCRYPTO_PREFIX %+ _BN_asc2bn
%xdefine _BN_bin2bn _ %+ XCRYPTO_PREFIX %+ _BN_bin2bn
%xdefine _BN_bn2bin _ %+ XCRYPTO_PREFIX %+ _BN_bn2bin
%xdefine _BN_bn2bin_padded _ %+ XCRYPTO_PREFIX %+ _BN_bn2bin_padded
%xdefine _BN_bn2binpad _ %+ XCRYPTO_PREFIX %+ _BN_bn2binpad
%xdefine _BN_bn2cbb_padded _ %+ XCRYPTO_PREFIX %+ _BN_bn2cbb_padded
%xdefine _BN_bn2dec _ %+ XCRYPTO_PREFIX %+ _BN_bn2dec
%xdefine _BN_bn2hex _ %+ XCRYPTO_PREFIX %+ _BN_bn2hex
%xdefine _BN_bn2le_padded _ %+ XCRYPTO_PREFIX %+ _BN_bn2le_padded
%xdefine _BN_bn2mpi _ %+ XCRYPTO_PREFIX %+ _BN_bn2mpi
%xdefine _BN_clear _ %+ XCRYPTO_PREFIX %+ _BN_clear
%xdefine _BN_clear_bit _ %+ XCRYPTO_PREFIX %+ _BN_clear_bit
%xdefine _BN_clear_free _ %+ XCRYPTO_PREFIX %+ _BN_clear_free
%xdefine _BN_cmp _ %+ XCRYPTO_PREFIX %+ _BN_cmp
%xdefine _BN_cmp_word _ %+ XCRYPTO_PREFIX %+ _BN_cmp_word
%xdefine _BN_copy _ %+ XCRYPTO_PREFIX %+ _BN_copy
%xdefine _BN_count_low_zero_bits _ %+ XCRYPTO_PREFIX %+ _BN_count_low_zero_bits
%xdefine _BN_dec2bn _ %+ XCRYPTO_PREFIX %+ _BN_dec2bn
%xdefine _BN_div _ %+ XCRYPTO_PREFIX %+ _BN_div
%xdefine _BN_div_word _ %+ XCRYPTO_PREFIX %+ _BN_div_word
%xdefine _BN_dup _ %+ XCRYPTO_PREFIX %+ _BN_dup
%xdefine _BN_enhanced_miller_rabin_primality_test _ %+ XCRYPTO_PREFIX %+ _BN_enhanced_miller_rabin_primality_test
%xdefine _BN_equal_consttime _ %+ XCRYPTO_PREFIX %+ _BN_equal_consttime
%xdefine _BN_exp _ %+ XCRYPTO_PREFIX %+ _BN_exp
%xdefine _BN_free _ %+ XCRYPTO_PREFIX %+ _BN_free
%xdefine _BN_from_montgomery _ %+ XCRYPTO_PREFIX %+ _BN_from_montgomery
%xdefine _BN_gcd _ %+ XCRYPTO_PREFIX %+ _BN_gcd
%xdefine _BN_generate_prime_ex _ %+ XCRYPTO_PREFIX %+ _BN_generate_prime_ex
%xdefine _BN_get_rfc3526_prime_1536 _ %+ XCRYPTO_PREFIX %+ _BN_get_rfc3526_prime_1536
%xdefine _BN_get_u64 _ %+ XCRYPTO_PREFIX %+ _BN_get_u64
%xdefine _BN_get_word _ %+ XCRYPTO_PREFIX %+ _BN_get_word
%xdefine _BN_hex2bn _ %+ XCRYPTO_PREFIX %+ _BN_hex2bn
%xdefine _BN_init _ %+ XCRYPTO_PREFIX %+ _BN_init
%xdefine _BN_is_bit_set _ %+ XCRYPTO_PREFIX %+ _BN_is_bit_set
%xdefine _BN_is_negative _ %+ XCRYPTO_PREFIX %+ _BN_is_negative
%xdefine _BN_is_odd _ %+ XCRYPTO_PREFIX %+ _BN_is_odd
%xdefine _BN_is_one _ %+ XCRYPTO_PREFIX %+ _BN_is_one
%xdefine _BN_is_pow2 _ %+ XCRYPTO_PREFIX %+ _BN_is_pow2
%xdefine _BN_is_prime_ex _ %+ XCRYPTO_PREFIX %+ _BN_is_prime_ex
%xdefine _BN_is_prime_fasttest_ex _ %+ XCRYPTO_PREFIX %+ _BN_is_prime_fasttest_ex
%xdefine _BN_is_word _ %+ XCRYPTO_PREFIX %+ _BN_is_word
%xdefine _BN_is_zero _ %+ XCRYPTO_PREFIX %+ _BN_is_zero
%xdefine _BN_le2bn _ %+ XCRYPTO_PREFIX %+ _BN_le2bn
%xdefine _BN_lshift _ %+ XCRYPTO_PREFIX %+ _BN_lshift
%xdefine _BN_lshift1 _ %+ XCRYPTO_PREFIX %+ _BN_lshift1
%xdefine _BN_marshal_asn1 _ %+ XCRYPTO_PREFIX %+ _BN_marshal_asn1
%xdefine _BN_mask_bits _ %+ XCRYPTO_PREFIX %+ _BN_mask_bits
%xdefine _BN_mod_add _ %+ XCRYPTO_PREFIX %+ _BN_mod_add
%xdefine _BN_mod_add_quick _ %+ XCRYPTO_PREFIX %+ _BN_mod_add_quick
%xdefine _BN_mod_exp _ %+ XCRYPTO_PREFIX %+ _BN_mod_exp
%xdefine _BN_mod_exp2_mont _ %+ XCRYPTO_PREFIX %+ _BN_mod_exp2_mont
%xdefine _BN_mod_exp_mont _ %+ XCRYPTO_PREFIX %+ _BN_mod_exp_mont
%xdefine _BN_mod_exp_mont_consttime _ %+ XCRYPTO_PREFIX %+ _BN_mod_exp_mont_consttime
%xdefine _BN_mod_exp_mont_word _ %+ XCRYPTO_PREFIX %+ _BN_mod_exp_mont_word
%xdefine _BN_mod_inverse _ %+ XCRYPTO_PREFIX %+ _BN_mod_inverse
%xdefine _BN_mod_inverse_blinded _ %+ XCRYPTO_PREFIX %+ _BN_mod_inverse_blinded
%xdefine _BN_mod_inverse_odd _ %+ XCRYPTO_PREFIX %+ _BN_mod_inverse_odd
%xdefine _BN_mod_lshift _ %+ XCRYPTO_PREFIX %+ _BN_mod_lshift
%xdefine _BN_mod_lshift1 _ %+ XCRYPTO_PREFIX %+ _BN_mod_lshift1
%xdefine _BN_mod_lshift1_quick _ %+ XCRYPTO_PREFIX %+ _BN_mod_lshift1_quick
%xdefine _BN_mod_lshift_quick _ %+ XCRYPTO_PREFIX %+ _BN_mod_lshift_quick
%xdefine _BN_mod_mul _ %+ XCRYPTO_PREFIX %+ _BN_mod_mul
%xdefine _BN_mod_mul_montgomery _ %+ XCRYPTO_PREFIX %+ _BN_mod_mul_montgomery
%xdefine _BN_mod_pow2 _ %+ XCRYPTO_PREFIX %+ _BN_mod_pow2
%xdefine _BN_mod_sqr _ %+ XCRYPTO_PREFIX %+ _BN_mod_sqr
%xdefine _BN_mod_sqrt _ %+ XCRYPTO_PREFIX %+ _BN_mod_sqrt
%xdefine _BN_mod_sub _ %+ XCRYPTO_PREFIX %+ _BN_mod_sub
%xdefine _BN_mod_sub_quick _ %+ XCRYPTO_PREFIX %+ _BN_mod_sub_quick
%xdefine _BN_mod_word _ %+ XCRYPTO_PREFIX %+ _BN_mod_word
%xdefine _BN_mpi2bn _ %+ XCRYPTO_PREFIX %+ _BN_mpi2bn
%xdefine _BN_mul _ %+ XCRYPTO_PREFIX %+ _BN_mul
%xdefine _BN_mul_word _ %+ XCRYPTO_PREFIX %+ _BN_mul_word
%xdefine _BN_new _ %+ XCRYPTO_PREFIX %+ _BN_new
%xdefine _BN_nnmod _ %+ XCRYPTO_PREFIX %+ _BN_nnmod
%xdefine _BN_nnmod_pow2 _ %+ XCRYPTO_PREFIX %+ _BN_nnmod_pow2
%xdefine _BN_num_bits _ %+ XCRYPTO_PREFIX %+ _BN_num_bits
%xdefine _BN_num_bits_word _ %+ XCRYPTO_PREFIX %+ _BN_num_bits_word
%xdefine _BN_num_bytes _ %+ XCRYPTO_PREFIX %+ _BN_num_bytes
%xdefine _BN_one _ %+ XCRYPTO_PREFIX %+ _BN_one
%xdefine _BN_parse_asn1_unsigned _ %+ XCRYPTO_PREFIX %+ _BN_parse_asn1_unsigned
%xdefine _BN_primality_test _ %+ XCRYPTO_PREFIX %+ _BN_primality_test
%xdefine _BN_print _ %+ XCRYPTO_PREFIX %+ _BN_print
%xdefine _BN_print_fp _ %+ XCRYPTO_PREFIX %+ _BN_print_fp
%xdefine _BN_pseudo_rand _ %+ XCRYPTO_PREFIX %+ _BN_pseudo_rand
%xdefine _BN_pseudo_rand_range _ %+ XCRYPTO_PREFIX %+ _BN_pseudo_rand_range
%xdefine _BN_rand _ %+ XCRYPTO_PREFIX %+ _BN_rand
%xdefine _BN_rand_range _ %+ XCRYPTO_PREFIX %+ _BN_rand_range
%xdefine _BN_rand_range_ex _ %+ XCRYPTO_PREFIX %+ _BN_rand_range_ex
%xdefine _BN_rshift _ %+ XCRYPTO_PREFIX %+ _BN_rshift
%xdefine _BN_rshift1 _ %+ XCRYPTO_PREFIX %+ _BN_rshift1
%xdefine _BN_set_bit _ %+ XCRYPTO_PREFIX %+ _BN_set_bit
%xdefine _BN_set_negative _ %+ XCRYPTO_PREFIX %+ _BN_set_negative
%xdefine _BN_set_u64 _ %+ XCRYPTO_PREFIX %+ _BN_set_u64
%xdefine _BN_set_word _ %+ XCRYPTO_PREFIX %+ _BN_set_word
%xdefine _BN_sqr _ %+ XCRYPTO_PREFIX %+ _BN_sqr
%xdefine _BN_sqrt _ %+ XCRYPTO_PREFIX %+ _BN_sqrt
%xdefine _BN_sub _ %+ XCRYPTO_PREFIX %+ _BN_sub
%xdefine _BN_sub_word _ %+ XCRYPTO_PREFIX %+ _BN_sub_word
%xdefine _BN_to_ASN1_ENUMERATED _ %+ XCRYPTO_PREFIX %+ _BN_to_ASN1_ENUMERATED
%xdefine _BN_to_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _BN_to_ASN1_INTEGER
%xdefine _BN_to_montgomery _ %+ XCRYPTO_PREFIX %+ _BN_to_montgomery
%xdefine _BN_uadd _ %+ XCRYPTO_PREFIX %+ _BN_uadd
%xdefine _BN_ucmp _ %+ XCRYPTO_PREFIX %+ _BN_ucmp
%xdefine _BN_usub _ %+ XCRYPTO_PREFIX %+ _BN_usub
%xdefine _BN_value_one _ %+ XCRYPTO_PREFIX %+ _BN_value_one
%xdefine _BN_zero _ %+ XCRYPTO_PREFIX %+ _BN_zero
%xdefine _BORINGSSL_self_test _ %+ XCRYPTO_PREFIX %+ _BORINGSSL_self_test
%xdefine _BUF_MEM_append _ %+ XCRYPTO_PREFIX %+ _BUF_MEM_append
%xdefine _BUF_MEM_free _ %+ XCRYPTO_PREFIX %+ _BUF_MEM_free
%xdefine _BUF_MEM_grow _ %+ XCRYPTO_PREFIX %+ _BUF_MEM_grow
%xdefine _BUF_MEM_grow_clean _ %+ XCRYPTO_PREFIX %+ _BUF_MEM_grow_clean
%xdefine _BUF_MEM_new _ %+ XCRYPTO_PREFIX %+ _BUF_MEM_new
%xdefine _BUF_MEM_reserve _ %+ XCRYPTO_PREFIX %+ _BUF_MEM_reserve
%xdefine _BUF_memdup _ %+ XCRYPTO_PREFIX %+ _BUF_memdup
%xdefine _BUF_strdup _ %+ XCRYPTO_PREFIX %+ _BUF_strdup
%xdefine _BUF_strlcat _ %+ XCRYPTO_PREFIX %+ _BUF_strlcat
%xdefine _BUF_strlcpy _ %+ XCRYPTO_PREFIX %+ _BUF_strlcpy
%xdefine _BUF_strndup _ %+ XCRYPTO_PREFIX %+ _BUF_strndup
%xdefine _BUF_strnlen _ %+ XCRYPTO_PREFIX %+ _BUF_strnlen
%xdefine _CBB_add_asn1 _ %+ XCRYPTO_PREFIX %+ _CBB_add_asn1
%xdefine _CBB_add_asn1_bool _ %+ XCRYPTO_PREFIX %+ _CBB_add_asn1_bool
%xdefine _CBB_add_asn1_int64 _ %+ XCRYPTO_PREFIX %+ _CBB_add_asn1_int64
%xdefine _CBB_add_asn1_octet_string _ %+ XCRYPTO_PREFIX %+ _CBB_add_asn1_octet_string
%xdefine _CBB_add_asn1_oid_from_text _ %+ XCRYPTO_PREFIX %+ _CBB_add_asn1_oid_from_text
%xdefine _CBB_add_asn1_uint64 _ %+ XCRYPTO_PREFIX %+ _CBB_add_asn1_uint64
%xdefine _CBB_add_bytes _ %+ XCRYPTO_PREFIX %+ _CBB_add_bytes
%xdefine _CBB_add_space _ %+ XCRYPTO_PREFIX %+ _CBB_add_space
%xdefine _CBB_add_u16 _ %+ XCRYPTO_PREFIX %+ _CBB_add_u16
%xdefine _CBB_add_u16_length_prefixed _ %+ XCRYPTO_PREFIX %+ _CBB_add_u16_length_prefixed
%xdefine _CBB_add_u16le _ %+ XCRYPTO_PREFIX %+ _CBB_add_u16le
%xdefine _CBB_add_u24 _ %+ XCRYPTO_PREFIX %+ _CBB_add_u24
%xdefine _CBB_add_u24_length_prefixed _ %+ XCRYPTO_PREFIX %+ _CBB_add_u24_length_prefixed
%xdefine _CBB_add_u32 _ %+ XCRYPTO_PREFIX %+ _CBB_add_u32
%xdefine _CBB_add_u32le _ %+ XCRYPTO_PREFIX %+ _CBB_add_u32le
%xdefine _CBB_add_u64 _ %+ XCRYPTO_PREFIX %+ _CBB_add_u64
%xdefine _CBB_add_u64le _ %+ XCRYPTO_PREFIX %+ _CBB_add_u64le
%xdefine _CBB_add_u8 _ %+ XCRYPTO_PREFIX %+ _CBB_add_u8
%xdefine _CBB_add_u8_length_prefixed _ %+ XCRYPTO_PREFIX %+ _CBB_add_u8_length_prefixed
%xdefine _CBB_cleanup _ %+ XCRYPTO_PREFIX %+ _CBB_cleanup
%xdefine _CBB_data _ %+ XCRYPTO_PREFIX %+ _CBB_data
%xdefine _CBB_did_write _ %+ XCRYPTO_PREFIX %+ _CBB_did_write
%xdefine _CBB_discard_child _ %+ XCRYPTO_PREFIX %+ _CBB_discard_child
%xdefine _CBB_finish _ %+ XCRYPTO_PREFIX %+ _CBB_finish
%xdefine _CBB_finish_i2d _ %+ XCRYPTO_PREFIX %+ _CBB_finish_i2d
%xdefine _CBB_flush _ %+ XCRYPTO_PREFIX %+ _CBB_flush
%xdefine _CBB_flush_asn1_set_of _ %+ XCRYPTO_PREFIX %+ _CBB_flush_asn1_set_of
%xdefine _CBB_init _ %+ XCRYPTO_PREFIX %+ _CBB_init
%xdefine _CBB_init_fixed _ %+ XCRYPTO_PREFIX %+ _CBB_init_fixed
%xdefine _CBB_len _ %+ XCRYPTO_PREFIX %+ _CBB_len
%xdefine _CBB_reserve _ %+ XCRYPTO_PREFIX %+ _CBB_reserve
%xdefine _CBB_zero _ %+ XCRYPTO_PREFIX %+ _CBB_zero
%xdefine _CBS_asn1_ber_to_der _ %+ XCRYPTO_PREFIX %+ _CBS_asn1_ber_to_der
%xdefine _CBS_asn1_bitstring_has_bit _ %+ XCRYPTO_PREFIX %+ _CBS_asn1_bitstring_has_bit
%xdefine _CBS_asn1_oid_to_text _ %+ XCRYPTO_PREFIX %+ _CBS_asn1_oid_to_text
%xdefine _CBS_contains_zero_byte _ %+ XCRYPTO_PREFIX %+ _CBS_contains_zero_byte
%xdefine _CBS_copy_bytes _ %+ XCRYPTO_PREFIX %+ _CBS_copy_bytes
%xdefine _CBS_data _ %+ XCRYPTO_PREFIX %+ _CBS_data
%xdefine _CBS_get_any_asn1 _ %+ XCRYPTO_PREFIX %+ _CBS_get_any_asn1
%xdefine _CBS_get_any_asn1_element _ %+ XCRYPTO_PREFIX %+ _CBS_get_any_asn1_element
%xdefine _CBS_get_any_ber_asn1_element _ %+ XCRYPTO_PREFIX %+ _CBS_get_any_ber_asn1_element
%xdefine _CBS_get_asn1 _ %+ XCRYPTO_PREFIX %+ _CBS_get_asn1
%xdefine _CBS_get_asn1_bool _ %+ XCRYPTO_PREFIX %+ _CBS_get_asn1_bool
%xdefine _CBS_get_asn1_element _ %+ XCRYPTO_PREFIX %+ _CBS_get_asn1_element
%xdefine _CBS_get_asn1_implicit_string _ %+ XCRYPTO_PREFIX %+ _CBS_get_asn1_implicit_string
%xdefine _CBS_get_asn1_int64 _ %+ XCRYPTO_PREFIX %+ _CBS_get_asn1_int64
%xdefine _CBS_get_asn1_uint64 _ %+ XCRYPTO_PREFIX %+ _CBS_get_asn1_uint64
%xdefine _CBS_get_bytes _ %+ XCRYPTO_PREFIX %+ _CBS_get_bytes
%xdefine _CBS_get_last_u8 _ %+ XCRYPTO_PREFIX %+ _CBS_get_last_u8
%xdefine _CBS_get_optional_asn1 _ %+ XCRYPTO_PREFIX %+ _CBS_get_optional_asn1
%xdefine _CBS_get_optional_asn1_bool _ %+ XCRYPTO_PREFIX %+ _CBS_get_optional_asn1_bool
%xdefine _CBS_get_optional_asn1_octet_string _ %+ XCRYPTO_PREFIX %+ _CBS_get_optional_asn1_octet_string
%xdefine _CBS_get_optional_asn1_uint64 _ %+ XCRYPTO_PREFIX %+ _CBS_get_optional_asn1_uint64
%xdefine _CBS_get_u16 _ %+ XCRYPTO_PREFIX %+ _CBS_get_u16
%xdefine _CBS_get_u16_length_prefixed _ %+ XCRYPTO_PREFIX %+ _CBS_get_u16_length_prefixed
%xdefine _CBS_get_u16le _ %+ XCRYPTO_PREFIX %+ _CBS_get_u16le
%xdefine _CBS_get_u24 _ %+ XCRYPTO_PREFIX %+ _CBS_get_u24
%xdefine _CBS_get_u24_length_prefixed _ %+ XCRYPTO_PREFIX %+ _CBS_get_u24_length_prefixed
%xdefine _CBS_get_u32 _ %+ XCRYPTO_PREFIX %+ _CBS_get_u32
%xdefine _CBS_get_u32le _ %+ XCRYPTO_PREFIX %+ _CBS_get_u32le
%xdefine _CBS_get_u64 _ %+ XCRYPTO_PREFIX %+ _CBS_get_u64
%xdefine _CBS_get_u64le _ %+ XCRYPTO_PREFIX %+ _CBS_get_u64le
%xdefine _CBS_get_u8 _ %+ XCRYPTO_PREFIX %+ _CBS_get_u8
%xdefine _CBS_get_u8_length_prefixed _ %+ XCRYPTO_PREFIX %+ _CBS_get_u8_length_prefixed
%xdefine _CBS_init _ %+ XCRYPTO_PREFIX %+ _CBS_init
%xdefine _CBS_is_valid_asn1_bitstring _ %+ XCRYPTO_PREFIX %+ _CBS_is_valid_asn1_bitstring
%xdefine _CBS_len _ %+ XCRYPTO_PREFIX %+ _CBS_len
%xdefine _CBS_mem_equal _ %+ XCRYPTO_PREFIX %+ _CBS_mem_equal
%xdefine _CBS_peek_asn1_tag _ %+ XCRYPTO_PREFIX %+ _CBS_peek_asn1_tag
%xdefine _CBS_skip _ %+ XCRYPTO_PREFIX %+ _CBS_skip
%xdefine _CBS_stow _ %+ XCRYPTO_PREFIX %+ _CBS_stow
%xdefine _CBS_strdup _ %+ XCRYPTO_PREFIX %+ _CBS_strdup
%xdefine _CERTIFICATEPOLICIES_free _ %+ XCRYPTO_PREFIX %+ _CERTIFICATEPOLICIES_free
%xdefine _CERTIFICATEPOLICIES_it _ %+ XCRYPTO_PREFIX %+ _CERTIFICATEPOLICIES_it
%xdefine _CERTIFICATEPOLICIES_new _ %+ XCRYPTO_PREFIX %+ _CERTIFICATEPOLICIES_new
%xdefine _CMAC_CTX_copy _ %+ XCRYPTO_PREFIX %+ _CMAC_CTX_copy
%xdefine _CMAC_CTX_free _ %+ XCRYPTO_PREFIX %+ _CMAC_CTX_free
%xdefine _CMAC_CTX_new _ %+ XCRYPTO_PREFIX %+ _CMAC_CTX_new
%xdefine _CMAC_Final _ %+ XCRYPTO_PREFIX %+ _CMAC_Final
%xdefine _CMAC_Init _ %+ XCRYPTO_PREFIX %+ _CMAC_Init
%xdefine _CMAC_Reset _ %+ XCRYPTO_PREFIX %+ _CMAC_Reset
%xdefine _CMAC_Update _ %+ XCRYPTO_PREFIX %+ _CMAC_Update
%xdefine _CONF_VALUE_new _ %+ XCRYPTO_PREFIX %+ _CONF_VALUE_new
%xdefine _CONF_modules_free _ %+ XCRYPTO_PREFIX %+ _CONF_modules_free
%xdefine _CONF_modules_load_file _ %+ XCRYPTO_PREFIX %+ _CONF_modules_load_file
%xdefine _CONF_parse_list _ %+ XCRYPTO_PREFIX %+ _CONF_parse_list
%xdefine _CRL_DIST_POINTS_free _ %+ XCRYPTO_PREFIX %+ _CRL_DIST_POINTS_free
%xdefine _CRL_DIST_POINTS_it _ %+ XCRYPTO_PREFIX %+ _CRL_DIST_POINTS_it
%xdefine _CRL_DIST_POINTS_new _ %+ XCRYPTO_PREFIX %+ _CRL_DIST_POINTS_new
%xdefine _CRYPTO_BUFFER_POOL_free _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_POOL_free
%xdefine _CRYPTO_BUFFER_POOL_new _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_POOL_new
%xdefine _CRYPTO_BUFFER_alloc _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_alloc
%xdefine _CRYPTO_BUFFER_data _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_data
%xdefine _CRYPTO_BUFFER_free _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_free
%xdefine _CRYPTO_BUFFER_init_CBS _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_init_CBS
%xdefine _CRYPTO_BUFFER_len _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_len
%xdefine _CRYPTO_BUFFER_new _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_new
%xdefine _CRYPTO_BUFFER_new_from_CBS _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_new_from_CBS
%xdefine _CRYPTO_BUFFER_up_ref _ %+ XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_up_ref
%xdefine _CRYPTO_MUTEX_cleanup _ %+ XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_cleanup
%xdefine _CRYPTO_MUTEX_init _ %+ XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_init
%xdefine _CRYPTO_MUTEX_lock_read _ %+ XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_lock_read
%xdefine _CRYPTO_MUTEX_lock_write _ %+ XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_lock_write
%xdefine _CRYPTO_MUTEX_unlock_read _ %+ XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_unlock_read
%xdefine _CRYPTO_MUTEX_unlock_write _ %+ XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_unlock_write
%xdefine _CRYPTO_POLYVAL_finish _ %+ XCRYPTO_PREFIX %+ _CRYPTO_POLYVAL_finish
%xdefine _CRYPTO_POLYVAL_init _ %+ XCRYPTO_PREFIX %+ _CRYPTO_POLYVAL_init
%xdefine _CRYPTO_POLYVAL_update_blocks _ %+ XCRYPTO_PREFIX %+ _CRYPTO_POLYVAL_update_blocks
%xdefine _CRYPTO_STATIC_MUTEX_lock_read _ %+ XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_lock_read
%xdefine _CRYPTO_STATIC_MUTEX_lock_write _ %+ XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_lock_write
%xdefine _CRYPTO_STATIC_MUTEX_unlock_read _ %+ XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_unlock_read
%xdefine _CRYPTO_STATIC_MUTEX_unlock_write _ %+ XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_unlock_write
%xdefine _CRYPTO_THREADID_current _ %+ XCRYPTO_PREFIX %+ _CRYPTO_THREADID_current
%xdefine _CRYPTO_THREADID_set_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_THREADID_set_callback
%xdefine _CRYPTO_THREADID_set_numeric _ %+ XCRYPTO_PREFIX %+ _CRYPTO_THREADID_set_numeric
%xdefine _CRYPTO_THREADID_set_pointer _ %+ XCRYPTO_PREFIX %+ _CRYPTO_THREADID_set_pointer
%xdefine _CRYPTO_cbc128_decrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_cbc128_decrypt
%xdefine _CRYPTO_cbc128_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_cbc128_encrypt
%xdefine _CRYPTO_cfb128_1_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_cfb128_1_encrypt
%xdefine _CRYPTO_cfb128_8_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_cfb128_8_encrypt
%xdefine _CRYPTO_cfb128_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_cfb128_encrypt
%xdefine _CRYPTO_chacha_20 _ %+ XCRYPTO_PREFIX %+ _CRYPTO_chacha_20
%xdefine _CRYPTO_cleanup_all_ex_data _ %+ XCRYPTO_PREFIX %+ _CRYPTO_cleanup_all_ex_data
%xdefine _CRYPTO_ctr128_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_ctr128_encrypt
%xdefine _CRYPTO_ctr128_encrypt_ctr32 _ %+ XCRYPTO_PREFIX %+ _CRYPTO_ctr128_encrypt_ctr32
%xdefine _CRYPTO_fork_detect_ignore_madv_wipeonfork_for_testing _ %+ XCRYPTO_PREFIX %+ _CRYPTO_fork_detect_ignore_madv_wipeonfork_for_testing
%xdefine _CRYPTO_free_ex_data _ %+ XCRYPTO_PREFIX %+ _CRYPTO_free_ex_data
%xdefine _CRYPTO_gcm128_aad _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_aad
%xdefine _CRYPTO_gcm128_decrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_decrypt
%xdefine _CRYPTO_gcm128_decrypt_ctr32 _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_decrypt_ctr32
%xdefine _CRYPTO_gcm128_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_encrypt
%xdefine _CRYPTO_gcm128_encrypt_ctr32 _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_encrypt_ctr32
%xdefine _CRYPTO_gcm128_finish _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_finish
%xdefine _CRYPTO_gcm128_init_key _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_init_key
%xdefine _CRYPTO_gcm128_setiv _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_setiv
%xdefine _CRYPTO_gcm128_tag _ %+ XCRYPTO_PREFIX %+ _CRYPTO_gcm128_tag
%xdefine _CRYPTO_get_dynlock_create_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_dynlock_create_callback
%xdefine _CRYPTO_get_dynlock_destroy_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_dynlock_destroy_callback
%xdefine _CRYPTO_get_dynlock_lock_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_dynlock_lock_callback
%xdefine _CRYPTO_get_ex_data _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_ex_data
%xdefine _CRYPTO_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_ex_new_index
%xdefine _CRYPTO_get_fork_generation _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_fork_generation
%xdefine _CRYPTO_get_lock_name _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_lock_name
%xdefine _CRYPTO_get_locking_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_locking_callback
%xdefine _CRYPTO_get_thread_local _ %+ XCRYPTO_PREFIX %+ _CRYPTO_get_thread_local
%xdefine _CRYPTO_ghash_init _ %+ XCRYPTO_PREFIX %+ _CRYPTO_ghash_init
%xdefine _CRYPTO_has_asm _ %+ XCRYPTO_PREFIX %+ _CRYPTO_has_asm
%xdefine _CRYPTO_hchacha20 _ %+ XCRYPTO_PREFIX %+ _CRYPTO_hchacha20
%xdefine _CRYPTO_is_ARMv8_AES_capable _ %+ XCRYPTO_PREFIX %+ _CRYPTO_is_ARMv8_AES_capable
%xdefine _CRYPTO_is_ARMv8_PMULL_capable _ %+ XCRYPTO_PREFIX %+ _CRYPTO_is_ARMv8_PMULL_capable
%xdefine _CRYPTO_is_NEON_capable_at_runtime _ %+ XCRYPTO_PREFIX %+ _CRYPTO_is_NEON_capable_at_runtime
%xdefine _CRYPTO_is_confidential_build _ %+ XCRYPTO_PREFIX %+ _CRYPTO_is_confidential_build
%xdefine _CRYPTO_library_init _ %+ XCRYPTO_PREFIX %+ _CRYPTO_library_init
%xdefine _CRYPTO_malloc_init _ %+ XCRYPTO_PREFIX %+ _CRYPTO_malloc_init
%xdefine _CRYPTO_memcmp _ %+ XCRYPTO_PREFIX %+ _CRYPTO_memcmp
%xdefine _CRYPTO_new_ex_data _ %+ XCRYPTO_PREFIX %+ _CRYPTO_new_ex_data
%xdefine _CRYPTO_num_locks _ %+ XCRYPTO_PREFIX %+ _CRYPTO_num_locks
%xdefine _CRYPTO_ofb128_encrypt _ %+ XCRYPTO_PREFIX %+ _CRYPTO_ofb128_encrypt
%xdefine _CRYPTO_once _ %+ XCRYPTO_PREFIX %+ _CRYPTO_once
%xdefine _CRYPTO_poly1305_finish _ %+ XCRYPTO_PREFIX %+ _CRYPTO_poly1305_finish
%xdefine _CRYPTO_poly1305_init _ %+ XCRYPTO_PREFIX %+ _CRYPTO_poly1305_init
%xdefine _CRYPTO_poly1305_update _ %+ XCRYPTO_PREFIX %+ _CRYPTO_poly1305_update
%xdefine _CRYPTO_rdrand _ %+ XCRYPTO_PREFIX %+ _CRYPTO_rdrand
%xdefine _CRYPTO_rdrand_multiple8_buf _ %+ XCRYPTO_PREFIX %+ _CRYPTO_rdrand_multiple8_buf
%xdefine _CRYPTO_refcount_dec_and_test_zero _ %+ XCRYPTO_PREFIX %+ _CRYPTO_refcount_dec_and_test_zero
%xdefine _CRYPTO_refcount_inc _ %+ XCRYPTO_PREFIX %+ _CRYPTO_refcount_inc
%xdefine _CRYPTO_set_add_lock_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_add_lock_callback
%xdefine _CRYPTO_set_dynlock_create_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_dynlock_create_callback
%xdefine _CRYPTO_set_dynlock_destroy_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_dynlock_destroy_callback
%xdefine _CRYPTO_set_dynlock_lock_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_dynlock_lock_callback
%xdefine _CRYPTO_set_ex_data _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_ex_data
%xdefine _CRYPTO_set_id_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_id_callback
%xdefine _CRYPTO_set_locking_callback _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_locking_callback
%xdefine _CRYPTO_set_thread_local _ %+ XCRYPTO_PREFIX %+ _CRYPTO_set_thread_local
%xdefine _CRYPTO_sysrand _ %+ XCRYPTO_PREFIX %+ _CRYPTO_sysrand
%xdefine _CRYPTO_sysrand_if_available _ %+ XCRYPTO_PREFIX %+ _CRYPTO_sysrand_if_available
%xdefine _CRYPTO_tls1_prf _ %+ XCRYPTO_PREFIX %+ _CRYPTO_tls1_prf
%xdefine _CTR_DRBG_clear _ %+ XCRYPTO_PREFIX %+ _CTR_DRBG_clear
%xdefine _CTR_DRBG_generate _ %+ XCRYPTO_PREFIX %+ _CTR_DRBG_generate
%xdefine _CTR_DRBG_init _ %+ XCRYPTO_PREFIX %+ _CTR_DRBG_init
%xdefine _CTR_DRBG_reseed _ %+ XCRYPTO_PREFIX %+ _CTR_DRBG_reseed
%xdefine _ChaCha20_ctr32 _ %+ XCRYPTO_PREFIX %+ _ChaCha20_ctr32
%xdefine _DES_decrypt3 _ %+ XCRYPTO_PREFIX %+ _DES_decrypt3
%xdefine _DES_ecb3_encrypt _ %+ XCRYPTO_PREFIX %+ _DES_ecb3_encrypt
%xdefine _DES_ecb_encrypt _ %+ XCRYPTO_PREFIX %+ _DES_ecb_encrypt
%xdefine _DES_ede2_cbc_encrypt _ %+ XCRYPTO_PREFIX %+ _DES_ede2_cbc_encrypt
%xdefine _DES_ede3_cbc_encrypt _ %+ XCRYPTO_PREFIX %+ _DES_ede3_cbc_encrypt
%xdefine _DES_encrypt3 _ %+ XCRYPTO_PREFIX %+ _DES_encrypt3
%xdefine _DES_ncbc_encrypt _ %+ XCRYPTO_PREFIX %+ _DES_ncbc_encrypt
%xdefine _DES_set_key _ %+ XCRYPTO_PREFIX %+ _DES_set_key
%xdefine _DES_set_key_unchecked _ %+ XCRYPTO_PREFIX %+ _DES_set_key_unchecked
%xdefine _DES_set_odd_parity _ %+ XCRYPTO_PREFIX %+ _DES_set_odd_parity
%xdefine _DH_check _ %+ XCRYPTO_PREFIX %+ _DH_check
%xdefine _DH_check_pub_key _ %+ XCRYPTO_PREFIX %+ _DH_check_pub_key
%xdefine _DH_compute_key _ %+ XCRYPTO_PREFIX %+ _DH_compute_key
%xdefine _DH_free _ %+ XCRYPTO_PREFIX %+ _DH_free
%xdefine _DH_generate_key _ %+ XCRYPTO_PREFIX %+ _DH_generate_key
%xdefine _DH_generate_parameters_ex _ %+ XCRYPTO_PREFIX %+ _DH_generate_parameters_ex
%xdefine _DH_get0_g _ %+ XCRYPTO_PREFIX %+ _DH_get0_g
%xdefine _DH_get0_key _ %+ XCRYPTO_PREFIX %+ _DH_get0_key
%xdefine _DH_get0_p _ %+ XCRYPTO_PREFIX %+ _DH_get0_p
%xdefine _DH_get0_pqg _ %+ XCRYPTO_PREFIX %+ _DH_get0_pqg
%xdefine _DH_get0_priv_key _ %+ XCRYPTO_PREFIX %+ _DH_get0_priv_key
%xdefine _DH_get0_pub_key _ %+ XCRYPTO_PREFIX %+ _DH_get0_pub_key
%xdefine _DH_get0_q _ %+ XCRYPTO_PREFIX %+ _DH_get0_q
%xdefine _DH_get_ex_data _ %+ XCRYPTO_PREFIX %+ _DH_get_ex_data
%xdefine _DH_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _DH_get_ex_new_index
%xdefine _DH_marshal_parameters _ %+ XCRYPTO_PREFIX %+ _DH_marshal_parameters
%xdefine _DH_new _ %+ XCRYPTO_PREFIX %+ _DH_new
%xdefine _DH_num_bits _ %+ XCRYPTO_PREFIX %+ _DH_num_bits
%xdefine _DH_parse_parameters _ %+ XCRYPTO_PREFIX %+ _DH_parse_parameters
%xdefine _DH_set0_key _ %+ XCRYPTO_PREFIX %+ _DH_set0_key
%xdefine _DH_set0_pqg _ %+ XCRYPTO_PREFIX %+ _DH_set0_pqg
%xdefine _DH_set_ex_data _ %+ XCRYPTO_PREFIX %+ _DH_set_ex_data
%xdefine _DH_set_length _ %+ XCRYPTO_PREFIX %+ _DH_set_length
%xdefine _DH_size _ %+ XCRYPTO_PREFIX %+ _DH_size
%xdefine _DH_up_ref _ %+ XCRYPTO_PREFIX %+ _DH_up_ref
%xdefine _DHparams_dup _ %+ XCRYPTO_PREFIX %+ _DHparams_dup
%xdefine _DIRECTORYSTRING_free _ %+ XCRYPTO_PREFIX %+ _DIRECTORYSTRING_free
%xdefine _DIRECTORYSTRING_it _ %+ XCRYPTO_PREFIX %+ _DIRECTORYSTRING_it
%xdefine _DIRECTORYSTRING_new _ %+ XCRYPTO_PREFIX %+ _DIRECTORYSTRING_new
%xdefine _DISPLAYTEXT_free _ %+ XCRYPTO_PREFIX %+ _DISPLAYTEXT_free
%xdefine _DISPLAYTEXT_it _ %+ XCRYPTO_PREFIX %+ _DISPLAYTEXT_it
%xdefine _DISPLAYTEXT_new _ %+ XCRYPTO_PREFIX %+ _DISPLAYTEXT_new
%xdefine _DIST_POINT_NAME_free _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_NAME_free
%xdefine _DIST_POINT_NAME_it _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_NAME_it
%xdefine _DIST_POINT_NAME_new _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_NAME_new
%xdefine _DIST_POINT_free _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_free
%xdefine _DIST_POINT_it _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_it
%xdefine _DIST_POINT_new _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_new
%xdefine _DIST_POINT_set_dpname _ %+ XCRYPTO_PREFIX %+ _DIST_POINT_set_dpname
%xdefine _DSA_SIG_free _ %+ XCRYPTO_PREFIX %+ _DSA_SIG_free
%xdefine _DSA_SIG_marshal _ %+ XCRYPTO_PREFIX %+ _DSA_SIG_marshal
%xdefine _DSA_SIG_new _ %+ XCRYPTO_PREFIX %+ _DSA_SIG_new
%xdefine _DSA_SIG_parse _ %+ XCRYPTO_PREFIX %+ _DSA_SIG_parse
%xdefine _DSA_check_signature _ %+ XCRYPTO_PREFIX %+ _DSA_check_signature
%xdefine _DSA_do_check_signature _ %+ XCRYPTO_PREFIX %+ _DSA_do_check_signature
%xdefine _DSA_do_sign _ %+ XCRYPTO_PREFIX %+ _DSA_do_sign
%xdefine _DSA_do_verify _ %+ XCRYPTO_PREFIX %+ _DSA_do_verify
%xdefine _DSA_dup_DH _ %+ XCRYPTO_PREFIX %+ _DSA_dup_DH
%xdefine _DSA_free _ %+ XCRYPTO_PREFIX %+ _DSA_free
%xdefine _DSA_generate_key _ %+ XCRYPTO_PREFIX %+ _DSA_generate_key
%xdefine _DSA_generate_parameters_ex _ %+ XCRYPTO_PREFIX %+ _DSA_generate_parameters_ex
%xdefine _DSA_get0_g _ %+ XCRYPTO_PREFIX %+ _DSA_get0_g
%xdefine _DSA_get0_key _ %+ XCRYPTO_PREFIX %+ _DSA_get0_key
%xdefine _DSA_get0_p _ %+ XCRYPTO_PREFIX %+ _DSA_get0_p
%xdefine _DSA_get0_pqg _ %+ XCRYPTO_PREFIX %+ _DSA_get0_pqg
%xdefine _DSA_get0_priv_key _ %+ XCRYPTO_PREFIX %+ _DSA_get0_priv_key
%xdefine _DSA_get0_pub_key _ %+ XCRYPTO_PREFIX %+ _DSA_get0_pub_key
%xdefine _DSA_get0_q _ %+ XCRYPTO_PREFIX %+ _DSA_get0_q
%xdefine _DSA_get_ex_data _ %+ XCRYPTO_PREFIX %+ _DSA_get_ex_data
%xdefine _DSA_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _DSA_get_ex_new_index
%xdefine _DSA_marshal_parameters _ %+ XCRYPTO_PREFIX %+ _DSA_marshal_parameters
%xdefine _DSA_marshal_private_key _ %+ XCRYPTO_PREFIX %+ _DSA_marshal_private_key
%xdefine _DSA_marshal_public_key _ %+ XCRYPTO_PREFIX %+ _DSA_marshal_public_key
%xdefine _DSA_new _ %+ XCRYPTO_PREFIX %+ _DSA_new
%xdefine _DSA_parse_parameters _ %+ XCRYPTO_PREFIX %+ _DSA_parse_parameters
%xdefine _DSA_parse_private_key _ %+ XCRYPTO_PREFIX %+ _DSA_parse_private_key
%xdefine _DSA_parse_public_key _ %+ XCRYPTO_PREFIX %+ _DSA_parse_public_key
%xdefine _DSA_set0_key _ %+ XCRYPTO_PREFIX %+ _DSA_set0_key
%xdefine _DSA_set0_pqg _ %+ XCRYPTO_PREFIX %+ _DSA_set0_pqg
%xdefine _DSA_set_ex_data _ %+ XCRYPTO_PREFIX %+ _DSA_set_ex_data
%xdefine _DSA_sign _ %+ XCRYPTO_PREFIX %+ _DSA_sign
%xdefine _DSA_size _ %+ XCRYPTO_PREFIX %+ _DSA_size
%xdefine _DSA_up_ref _ %+ XCRYPTO_PREFIX %+ _DSA_up_ref
%xdefine _DSA_verify _ %+ XCRYPTO_PREFIX %+ _DSA_verify
%xdefine _DSAparams_dup _ %+ XCRYPTO_PREFIX %+ _DSAparams_dup
%xdefine _DTLS_client_method _ %+ XCRYPTO_PREFIX %+ _DTLS_client_method
%xdefine _DTLS_method _ %+ XCRYPTO_PREFIX %+ _DTLS_method
%xdefine _DTLS_server_method _ %+ XCRYPTO_PREFIX %+ _DTLS_server_method
%xdefine _DTLS_with_buffers_method _ %+ XCRYPTO_PREFIX %+ _DTLS_with_buffers_method
%xdefine _DTLSv1_2_client_method _ %+ XCRYPTO_PREFIX %+ _DTLSv1_2_client_method
%xdefine _DTLSv1_2_method _ %+ XCRYPTO_PREFIX %+ _DTLSv1_2_method
%xdefine _DTLSv1_2_server_method _ %+ XCRYPTO_PREFIX %+ _DTLSv1_2_server_method
%xdefine _DTLSv1_client_method _ %+ XCRYPTO_PREFIX %+ _DTLSv1_client_method
%xdefine _DTLSv1_get_timeout _ %+ XCRYPTO_PREFIX %+ _DTLSv1_get_timeout
%xdefine _DTLSv1_handle_timeout _ %+ XCRYPTO_PREFIX %+ _DTLSv1_handle_timeout
%xdefine _DTLSv1_method _ %+ XCRYPTO_PREFIX %+ _DTLSv1_method
%xdefine _DTLSv1_server_method _ %+ XCRYPTO_PREFIX %+ _DTLSv1_server_method
%xdefine _DTLSv1_set_initial_timeout_duration _ %+ XCRYPTO_PREFIX %+ _DTLSv1_set_initial_timeout_duration
%xdefine _DW.ref.__gxx_personality_v0 _ %+ XCRYPTO_PREFIX %+ _DW.ref.__gxx_personality_v0
%xdefine _ECDH_compute_key _ %+ XCRYPTO_PREFIX %+ _ECDH_compute_key
%xdefine _ECDH_compute_key_fips _ %+ XCRYPTO_PREFIX %+ _ECDH_compute_key_fips
%xdefine _ECDSA_SIG_free _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_free
%xdefine _ECDSA_SIG_from_bytes _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_from_bytes
%xdefine _ECDSA_SIG_get0 _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_get0
%xdefine _ECDSA_SIG_get0_r _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_get0_r
%xdefine _ECDSA_SIG_get0_s _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_get0_s
%xdefine _ECDSA_SIG_marshal _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_marshal
%xdefine _ECDSA_SIG_max_len _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_max_len
%xdefine _ECDSA_SIG_new _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_new
%xdefine _ECDSA_SIG_parse _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_parse
%xdefine _ECDSA_SIG_set0 _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_set0
%xdefine _ECDSA_SIG_to_bytes _ %+ XCRYPTO_PREFIX %+ _ECDSA_SIG_to_bytes
%xdefine _ECDSA_do_sign _ %+ XCRYPTO_PREFIX %+ _ECDSA_do_sign
%xdefine _ECDSA_do_verify _ %+ XCRYPTO_PREFIX %+ _ECDSA_do_verify
%xdefine _ECDSA_sign _ %+ XCRYPTO_PREFIX %+ _ECDSA_sign
%xdefine _ECDSA_size _ %+ XCRYPTO_PREFIX %+ _ECDSA_size
%xdefine _ECDSA_verify _ %+ XCRYPTO_PREFIX %+ _ECDSA_verify
%xdefine _EC_GFp_mont_method _ %+ XCRYPTO_PREFIX %+ _EC_GFp_mont_method
%xdefine _EC_GFp_nistp224_method _ %+ XCRYPTO_PREFIX %+ _EC_GFp_nistp224_method
%xdefine _EC_GFp_nistp256_method _ %+ XCRYPTO_PREFIX %+ _EC_GFp_nistp256_method
%xdefine _EC_GFp_nistz256_method _ %+ XCRYPTO_PREFIX %+ _EC_GFp_nistz256_method
%xdefine _EC_GROUP_cmp _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_cmp
%xdefine _EC_GROUP_dup _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_dup
%xdefine _EC_GROUP_free _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_free
%xdefine _EC_GROUP_get0_generator _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get0_generator
%xdefine _EC_GROUP_get0_order _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get0_order
%xdefine _EC_GROUP_get_cofactor _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get_cofactor
%xdefine _EC_GROUP_get_curve_GFp _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get_curve_GFp
%xdefine _EC_GROUP_get_curve_name _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get_curve_name
%xdefine _EC_GROUP_get_degree _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get_degree
%xdefine _EC_GROUP_get_order _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_get_order
%xdefine _EC_GROUP_method_of _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_method_of
%xdefine _EC_GROUP_new_by_curve_name _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_new_by_curve_name
%xdefine _EC_GROUP_new_curve_GFp _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_new_curve_GFp
%xdefine _EC_GROUP_order_bits _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_order_bits
%xdefine _EC_GROUP_set_asn1_flag _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_set_asn1_flag
%xdefine _EC_GROUP_set_generator _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_set_generator
%xdefine _EC_GROUP_set_point_conversion_form _ %+ XCRYPTO_PREFIX %+ _EC_GROUP_set_point_conversion_form
%xdefine _EC_KEY_check_fips _ %+ XCRYPTO_PREFIX %+ _EC_KEY_check_fips
%xdefine _EC_KEY_check_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_check_key
%xdefine _EC_KEY_derive_from_secret _ %+ XCRYPTO_PREFIX %+ _EC_KEY_derive_from_secret
%xdefine _EC_KEY_dup _ %+ XCRYPTO_PREFIX %+ _EC_KEY_dup
%xdefine _EC_KEY_free _ %+ XCRYPTO_PREFIX %+ _EC_KEY_free
%xdefine _EC_KEY_generate_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_generate_key
%xdefine _EC_KEY_generate_key_fips _ %+ XCRYPTO_PREFIX %+ _EC_KEY_generate_key_fips
%xdefine _EC_KEY_get0_group _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get0_group
%xdefine _EC_KEY_get0_private_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get0_private_key
%xdefine _EC_KEY_get0_public_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get0_public_key
%xdefine _EC_KEY_get_conv_form _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get_conv_form
%xdefine _EC_KEY_get_enc_flags _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get_enc_flags
%xdefine _EC_KEY_get_ex_data _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get_ex_data
%xdefine _EC_KEY_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _EC_KEY_get_ex_new_index
%xdefine _EC_KEY_is_opaque _ %+ XCRYPTO_PREFIX %+ _EC_KEY_is_opaque
%xdefine _EC_KEY_key2buf _ %+ XCRYPTO_PREFIX %+ _EC_KEY_key2buf
%xdefine _EC_KEY_marshal_curve_name _ %+ XCRYPTO_PREFIX %+ _EC_KEY_marshal_curve_name
%xdefine _EC_KEY_marshal_private_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_marshal_private_key
%xdefine _EC_KEY_new _ %+ XCRYPTO_PREFIX %+ _EC_KEY_new
%xdefine _EC_KEY_new_by_curve_name _ %+ XCRYPTO_PREFIX %+ _EC_KEY_new_by_curve_name
%xdefine _EC_KEY_new_method _ %+ XCRYPTO_PREFIX %+ _EC_KEY_new_method
%xdefine _EC_KEY_parse_curve_name _ %+ XCRYPTO_PREFIX %+ _EC_KEY_parse_curve_name
%xdefine _EC_KEY_parse_parameters _ %+ XCRYPTO_PREFIX %+ _EC_KEY_parse_parameters
%xdefine _EC_KEY_parse_private_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_parse_private_key
%xdefine _EC_KEY_set_asn1_flag _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_asn1_flag
%xdefine _EC_KEY_set_conv_form _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_conv_form
%xdefine _EC_KEY_set_enc_flags _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_enc_flags
%xdefine _EC_KEY_set_ex_data _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_ex_data
%xdefine _EC_KEY_set_group _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_group
%xdefine _EC_KEY_set_private_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_private_key
%xdefine _EC_KEY_set_public_key _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_public_key
%xdefine _EC_KEY_set_public_key_affine_coordinates _ %+ XCRYPTO_PREFIX %+ _EC_KEY_set_public_key_affine_coordinates
%xdefine _EC_KEY_up_ref _ %+ XCRYPTO_PREFIX %+ _EC_KEY_up_ref
%xdefine _EC_METHOD_get_field_type _ %+ XCRYPTO_PREFIX %+ _EC_METHOD_get_field_type
%xdefine _EC_POINT_add _ %+ XCRYPTO_PREFIX %+ _EC_POINT_add
%xdefine _EC_POINT_clear_free _ %+ XCRYPTO_PREFIX %+ _EC_POINT_clear_free
%xdefine _EC_POINT_cmp _ %+ XCRYPTO_PREFIX %+ _EC_POINT_cmp
%xdefine _EC_POINT_copy _ %+ XCRYPTO_PREFIX %+ _EC_POINT_copy
%xdefine _EC_POINT_dbl _ %+ XCRYPTO_PREFIX %+ _EC_POINT_dbl
%xdefine _EC_POINT_dup _ %+ XCRYPTO_PREFIX %+ _EC_POINT_dup
%xdefine _EC_POINT_free _ %+ XCRYPTO_PREFIX %+ _EC_POINT_free
%xdefine _EC_POINT_get_affine_coordinates_GFp _ %+ XCRYPTO_PREFIX %+ _EC_POINT_get_affine_coordinates_GFp
%xdefine _EC_POINT_invert _ %+ XCRYPTO_PREFIX %+ _EC_POINT_invert
%xdefine _EC_POINT_is_at_infinity _ %+ XCRYPTO_PREFIX %+ _EC_POINT_is_at_infinity
%xdefine _EC_POINT_is_on_curve _ %+ XCRYPTO_PREFIX %+ _EC_POINT_is_on_curve
%xdefine _EC_POINT_mul _ %+ XCRYPTO_PREFIX %+ _EC_POINT_mul
%xdefine _EC_POINT_new _ %+ XCRYPTO_PREFIX %+ _EC_POINT_new
%xdefine _EC_POINT_oct2point _ %+ XCRYPTO_PREFIX %+ _EC_POINT_oct2point
%xdefine _EC_POINT_point2cbb _ %+ XCRYPTO_PREFIX %+ _EC_POINT_point2cbb
%xdefine _EC_POINT_point2oct _ %+ XCRYPTO_PREFIX %+ _EC_POINT_point2oct
%xdefine _EC_POINT_set_affine_coordinates_GFp _ %+ XCRYPTO_PREFIX %+ _EC_POINT_set_affine_coordinates_GFp
%xdefine _EC_POINT_set_compressed_coordinates_GFp _ %+ XCRYPTO_PREFIX %+ _EC_POINT_set_compressed_coordinates_GFp
%xdefine _EC_POINT_set_to_infinity _ %+ XCRYPTO_PREFIX %+ _EC_POINT_set_to_infinity
%xdefine _EC_curve_nid2nist _ %+ XCRYPTO_PREFIX %+ _EC_curve_nid2nist
%xdefine _EC_curve_nist2nid _ %+ XCRYPTO_PREFIX %+ _EC_curve_nist2nid
%xdefine _EC_get_builtin_curves _ %+ XCRYPTO_PREFIX %+ _EC_get_builtin_curves
%xdefine _ED25519_keypair _ %+ XCRYPTO_PREFIX %+ _ED25519_keypair
%xdefine _ED25519_keypair_from_seed _ %+ XCRYPTO_PREFIX %+ _ED25519_keypair_from_seed
%xdefine _ED25519_sign _ %+ XCRYPTO_PREFIX %+ _ED25519_sign
%xdefine _ED25519_verify _ %+ XCRYPTO_PREFIX %+ _ED25519_verify
%xdefine _EDIPARTYNAME_free _ %+ XCRYPTO_PREFIX %+ _EDIPARTYNAME_free
%xdefine _EDIPARTYNAME_it _ %+ XCRYPTO_PREFIX %+ _EDIPARTYNAME_it
%xdefine _EDIPARTYNAME_new _ %+ XCRYPTO_PREFIX %+ _EDIPARTYNAME_new
%xdefine _ENGINE_free _ %+ XCRYPTO_PREFIX %+ _ENGINE_free
%xdefine _ENGINE_get_ECDSA_method _ %+ XCRYPTO_PREFIX %+ _ENGINE_get_ECDSA_method
%xdefine _ENGINE_get_RSA_method _ %+ XCRYPTO_PREFIX %+ _ENGINE_get_RSA_method
%xdefine _ENGINE_load_builtin_engines _ %+ XCRYPTO_PREFIX %+ _ENGINE_load_builtin_engines
%xdefine _ENGINE_new _ %+ XCRYPTO_PREFIX %+ _ENGINE_new
%xdefine _ENGINE_register_all_complete _ %+ XCRYPTO_PREFIX %+ _ENGINE_register_all_complete
%xdefine _ENGINE_set_ECDSA_method _ %+ XCRYPTO_PREFIX %+ _ENGINE_set_ECDSA_method
%xdefine _ENGINE_set_RSA_method _ %+ XCRYPTO_PREFIX %+ _ENGINE_set_RSA_method
%xdefine _ERR_SAVE_STATE_free _ %+ XCRYPTO_PREFIX %+ _ERR_SAVE_STATE_free
%xdefine _ERR_add_error_data _ %+ XCRYPTO_PREFIX %+ _ERR_add_error_data
%xdefine _ERR_add_error_dataf _ %+ XCRYPTO_PREFIX %+ _ERR_add_error_dataf
%xdefine _ERR_clear_error _ %+ XCRYPTO_PREFIX %+ _ERR_clear_error
%xdefine _ERR_clear_system_error _ %+ XCRYPTO_PREFIX %+ _ERR_clear_system_error
%xdefine _ERR_error_string _ %+ XCRYPTO_PREFIX %+ _ERR_error_string
%xdefine _ERR_error_string_n _ %+ XCRYPTO_PREFIX %+ _ERR_error_string_n
%xdefine _ERR_free_strings _ %+ XCRYPTO_PREFIX %+ _ERR_free_strings
%xdefine _ERR_func_error_string _ %+ XCRYPTO_PREFIX %+ _ERR_func_error_string
%xdefine _ERR_get_error _ %+ XCRYPTO_PREFIX %+ _ERR_get_error
%xdefine _ERR_get_error_line _ %+ XCRYPTO_PREFIX %+ _ERR_get_error_line
%xdefine _ERR_get_error_line_data _ %+ XCRYPTO_PREFIX %+ _ERR_get_error_line_data
%xdefine _ERR_get_next_error_library _ %+ XCRYPTO_PREFIX %+ _ERR_get_next_error_library
%xdefine _ERR_lib_error_string _ %+ XCRYPTO_PREFIX %+ _ERR_lib_error_string
%xdefine _ERR_load_BIO_strings _ %+ XCRYPTO_PREFIX %+ _ERR_load_BIO_strings
%xdefine _ERR_load_ERR_strings _ %+ XCRYPTO_PREFIX %+ _ERR_load_ERR_strings
%xdefine _ERR_load_RAND_strings _ %+ XCRYPTO_PREFIX %+ _ERR_load_RAND_strings
%xdefine _ERR_load_SSL_strings _ %+ XCRYPTO_PREFIX %+ _ERR_load_SSL_strings
%xdefine _ERR_load_crypto_strings _ %+ XCRYPTO_PREFIX %+ _ERR_load_crypto_strings
%xdefine _ERR_peek_error _ %+ XCRYPTO_PREFIX %+ _ERR_peek_error
%xdefine _ERR_peek_error_line _ %+ XCRYPTO_PREFIX %+ _ERR_peek_error_line
%xdefine _ERR_peek_error_line_data _ %+ XCRYPTO_PREFIX %+ _ERR_peek_error_line_data
%xdefine _ERR_peek_last_error _ %+ XCRYPTO_PREFIX %+ _ERR_peek_last_error
%xdefine _ERR_peek_last_error_line _ %+ XCRYPTO_PREFIX %+ _ERR_peek_last_error_line
%xdefine _ERR_peek_last_error_line_data _ %+ XCRYPTO_PREFIX %+ _ERR_peek_last_error_line_data
%xdefine _ERR_pop_to_mark _ %+ XCRYPTO_PREFIX %+ _ERR_pop_to_mark
%xdefine _ERR_print_errors _ %+ XCRYPTO_PREFIX %+ _ERR_print_errors
%xdefine _ERR_print_errors_cb _ %+ XCRYPTO_PREFIX %+ _ERR_print_errors_cb
%xdefine _ERR_print_errors_fp _ %+ XCRYPTO_PREFIX %+ _ERR_print_errors_fp
%xdefine _ERR_put_error _ %+ XCRYPTO_PREFIX %+ _ERR_put_error
%xdefine _ERR_reason_error_string _ %+ XCRYPTO_PREFIX %+ _ERR_reason_error_string
%xdefine _ERR_remove_state _ %+ XCRYPTO_PREFIX %+ _ERR_remove_state
%xdefine _ERR_remove_thread_state _ %+ XCRYPTO_PREFIX %+ _ERR_remove_thread_state
%xdefine _ERR_restore_state _ %+ XCRYPTO_PREFIX %+ _ERR_restore_state
%xdefine _ERR_save_state _ %+ XCRYPTO_PREFIX %+ _ERR_save_state
%xdefine _ERR_set_mark _ %+ XCRYPTO_PREFIX %+ _ERR_set_mark
%xdefine _EVP_AEAD_CTX_aead _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_aead
%xdefine _EVP_AEAD_CTX_cleanup _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_cleanup
%xdefine _EVP_AEAD_CTX_free _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_free
%xdefine _EVP_AEAD_CTX_get_iv _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_get_iv
%xdefine _EVP_AEAD_CTX_init _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_init
%xdefine _EVP_AEAD_CTX_init_with_direction _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_init_with_direction
%xdefine _EVP_AEAD_CTX_new _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_new
%xdefine _EVP_AEAD_CTX_open _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_open
%xdefine _EVP_AEAD_CTX_open_gather _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_open_gather
%xdefine _EVP_AEAD_CTX_seal _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_seal
%xdefine _EVP_AEAD_CTX_seal_scatter _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_seal_scatter
%xdefine _EVP_AEAD_CTX_tag_len _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_tag_len
%xdefine _EVP_AEAD_CTX_zero _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_zero
%xdefine _EVP_AEAD_key_length _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_key_length
%xdefine _EVP_AEAD_max_overhead _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_max_overhead
%xdefine _EVP_AEAD_max_tag_len _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_max_tag_len
%xdefine _EVP_AEAD_nonce_length _ %+ XCRYPTO_PREFIX %+ _EVP_AEAD_nonce_length
%xdefine _EVP_BytesToKey _ %+ XCRYPTO_PREFIX %+ _EVP_BytesToKey
%xdefine _EVP_CIPHER_CTX_block_size _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_block_size
%xdefine _EVP_CIPHER_CTX_cipher _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_cipher
%xdefine _EVP_CIPHER_CTX_cleanup _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_cleanup
%xdefine _EVP_CIPHER_CTX_copy _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_copy
%xdefine _EVP_CIPHER_CTX_ctrl _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_ctrl
%xdefine _EVP_CIPHER_CTX_encrypting _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_encrypting
%xdefine _EVP_CIPHER_CTX_flags _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_flags
%xdefine _EVP_CIPHER_CTX_free _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_free
%xdefine _EVP_CIPHER_CTX_get_app_data _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_get_app_data
%xdefine _EVP_CIPHER_CTX_init _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_init
%xdefine _EVP_CIPHER_CTX_iv_length _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_iv_length
%xdefine _EVP_CIPHER_CTX_key_length _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_key_length
%xdefine _EVP_CIPHER_CTX_mode _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_mode
%xdefine _EVP_CIPHER_CTX_new _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_new
%xdefine _EVP_CIPHER_CTX_nid _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_nid
%xdefine _EVP_CIPHER_CTX_reset _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_reset
%xdefine _EVP_CIPHER_CTX_set_app_data _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_app_data
%xdefine _EVP_CIPHER_CTX_set_flags _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_flags
%xdefine _EVP_CIPHER_CTX_set_key_length _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_key_length
%xdefine _EVP_CIPHER_CTX_set_padding _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_padding
%xdefine _EVP_CIPHER_block_size _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_block_size
%xdefine _EVP_CIPHER_flags _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_flags
%xdefine _EVP_CIPHER_iv_length _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_iv_length
%xdefine _EVP_CIPHER_key_length _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_key_length
%xdefine _EVP_CIPHER_mode _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_mode
%xdefine _EVP_CIPHER_nid _ %+ XCRYPTO_PREFIX %+ _EVP_CIPHER_nid
%xdefine _EVP_Cipher _ %+ XCRYPTO_PREFIX %+ _EVP_Cipher
%xdefine _EVP_CipherFinal_ex _ %+ XCRYPTO_PREFIX %+ _EVP_CipherFinal_ex
%xdefine _EVP_CipherInit _ %+ XCRYPTO_PREFIX %+ _EVP_CipherInit
%xdefine _EVP_CipherInit_ex _ %+ XCRYPTO_PREFIX %+ _EVP_CipherInit_ex
%xdefine _EVP_CipherUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_CipherUpdate
%xdefine _EVP_DecodeBase64 _ %+ XCRYPTO_PREFIX %+ _EVP_DecodeBase64
%xdefine _EVP_DecodeBlock _ %+ XCRYPTO_PREFIX %+ _EVP_DecodeBlock
%xdefine _EVP_DecodeFinal _ %+ XCRYPTO_PREFIX %+ _EVP_DecodeFinal
%xdefine _EVP_DecodeInit _ %+ XCRYPTO_PREFIX %+ _EVP_DecodeInit
%xdefine _EVP_DecodeUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_DecodeUpdate
%xdefine _EVP_DecodedLength _ %+ XCRYPTO_PREFIX %+ _EVP_DecodedLength
%xdefine _EVP_DecryptFinal_ex _ %+ XCRYPTO_PREFIX %+ _EVP_DecryptFinal_ex
%xdefine _EVP_DecryptInit _ %+ XCRYPTO_PREFIX %+ _EVP_DecryptInit
%xdefine _EVP_DecryptInit_ex _ %+ XCRYPTO_PREFIX %+ _EVP_DecryptInit_ex
%xdefine _EVP_DecryptUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_DecryptUpdate
%xdefine _EVP_Digest _ %+ XCRYPTO_PREFIX %+ _EVP_Digest
%xdefine _EVP_DigestFinal _ %+ XCRYPTO_PREFIX %+ _EVP_DigestFinal
%xdefine _EVP_DigestFinalXOF _ %+ XCRYPTO_PREFIX %+ _EVP_DigestFinalXOF
%xdefine _EVP_DigestFinal_ex _ %+ XCRYPTO_PREFIX %+ _EVP_DigestFinal_ex
%xdefine _EVP_DigestInit _ %+ XCRYPTO_PREFIX %+ _EVP_DigestInit
%xdefine _EVP_DigestInit_ex _ %+ XCRYPTO_PREFIX %+ _EVP_DigestInit_ex
%xdefine _EVP_DigestSign _ %+ XCRYPTO_PREFIX %+ _EVP_DigestSign
%xdefine _EVP_DigestSignFinal _ %+ XCRYPTO_PREFIX %+ _EVP_DigestSignFinal
%xdefine _EVP_DigestSignInit _ %+ XCRYPTO_PREFIX %+ _EVP_DigestSignInit
%xdefine _EVP_DigestSignUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_DigestSignUpdate
%xdefine _EVP_DigestUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_DigestUpdate
%xdefine _EVP_DigestVerify _ %+ XCRYPTO_PREFIX %+ _EVP_DigestVerify
%xdefine _EVP_DigestVerifyFinal _ %+ XCRYPTO_PREFIX %+ _EVP_DigestVerifyFinal
%xdefine _EVP_DigestVerifyInit _ %+ XCRYPTO_PREFIX %+ _EVP_DigestVerifyInit
%xdefine _EVP_DigestVerifyUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_DigestVerifyUpdate
%xdefine _EVP_EncodeBlock _ %+ XCRYPTO_PREFIX %+ _EVP_EncodeBlock
%xdefine _EVP_EncodeFinal _ %+ XCRYPTO_PREFIX %+ _EVP_EncodeFinal
%xdefine _EVP_EncodeInit _ %+ XCRYPTO_PREFIX %+ _EVP_EncodeInit
%xdefine _EVP_EncodeUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_EncodeUpdate
%xdefine _EVP_EncodedLength _ %+ XCRYPTO_PREFIX %+ _EVP_EncodedLength
%xdefine _EVP_EncryptFinal_ex _ %+ XCRYPTO_PREFIX %+ _EVP_EncryptFinal_ex
%xdefine _EVP_EncryptInit _ %+ XCRYPTO_PREFIX %+ _EVP_EncryptInit
%xdefine _EVP_EncryptInit_ex _ %+ XCRYPTO_PREFIX %+ _EVP_EncryptInit_ex
%xdefine _EVP_EncryptUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_EncryptUpdate
%xdefine _EVP_MD_CTX_block_size _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_block_size
%xdefine _EVP_MD_CTX_cleanup _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_cleanup
%xdefine _EVP_MD_CTX_copy _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_copy
%xdefine _EVP_MD_CTX_copy_ex _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_copy_ex
%xdefine _EVP_MD_CTX_create _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_create
%xdefine _EVP_MD_CTX_destroy _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_destroy
%xdefine _EVP_MD_CTX_free _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_free
%xdefine _EVP_MD_CTX_init _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_init
%xdefine _EVP_MD_CTX_md _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_md
%xdefine _EVP_MD_CTX_new _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_new
%xdefine _EVP_MD_CTX_reset _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_reset
%xdefine _EVP_MD_CTX_size _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_size
%xdefine _EVP_MD_CTX_type _ %+ XCRYPTO_PREFIX %+ _EVP_MD_CTX_type
%xdefine _EVP_MD_block_size _ %+ XCRYPTO_PREFIX %+ _EVP_MD_block_size
%xdefine _EVP_MD_flags _ %+ XCRYPTO_PREFIX %+ _EVP_MD_flags
%xdefine _EVP_MD_meth_get_flags _ %+ XCRYPTO_PREFIX %+ _EVP_MD_meth_get_flags
%xdefine _EVP_MD_size _ %+ XCRYPTO_PREFIX %+ _EVP_MD_size
%xdefine _EVP_MD_type _ %+ XCRYPTO_PREFIX %+ _EVP_MD_type
%xdefine _EVP_PBE_scrypt _ %+ XCRYPTO_PREFIX %+ _EVP_PBE_scrypt
%xdefine _EVP_PKCS82PKEY _ %+ XCRYPTO_PREFIX %+ _EVP_PKCS82PKEY
%xdefine _EVP_PKEY2PKCS8 _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY2PKCS8
%xdefine _EVP_PKEY_CTX_ctrl _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_ctrl
%xdefine _EVP_PKEY_CTX_dup _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_dup
%xdefine _EVP_PKEY_CTX_free _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_free
%xdefine _EVP_PKEY_CTX_get0_pkey _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get0_pkey
%xdefine _EVP_PKEY_CTX_get0_rsa_oaep_label _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get0_rsa_oaep_label
%xdefine _EVP_PKEY_CTX_get_rsa_mgf1_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_mgf1_md
%xdefine _EVP_PKEY_CTX_get_rsa_oaep_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_oaep_md
%xdefine _EVP_PKEY_CTX_get_rsa_padding _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_padding
%xdefine _EVP_PKEY_CTX_get_rsa_pss_saltlen _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_pss_saltlen
%xdefine _EVP_PKEY_CTX_get_signature_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_signature_md
%xdefine _EVP_PKEY_CTX_new _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_new
%xdefine _EVP_PKEY_CTX_new_id _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_new_id
%xdefine _EVP_PKEY_CTX_set0_rsa_oaep_label _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set0_rsa_oaep_label
%xdefine _EVP_PKEY_CTX_set_ec_param_enc _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_ec_param_enc
%xdefine _EVP_PKEY_CTX_set_ec_paramgen_curve_nid _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_ec_paramgen_curve_nid
%xdefine _EVP_PKEY_CTX_set_rsa_keygen_bits _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_keygen_bits
%xdefine _EVP_PKEY_CTX_set_rsa_keygen_pubexp _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_keygen_pubexp
%xdefine _EVP_PKEY_CTX_set_rsa_mgf1_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_mgf1_md
%xdefine _EVP_PKEY_CTX_set_rsa_oaep_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_oaep_md
%xdefine _EVP_PKEY_CTX_set_rsa_padding _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_padding
%xdefine _EVP_PKEY_CTX_set_rsa_pss_keygen_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_keygen_md
%xdefine _EVP_PKEY_CTX_set_rsa_pss_keygen_mgf1_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_keygen_mgf1_md
%xdefine _EVP_PKEY_CTX_set_rsa_pss_keygen_saltlen _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_keygen_saltlen
%xdefine _EVP_PKEY_CTX_set_rsa_pss_saltlen _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_saltlen
%xdefine _EVP_PKEY_CTX_set_signature_md _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_signature_md
%xdefine _EVP_PKEY_assign _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_assign
%xdefine _EVP_PKEY_assign_DSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_assign_DSA
%xdefine _EVP_PKEY_assign_EC_KEY _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_assign_EC_KEY
%xdefine _EVP_PKEY_assign_RSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_assign_RSA
%xdefine _EVP_PKEY_base_id _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_base_id
%xdefine _EVP_PKEY_bits _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_bits
%xdefine _EVP_PKEY_cmp _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_cmp
%xdefine _EVP_PKEY_cmp_parameters _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_cmp_parameters
%xdefine _EVP_PKEY_copy_parameters _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_copy_parameters
%xdefine _EVP_PKEY_decrypt _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_decrypt
%xdefine _EVP_PKEY_decrypt_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_decrypt_init
%xdefine _EVP_PKEY_derive _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_derive
%xdefine _EVP_PKEY_derive_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_derive_init
%xdefine _EVP_PKEY_derive_set_peer _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_derive_set_peer
%xdefine _EVP_PKEY_encrypt _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_encrypt
%xdefine _EVP_PKEY_encrypt_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_encrypt_init
%xdefine _EVP_PKEY_free _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_free
%xdefine _EVP_PKEY_get0_DH _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get0_DH
%xdefine _EVP_PKEY_get0_DSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get0_DSA
%xdefine _EVP_PKEY_get0_EC_KEY _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get0_EC_KEY
%xdefine _EVP_PKEY_get0_RSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get0_RSA
%xdefine _EVP_PKEY_get1_DH _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get1_DH
%xdefine _EVP_PKEY_get1_DSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get1_DSA
%xdefine _EVP_PKEY_get1_EC_KEY _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get1_EC_KEY
%xdefine _EVP_PKEY_get1_RSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get1_RSA
%xdefine _EVP_PKEY_get1_tls_encodedpoint _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get1_tls_encodedpoint
%xdefine _EVP_PKEY_get_raw_private_key _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get_raw_private_key
%xdefine _EVP_PKEY_get_raw_public_key _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_get_raw_public_key
%xdefine _EVP_PKEY_id _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_id
%xdefine _EVP_PKEY_is_opaque _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_is_opaque
%xdefine _EVP_PKEY_keygen _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_keygen
%xdefine _EVP_PKEY_keygen_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_keygen_init
%xdefine _EVP_PKEY_missing_parameters _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_missing_parameters
%xdefine _EVP_PKEY_new _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_new
%xdefine _EVP_PKEY_new_raw_private_key _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_new_raw_private_key
%xdefine _EVP_PKEY_new_raw_public_key _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_new_raw_public_key
%xdefine _EVP_PKEY_paramgen _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_paramgen
%xdefine _EVP_PKEY_paramgen_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_paramgen_init
%xdefine _EVP_PKEY_print_params _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_print_params
%xdefine _EVP_PKEY_print_private _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_print_private
%xdefine _EVP_PKEY_print_public _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_print_public
%xdefine _EVP_PKEY_set1_DSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_set1_DSA
%xdefine _EVP_PKEY_set1_EC_KEY _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_set1_EC_KEY
%xdefine _EVP_PKEY_set1_RSA _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_set1_RSA
%xdefine _EVP_PKEY_set1_tls_encodedpoint _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_set1_tls_encodedpoint
%xdefine _EVP_PKEY_set_type _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_set_type
%xdefine _EVP_PKEY_sign _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_sign
%xdefine _EVP_PKEY_sign_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_sign_init
%xdefine _EVP_PKEY_size _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_size
%xdefine _EVP_PKEY_type _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_type
%xdefine _EVP_PKEY_up_ref _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_up_ref
%xdefine _EVP_PKEY_verify _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_verify
%xdefine _EVP_PKEY_verify_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_verify_init
%xdefine _EVP_PKEY_verify_recover _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_verify_recover
%xdefine _EVP_PKEY_verify_recover_init _ %+ XCRYPTO_PREFIX %+ _EVP_PKEY_verify_recover_init
%xdefine _EVP_SignFinal _ %+ XCRYPTO_PREFIX %+ _EVP_SignFinal
%xdefine _EVP_SignInit _ %+ XCRYPTO_PREFIX %+ _EVP_SignInit
%xdefine _EVP_SignInit_ex _ %+ XCRYPTO_PREFIX %+ _EVP_SignInit_ex
%xdefine _EVP_SignUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_SignUpdate
%xdefine _EVP_VerifyFinal _ %+ XCRYPTO_PREFIX %+ _EVP_VerifyFinal
%xdefine _EVP_VerifyInit _ %+ XCRYPTO_PREFIX %+ _EVP_VerifyInit
%xdefine _EVP_VerifyInit_ex _ %+ XCRYPTO_PREFIX %+ _EVP_VerifyInit_ex
%xdefine _EVP_VerifyUpdate _ %+ XCRYPTO_PREFIX %+ _EVP_VerifyUpdate
%xdefine _EVP_add_cipher_alias _ %+ XCRYPTO_PREFIX %+ _EVP_add_cipher_alias
%xdefine _EVP_add_digest _ %+ XCRYPTO_PREFIX %+ _EVP_add_digest
%xdefine _EVP_aead_aes_128_cbc_sha1_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_cbc_sha1_tls
%xdefine _EVP_aead_aes_128_cbc_sha1_tls_implicit_iv _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_cbc_sha1_tls_implicit_iv
%xdefine _EVP_aead_aes_128_cbc_sha256_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_cbc_sha256_tls
%xdefine _EVP_aead_aes_128_ccm_bluetooth _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_ccm_bluetooth
%xdefine _EVP_aead_aes_128_ccm_bluetooth_8 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_ccm_bluetooth_8
%xdefine _EVP_aead_aes_128_ctr_hmac_sha256 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_ctr_hmac_sha256
%xdefine _EVP_aead_aes_128_gcm _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm
%xdefine _EVP_aead_aes_128_gcm_siv _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm_siv
%xdefine _EVP_aead_aes_128_gcm_tls12 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm_tls12
%xdefine _EVP_aead_aes_128_gcm_tls13 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm_tls13
%xdefine _EVP_aead_aes_192_gcm _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_192_gcm
%xdefine _EVP_aead_aes_256_cbc_sha1_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha1_tls
%xdefine _EVP_aead_aes_256_cbc_sha1_tls_implicit_iv _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha1_tls_implicit_iv
%xdefine _EVP_aead_aes_256_cbc_sha256_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha256_tls
%xdefine _EVP_aead_aes_256_cbc_sha384_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha384_tls
%xdefine _EVP_aead_aes_256_ctr_hmac_sha256 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_ctr_hmac_sha256
%xdefine _EVP_aead_aes_256_gcm _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm
%xdefine _EVP_aead_aes_256_gcm_siv _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm_siv
%xdefine _EVP_aead_aes_256_gcm_tls12 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm_tls12
%xdefine _EVP_aead_aes_256_gcm_tls13 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm_tls13
%xdefine _EVP_aead_chacha20_poly1305 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_chacha20_poly1305
%xdefine _EVP_aead_des_ede3_cbc_sha1_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_des_ede3_cbc_sha1_tls
%xdefine _EVP_aead_des_ede3_cbc_sha1_tls_implicit_iv _ %+ XCRYPTO_PREFIX %+ _EVP_aead_des_ede3_cbc_sha1_tls_implicit_iv
%xdefine _EVP_aead_null_sha1_tls _ %+ XCRYPTO_PREFIX %+ _EVP_aead_null_sha1_tls
%xdefine _EVP_aead_xchacha20_poly1305 _ %+ XCRYPTO_PREFIX %+ _EVP_aead_xchacha20_poly1305
%xdefine _EVP_aes_128_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_aes_128_cbc
%xdefine _EVP_aes_128_ctr _ %+ XCRYPTO_PREFIX %+ _EVP_aes_128_ctr
%xdefine _EVP_aes_128_ecb _ %+ XCRYPTO_PREFIX %+ _EVP_aes_128_ecb
%xdefine _EVP_aes_128_gcm _ %+ XCRYPTO_PREFIX %+ _EVP_aes_128_gcm
%xdefine _EVP_aes_128_ofb _ %+ XCRYPTO_PREFIX %+ _EVP_aes_128_ofb
%xdefine _EVP_aes_192_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_aes_192_cbc
%xdefine _EVP_aes_192_ctr _ %+ XCRYPTO_PREFIX %+ _EVP_aes_192_ctr
%xdefine _EVP_aes_192_ecb _ %+ XCRYPTO_PREFIX %+ _EVP_aes_192_ecb
%xdefine _EVP_aes_192_gcm _ %+ XCRYPTO_PREFIX %+ _EVP_aes_192_gcm
%xdefine _EVP_aes_192_ofb _ %+ XCRYPTO_PREFIX %+ _EVP_aes_192_ofb
%xdefine _EVP_aes_256_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_aes_256_cbc
%xdefine _EVP_aes_256_ctr _ %+ XCRYPTO_PREFIX %+ _EVP_aes_256_ctr
%xdefine _EVP_aes_256_ecb _ %+ XCRYPTO_PREFIX %+ _EVP_aes_256_ecb
%xdefine _EVP_aes_256_gcm _ %+ XCRYPTO_PREFIX %+ _EVP_aes_256_gcm
%xdefine _EVP_aes_256_ofb _ %+ XCRYPTO_PREFIX %+ _EVP_aes_256_ofb
%xdefine _EVP_cleanup _ %+ XCRYPTO_PREFIX %+ _EVP_cleanup
%xdefine _EVP_des_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_des_cbc
%xdefine _EVP_des_ecb _ %+ XCRYPTO_PREFIX %+ _EVP_des_ecb
%xdefine _EVP_des_ede _ %+ XCRYPTO_PREFIX %+ _EVP_des_ede
%xdefine _EVP_des_ede3 _ %+ XCRYPTO_PREFIX %+ _EVP_des_ede3
%xdefine _EVP_des_ede3_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_des_ede3_cbc
%xdefine _EVP_des_ede3_ecb _ %+ XCRYPTO_PREFIX %+ _EVP_des_ede3_ecb
%xdefine _EVP_des_ede_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_des_ede_cbc
%xdefine _EVP_enc_null _ %+ XCRYPTO_PREFIX %+ _EVP_enc_null
%xdefine _EVP_get_cipherbyname _ %+ XCRYPTO_PREFIX %+ _EVP_get_cipherbyname
%xdefine _EVP_get_cipherbynid _ %+ XCRYPTO_PREFIX %+ _EVP_get_cipherbynid
%xdefine _EVP_get_digestbyname _ %+ XCRYPTO_PREFIX %+ _EVP_get_digestbyname
%xdefine _EVP_get_digestbynid _ %+ XCRYPTO_PREFIX %+ _EVP_get_digestbynid
%xdefine _EVP_get_digestbyobj _ %+ XCRYPTO_PREFIX %+ _EVP_get_digestbyobj
%xdefine _EVP_has_aes_hardware _ %+ XCRYPTO_PREFIX %+ _EVP_has_aes_hardware
%xdefine _EVP_marshal_digest_algorithm _ %+ XCRYPTO_PREFIX %+ _EVP_marshal_digest_algorithm
%xdefine _EVP_marshal_private_key _ %+ XCRYPTO_PREFIX %+ _EVP_marshal_private_key
%xdefine _EVP_marshal_public_key _ %+ XCRYPTO_PREFIX %+ _EVP_marshal_public_key
%xdefine _EVP_md4 _ %+ XCRYPTO_PREFIX %+ _EVP_md4
%xdefine _EVP_md5 _ %+ XCRYPTO_PREFIX %+ _EVP_md5
%xdefine _EVP_md5_sha1 _ %+ XCRYPTO_PREFIX %+ _EVP_md5_sha1
%xdefine _EVP_parse_digest_algorithm _ %+ XCRYPTO_PREFIX %+ _EVP_parse_digest_algorithm
%xdefine _EVP_parse_private_key _ %+ XCRYPTO_PREFIX %+ _EVP_parse_private_key
%xdefine _EVP_parse_public_key _ %+ XCRYPTO_PREFIX %+ _EVP_parse_public_key
%xdefine _EVP_rc2_40_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_rc2_40_cbc
%xdefine _EVP_rc2_cbc _ %+ XCRYPTO_PREFIX %+ _EVP_rc2_cbc
%xdefine _EVP_rc4 _ %+ XCRYPTO_PREFIX %+ _EVP_rc4
%xdefine _EVP_sha1 _ %+ XCRYPTO_PREFIX %+ _EVP_sha1
%xdefine _EVP_sha224 _ %+ XCRYPTO_PREFIX %+ _EVP_sha224
%xdefine _EVP_sha256 _ %+ XCRYPTO_PREFIX %+ _EVP_sha256
%xdefine _EVP_sha384 _ %+ XCRYPTO_PREFIX %+ _EVP_sha384
%xdefine _EVP_sha512 _ %+ XCRYPTO_PREFIX %+ _EVP_sha512
%xdefine _EVP_sha512_256 _ %+ XCRYPTO_PREFIX %+ _EVP_sha512_256
%xdefine _EVP_tls_cbc_copy_mac _ %+ XCRYPTO_PREFIX %+ _EVP_tls_cbc_copy_mac
%xdefine _EVP_tls_cbc_digest_record _ %+ XCRYPTO_PREFIX %+ _EVP_tls_cbc_digest_record
%xdefine _EVP_tls_cbc_record_digest_supported _ %+ XCRYPTO_PREFIX %+ _EVP_tls_cbc_record_digest_supported
%xdefine _EVP_tls_cbc_remove_padding _ %+ XCRYPTO_PREFIX %+ _EVP_tls_cbc_remove_padding
%xdefine _EXTENDED_KEY_USAGE_free _ %+ XCRYPTO_PREFIX %+ _EXTENDED_KEY_USAGE_free
%xdefine _EXTENDED_KEY_USAGE_it _ %+ XCRYPTO_PREFIX %+ _EXTENDED_KEY_USAGE_it
%xdefine _EXTENDED_KEY_USAGE_new _ %+ XCRYPTO_PREFIX %+ _EXTENDED_KEY_USAGE_new
%xdefine _FIPS_mode _ %+ XCRYPTO_PREFIX %+ _FIPS_mode
%xdefine _FIPS_mode_set _ %+ XCRYPTO_PREFIX %+ _FIPS_mode_set
%xdefine _GENERAL_NAMES_free _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAMES_free
%xdefine _GENERAL_NAMES_it _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAMES_it
%xdefine _GENERAL_NAMES_new _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAMES_new
%xdefine _GENERAL_NAME_cmp _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_cmp
%xdefine _GENERAL_NAME_dup _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_dup
%xdefine _GENERAL_NAME_free _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_free
%xdefine _GENERAL_NAME_get0_otherName _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_get0_otherName
%xdefine _GENERAL_NAME_get0_value _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_get0_value
%xdefine _GENERAL_NAME_it _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_it
%xdefine _GENERAL_NAME_new _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_new
%xdefine _GENERAL_NAME_print _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_print
%xdefine _GENERAL_NAME_set0_othername _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_set0_othername
%xdefine _GENERAL_NAME_set0_value _ %+ XCRYPTO_PREFIX %+ _GENERAL_NAME_set0_value
%xdefine _GENERAL_SUBTREE_free _ %+ XCRYPTO_PREFIX %+ _GENERAL_SUBTREE_free
%xdefine _GENERAL_SUBTREE_it _ %+ XCRYPTO_PREFIX %+ _GENERAL_SUBTREE_it
%xdefine _GENERAL_SUBTREE_new _ %+ XCRYPTO_PREFIX %+ _GENERAL_SUBTREE_new
%xdefine _HKDF _ %+ XCRYPTO_PREFIX %+ _HKDF
%xdefine _HKDF_expand _ %+ XCRYPTO_PREFIX %+ _HKDF_expand
%xdefine _HKDF_extract _ %+ XCRYPTO_PREFIX %+ _HKDF_extract
%xdefine _HMAC _ %+ XCRYPTO_PREFIX %+ _HMAC
%xdefine _HMAC_CTX_cleanup _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_cleanup
%xdefine _HMAC_CTX_copy _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_copy
%xdefine _HMAC_CTX_copy_ex _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_copy_ex
%xdefine _HMAC_CTX_free _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_free
%xdefine _HMAC_CTX_init _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_init
%xdefine _HMAC_CTX_new _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_new
%xdefine _HMAC_CTX_reset _ %+ XCRYPTO_PREFIX %+ _HMAC_CTX_reset
%xdefine _HMAC_Final _ %+ XCRYPTO_PREFIX %+ _HMAC_Final
%xdefine _HMAC_Init _ %+ XCRYPTO_PREFIX %+ _HMAC_Init
%xdefine _HMAC_Init_ex _ %+ XCRYPTO_PREFIX %+ _HMAC_Init_ex
%xdefine _HMAC_Update _ %+ XCRYPTO_PREFIX %+ _HMAC_Update
%xdefine _HMAC_size _ %+ XCRYPTO_PREFIX %+ _HMAC_size
%xdefine _HRSS_decap _ %+ XCRYPTO_PREFIX %+ _HRSS_decap
%xdefine _HRSS_encap _ %+ XCRYPTO_PREFIX %+ _HRSS_encap
%xdefine _HRSS_generate_key _ %+ XCRYPTO_PREFIX %+ _HRSS_generate_key
%xdefine _HRSS_marshal_public_key _ %+ XCRYPTO_PREFIX %+ _HRSS_marshal_public_key
%xdefine _HRSS_parse_public_key _ %+ XCRYPTO_PREFIX %+ _HRSS_parse_public_key
%xdefine _HRSS_poly3_invert _ %+ XCRYPTO_PREFIX %+ _HRSS_poly3_invert
%xdefine _HRSS_poly3_mul _ %+ XCRYPTO_PREFIX %+ _HRSS_poly3_mul
%xdefine _ISSUING_DIST_POINT_free _ %+ XCRYPTO_PREFIX %+ _ISSUING_DIST_POINT_free
%xdefine _ISSUING_DIST_POINT_it _ %+ XCRYPTO_PREFIX %+ _ISSUING_DIST_POINT_it
%xdefine _ISSUING_DIST_POINT_new _ %+ XCRYPTO_PREFIX %+ _ISSUING_DIST_POINT_new
%xdefine _MD4 _ %+ XCRYPTO_PREFIX %+ _MD4
%xdefine _MD4_Final _ %+ XCRYPTO_PREFIX %+ _MD4_Final
%xdefine _MD4_Init _ %+ XCRYPTO_PREFIX %+ _MD4_Init
%xdefine _MD4_Transform _ %+ XCRYPTO_PREFIX %+ _MD4_Transform
%xdefine _MD4_Update _ %+ XCRYPTO_PREFIX %+ _MD4_Update
%xdefine _MD5 _ %+ XCRYPTO_PREFIX %+ _MD5
%xdefine _MD5_Final _ %+ XCRYPTO_PREFIX %+ _MD5_Final
%xdefine _MD5_Init _ %+ XCRYPTO_PREFIX %+ _MD5_Init
%xdefine _MD5_Transform _ %+ XCRYPTO_PREFIX %+ _MD5_Transform
%xdefine _MD5_Update _ %+ XCRYPTO_PREFIX %+ _MD5_Update
%xdefine _METHOD_ref _ %+ XCRYPTO_PREFIX %+ _METHOD_ref
%xdefine _METHOD_unref _ %+ XCRYPTO_PREFIX %+ _METHOD_unref
%xdefine _NAME_CONSTRAINTS_check _ %+ XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_check
%xdefine _NAME_CONSTRAINTS_free _ %+ XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_free
%xdefine _NAME_CONSTRAINTS_it _ %+ XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_it
%xdefine _NAME_CONSTRAINTS_new _ %+ XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_new
%xdefine _NCONF_free _ %+ XCRYPTO_PREFIX %+ _NCONF_free
%xdefine _NCONF_get_section _ %+ XCRYPTO_PREFIX %+ _NCONF_get_section
%xdefine _NCONF_get_string _ %+ XCRYPTO_PREFIX %+ _NCONF_get_string
%xdefine _NCONF_load _ %+ XCRYPTO_PREFIX %+ _NCONF_load
%xdefine _NCONF_load_bio _ %+ XCRYPTO_PREFIX %+ _NCONF_load_bio
%xdefine _NCONF_new _ %+ XCRYPTO_PREFIX %+ _NCONF_new
%xdefine _NETSCAPE_SPKAC_free _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKAC_free
%xdefine _NETSCAPE_SPKAC_it _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKAC_it
%xdefine _NETSCAPE_SPKAC_new _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKAC_new
%xdefine _NETSCAPE_SPKI_b64_decode _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_b64_decode
%xdefine _NETSCAPE_SPKI_b64_encode _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_b64_encode
%xdefine _NETSCAPE_SPKI_free _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_free
%xdefine _NETSCAPE_SPKI_get_pubkey _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_get_pubkey
%xdefine _NETSCAPE_SPKI_it _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_it
%xdefine _NETSCAPE_SPKI_new _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_new
%xdefine _NETSCAPE_SPKI_set_pubkey _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_set_pubkey
%xdefine _NETSCAPE_SPKI_sign _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_sign
%xdefine _NETSCAPE_SPKI_verify _ %+ XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_verify
%xdefine _NOTICEREF_free _ %+ XCRYPTO_PREFIX %+ _NOTICEREF_free
%xdefine _NOTICEREF_it _ %+ XCRYPTO_PREFIX %+ _NOTICEREF_it
%xdefine _NOTICEREF_new _ %+ XCRYPTO_PREFIX %+ _NOTICEREF_new
%xdefine _OBJ_cbs2nid _ %+ XCRYPTO_PREFIX %+ _OBJ_cbs2nid
%xdefine _OBJ_cleanup _ %+ XCRYPTO_PREFIX %+ _OBJ_cleanup
%xdefine _OBJ_cmp _ %+ XCRYPTO_PREFIX %+ _OBJ_cmp
%xdefine _OBJ_create _ %+ XCRYPTO_PREFIX %+ _OBJ_create
%xdefine _OBJ_dup _ %+ XCRYPTO_PREFIX %+ _OBJ_dup
%xdefine _OBJ_find_sigid_algs _ %+ XCRYPTO_PREFIX %+ _OBJ_find_sigid_algs
%xdefine _OBJ_find_sigid_by_algs _ %+ XCRYPTO_PREFIX %+ _OBJ_find_sigid_by_algs
%xdefine _OBJ_get0_data _ %+ XCRYPTO_PREFIX %+ _OBJ_get0_data
%xdefine _OBJ_length _ %+ XCRYPTO_PREFIX %+ _OBJ_length
%xdefine _OBJ_ln2nid _ %+ XCRYPTO_PREFIX %+ _OBJ_ln2nid
%xdefine _OBJ_nid2cbb _ %+ XCRYPTO_PREFIX %+ _OBJ_nid2cbb
%xdefine _OBJ_nid2ln _ %+ XCRYPTO_PREFIX %+ _OBJ_nid2ln
%xdefine _OBJ_nid2obj _ %+ XCRYPTO_PREFIX %+ _OBJ_nid2obj
%xdefine _OBJ_nid2sn _ %+ XCRYPTO_PREFIX %+ _OBJ_nid2sn
%xdefine _OBJ_obj2nid _ %+ XCRYPTO_PREFIX %+ _OBJ_obj2nid
%xdefine _OBJ_obj2txt _ %+ XCRYPTO_PREFIX %+ _OBJ_obj2txt
%xdefine _OBJ_sn2nid _ %+ XCRYPTO_PREFIX %+ _OBJ_sn2nid
%xdefine _OBJ_txt2nid _ %+ XCRYPTO_PREFIX %+ _OBJ_txt2nid
%xdefine _OBJ_txt2obj _ %+ XCRYPTO_PREFIX %+ _OBJ_txt2obj
%xdefine _OPENSSL_add_all_algorithms_conf _ %+ XCRYPTO_PREFIX %+ _OPENSSL_add_all_algorithms_conf
%xdefine _XCRYPTO_ARMcap_P _ %+ XCRYPTO_PREFIX %+ _XCRYPTO_ARMcap_P
%xdefine _OPENSSL_built_in_curves _ %+ XCRYPTO_PREFIX %+ _OPENSSL_built_in_curves
%xdefine _OPENSSL_cleanse _ %+ XCRYPTO_PREFIX %+ _OPENSSL_cleanse
%xdefine _OPENSSL_cleanup _ %+ XCRYPTO_PREFIX %+ _OPENSSL_cleanup
%xdefine _OPENSSL_clear_free _ %+ XCRYPTO_PREFIX %+ _OPENSSL_clear_free
%xdefine _OPENSSL_config _ %+ XCRYPTO_PREFIX %+ _OPENSSL_config
%xdefine _OPENSSL_cpuid_setup _ %+ XCRYPTO_PREFIX %+ _OPENSSL_cpuid_setup
%xdefine _OPENSSL_free _ %+ XCRYPTO_PREFIX %+ _OPENSSL_free
%xdefine _OPENSSL_get_armcap_pointer_for_test _ %+ XCRYPTO_PREFIX %+ _OPENSSL_get_armcap_pointer_for_test
%xdefine _OPENSSL_gmtime _ %+ XCRYPTO_PREFIX %+ _OPENSSL_gmtime
%xdefine _OPENSSL_gmtime_adj _ %+ XCRYPTO_PREFIX %+ _OPENSSL_gmtime_adj
%xdefine _OPENSSL_gmtime_diff _ %+ XCRYPTO_PREFIX %+ _OPENSSL_gmtime_diff
%xdefine _OPENSSL_hash32 _ %+ XCRYPTO_PREFIX %+ _OPENSSL_hash32
%xdefine _OPENSSL_ia32cap_P _ %+ XCRYPTO_PREFIX %+ _OPENSSL_ia32cap_P
%xdefine _OPENSSL_init_crypto _ %+ XCRYPTO_PREFIX %+ _OPENSSL_init_crypto
%xdefine _OPENSSL_init_ssl _ %+ XCRYPTO_PREFIX %+ _OPENSSL_init_ssl
%xdefine _OPENSSL_load_builtin_modules _ %+ XCRYPTO_PREFIX %+ _OPENSSL_load_builtin_modules
%xdefine _OPENSSL_malloc _ %+ XCRYPTO_PREFIX %+ _OPENSSL_malloc
%xdefine _OPENSSL_malloc_init _ %+ XCRYPTO_PREFIX %+ _OPENSSL_malloc_init
%xdefine _OPENSSL_memdup _ %+ XCRYPTO_PREFIX %+ _OPENSSL_memdup
%xdefine _OPENSSL_no_config _ %+ XCRYPTO_PREFIX %+ _OPENSSL_no_config
%xdefine _OPENSSL_realloc _ %+ XCRYPTO_PREFIX %+ _OPENSSL_realloc
%xdefine _OPENSSL_strcasecmp _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strcasecmp
%xdefine _OPENSSL_strdup _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strdup
%xdefine _OPENSSL_strlcat _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strlcat
%xdefine _OPENSSL_strlcpy _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strlcpy
%xdefine _OPENSSL_strncasecmp _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strncasecmp
%xdefine _OPENSSL_strndup _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strndup
%xdefine _OPENSSL_strnlen _ %+ XCRYPTO_PREFIX %+ _OPENSSL_strnlen
%xdefine _OPENSSL_tolower _ %+ XCRYPTO_PREFIX %+ _OPENSSL_tolower
%xdefine _OTHERNAME_cmp _ %+ XCRYPTO_PREFIX %+ _OTHERNAME_cmp
%xdefine _OTHERNAME_free _ %+ XCRYPTO_PREFIX %+ _OTHERNAME_free
%xdefine _OTHERNAME_it _ %+ XCRYPTO_PREFIX %+ _OTHERNAME_it
%xdefine _OTHERNAME_new _ %+ XCRYPTO_PREFIX %+ _OTHERNAME_new
%xdefine _OpenSSL_add_all_algorithms _ %+ XCRYPTO_PREFIX %+ _OpenSSL_add_all_algorithms
%xdefine _OpenSSL_add_all_ciphers _ %+ XCRYPTO_PREFIX %+ _OpenSSL_add_all_ciphers
%xdefine _OpenSSL_add_all_digests _ %+ XCRYPTO_PREFIX %+ _OpenSSL_add_all_digests
%xdefine _OpenSSL_version _ %+ XCRYPTO_PREFIX %+ _OpenSSL_version
%xdefine _OpenSSL_version_num _ %+ XCRYPTO_PREFIX %+ _OpenSSL_version_num
%xdefine _PEM_ASN1_read _ %+ XCRYPTO_PREFIX %+ _PEM_ASN1_read
%xdefine _PEM_ASN1_read_bio _ %+ XCRYPTO_PREFIX %+ _PEM_ASN1_read_bio
%xdefine _PEM_ASN1_write _ %+ XCRYPTO_PREFIX %+ _PEM_ASN1_write
%xdefine _PEM_ASN1_write_bio _ %+ XCRYPTO_PREFIX %+ _PEM_ASN1_write_bio
%xdefine _PEM_X509_INFO_read _ %+ XCRYPTO_PREFIX %+ _PEM_X509_INFO_read
%xdefine _PEM_X509_INFO_read_bio _ %+ XCRYPTO_PREFIX %+ _PEM_X509_INFO_read_bio
%xdefine _PEM_X509_INFO_write_bio _ %+ XCRYPTO_PREFIX %+ _PEM_X509_INFO_write_bio
%xdefine _PEM_bytes_read_bio _ %+ XCRYPTO_PREFIX %+ _PEM_bytes_read_bio
%xdefine _PEM_def_callback _ %+ XCRYPTO_PREFIX %+ _PEM_def_callback
%xdefine _PEM_dek_info _ %+ XCRYPTO_PREFIX %+ _PEM_dek_info
%xdefine _PEM_do_header _ %+ XCRYPTO_PREFIX %+ _PEM_do_header
%xdefine _PEM_get_EVP_CIPHER_INFO _ %+ XCRYPTO_PREFIX %+ _PEM_get_EVP_CIPHER_INFO
%xdefine _PEM_proc_type _ %+ XCRYPTO_PREFIX %+ _PEM_proc_type
%xdefine _PEM_read _ %+ XCRYPTO_PREFIX %+ _PEM_read
%xdefine _PEM_read_DHparams _ %+ XCRYPTO_PREFIX %+ _PEM_read_DHparams
%xdefine _PEM_read_DSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_DSAPrivateKey
%xdefine _PEM_read_DSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_DSA_PUBKEY
%xdefine _PEM_read_DSAparams _ %+ XCRYPTO_PREFIX %+ _PEM_read_DSAparams
%xdefine _PEM_read_ECPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_ECPrivateKey
%xdefine _PEM_read_EC_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_EC_PUBKEY
%xdefine _PEM_read_PKCS7 _ %+ XCRYPTO_PREFIX %+ _PEM_read_PKCS7
%xdefine _PEM_read_PKCS8 _ %+ XCRYPTO_PREFIX %+ _PEM_read_PKCS8
%xdefine _PEM_read_PKCS8_PRIV_KEY_INFO _ %+ XCRYPTO_PREFIX %+ _PEM_read_PKCS8_PRIV_KEY_INFO
%xdefine _PEM_read_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_PUBKEY
%xdefine _PEM_read_PrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_PrivateKey
%xdefine _PEM_read_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_RSAPrivateKey
%xdefine _PEM_read_RSAPublicKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_RSAPublicKey
%xdefine _PEM_read_RSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_RSA_PUBKEY
%xdefine _PEM_read_SSL_SESSION _ %+ XCRYPTO_PREFIX %+ _PEM_read_SSL_SESSION
%xdefine _PEM_read_X509 _ %+ XCRYPTO_PREFIX %+ _PEM_read_X509
%xdefine _PEM_read_X509_AUX _ %+ XCRYPTO_PREFIX %+ _PEM_read_X509_AUX
%xdefine _PEM_read_X509_CRL _ %+ XCRYPTO_PREFIX %+ _PEM_read_X509_CRL
%xdefine _PEM_read_X509_REQ _ %+ XCRYPTO_PREFIX %+ _PEM_read_X509_REQ
%xdefine _PEM_read_bio _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio
%xdefine _PEM_read_bio_DHparams _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_DHparams
%xdefine _PEM_read_bio_DSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_DSAPrivateKey
%xdefine _PEM_read_bio_DSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_DSA_PUBKEY
%xdefine _PEM_read_bio_DSAparams _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_DSAparams
%xdefine _PEM_read_bio_ECPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_ECPrivateKey
%xdefine _PEM_read_bio_EC_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_EC_PUBKEY
%xdefine _PEM_read_bio_PKCS7 _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_PKCS7
%xdefine _PEM_read_bio_PKCS8 _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_PKCS8
%xdefine _PEM_read_bio_PKCS8_PRIV_KEY_INFO _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_PKCS8_PRIV_KEY_INFO
%xdefine _PEM_read_bio_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_PUBKEY
%xdefine _PEM_read_bio_PrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_PrivateKey
%xdefine _PEM_read_bio_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_RSAPrivateKey
%xdefine _PEM_read_bio_RSAPublicKey _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_RSAPublicKey
%xdefine _PEM_read_bio_RSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_RSA_PUBKEY
%xdefine _PEM_read_bio_SSL_SESSION _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_SSL_SESSION
%xdefine _PEM_read_bio_X509 _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_X509
%xdefine _PEM_read_bio_X509_AUX _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_X509_AUX
%xdefine _PEM_read_bio_X509_CRL _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_X509_CRL
%xdefine _PEM_read_bio_X509_REQ _ %+ XCRYPTO_PREFIX %+ _PEM_read_bio_X509_REQ
%xdefine _PEM_write _ %+ XCRYPTO_PREFIX %+ _PEM_write
%xdefine _PEM_write_DHparams _ %+ XCRYPTO_PREFIX %+ _PEM_write_DHparams
%xdefine _PEM_write_DSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_DSAPrivateKey
%xdefine _PEM_write_DSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_DSA_PUBKEY
%xdefine _PEM_write_DSAparams _ %+ XCRYPTO_PREFIX %+ _PEM_write_DSAparams
%xdefine _PEM_write_ECPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_ECPrivateKey
%xdefine _PEM_write_EC_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_EC_PUBKEY
%xdefine _PEM_write_PKCS7 _ %+ XCRYPTO_PREFIX %+ _PEM_write_PKCS7
%xdefine _PEM_write_PKCS8 _ %+ XCRYPTO_PREFIX %+ _PEM_write_PKCS8
%xdefine _PEM_write_PKCS8PrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_PKCS8PrivateKey
%xdefine _PEM_write_PKCS8PrivateKey_nid _ %+ XCRYPTO_PREFIX %+ _PEM_write_PKCS8PrivateKey_nid
%xdefine _PEM_write_PKCS8_PRIV_KEY_INFO _ %+ XCRYPTO_PREFIX %+ _PEM_write_PKCS8_PRIV_KEY_INFO
%xdefine _PEM_write_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_PUBKEY
%xdefine _PEM_write_PrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_PrivateKey
%xdefine _PEM_write_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_RSAPrivateKey
%xdefine _PEM_write_RSAPublicKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_RSAPublicKey
%xdefine _PEM_write_RSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_RSA_PUBKEY
%xdefine _PEM_write_SSL_SESSION _ %+ XCRYPTO_PREFIX %+ _PEM_write_SSL_SESSION
%xdefine _PEM_write_X509 _ %+ XCRYPTO_PREFIX %+ _PEM_write_X509
%xdefine _PEM_write_X509_AUX _ %+ XCRYPTO_PREFIX %+ _PEM_write_X509_AUX
%xdefine _PEM_write_X509_CRL _ %+ XCRYPTO_PREFIX %+ _PEM_write_X509_CRL
%xdefine _PEM_write_X509_REQ _ %+ XCRYPTO_PREFIX %+ _PEM_write_X509_REQ
%xdefine _PEM_write_X509_REQ_NEW _ %+ XCRYPTO_PREFIX %+ _PEM_write_X509_REQ_NEW
%xdefine _PEM_write_bio _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio
%xdefine _PEM_write_bio_DHparams _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_DHparams
%xdefine _PEM_write_bio_DSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_DSAPrivateKey
%xdefine _PEM_write_bio_DSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_DSA_PUBKEY
%xdefine _PEM_write_bio_DSAparams _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_DSAparams
%xdefine _PEM_write_bio_ECPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_ECPrivateKey
%xdefine _PEM_write_bio_EC_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_EC_PUBKEY
%xdefine _PEM_write_bio_PKCS7 _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS7
%xdefine _PEM_write_bio_PKCS8 _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8
%xdefine _PEM_write_bio_PKCS8PrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8PrivateKey
%xdefine _PEM_write_bio_PKCS8PrivateKey_nid _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8PrivateKey_nid
%xdefine _PEM_write_bio_PKCS8_PRIV_KEY_INFO _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8_PRIV_KEY_INFO
%xdefine _PEM_write_bio_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PUBKEY
%xdefine _PEM_write_bio_PrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_PrivateKey
%xdefine _PEM_write_bio_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_RSAPrivateKey
%xdefine _PEM_write_bio_RSAPublicKey _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_RSAPublicKey
%xdefine _PEM_write_bio_RSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_RSA_PUBKEY
%xdefine _PEM_write_bio_SSL_SESSION _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_SSL_SESSION
%xdefine _PEM_write_bio_X509 _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_X509
%xdefine _PEM_write_bio_X509_AUX _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_X509_AUX
%xdefine _PEM_write_bio_X509_CRL _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_X509_CRL
%xdefine _PEM_write_bio_X509_REQ _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_X509_REQ
%xdefine _PEM_write_bio_X509_REQ_NEW _ %+ XCRYPTO_PREFIX %+ _PEM_write_bio_X509_REQ_NEW
%xdefine _PKCS12_PBE_add _ %+ XCRYPTO_PREFIX %+ _PKCS12_PBE_add
%xdefine _PKCS12_create _ %+ XCRYPTO_PREFIX %+ _PKCS12_create
%xdefine _PKCS12_free _ %+ XCRYPTO_PREFIX %+ _PKCS12_free
%xdefine _PKCS12_get_key_and_certs _ %+ XCRYPTO_PREFIX %+ _PKCS12_get_key_and_certs
%xdefine _PKCS12_parse _ %+ XCRYPTO_PREFIX %+ _PKCS12_parse
%xdefine _PKCS12_verify_mac _ %+ XCRYPTO_PREFIX %+ _PKCS12_verify_mac
%xdefine _PKCS5_PBKDF2_HMAC _ %+ XCRYPTO_PREFIX %+ _PKCS5_PBKDF2_HMAC
%xdefine _PKCS5_PBKDF2_HMAC_SHA1 _ %+ XCRYPTO_PREFIX %+ _PKCS5_PBKDF2_HMAC_SHA1
%xdefine _PKCS5_pbe2_decrypt_init _ %+ XCRYPTO_PREFIX %+ _PKCS5_pbe2_decrypt_init
%xdefine _PKCS5_pbe2_encrypt_init _ %+ XCRYPTO_PREFIX %+ _PKCS5_pbe2_encrypt_init
%xdefine _PKCS7_bundle_CRLs _ %+ XCRYPTO_PREFIX %+ _PKCS7_bundle_CRLs
%xdefine _PKCS7_bundle_certificates _ %+ XCRYPTO_PREFIX %+ _PKCS7_bundle_certificates
%xdefine _PKCS7_free _ %+ XCRYPTO_PREFIX %+ _PKCS7_free
%xdefine _PKCS7_get_CRLs _ %+ XCRYPTO_PREFIX %+ _PKCS7_get_CRLs
%xdefine _PKCS7_get_PEM_CRLs _ %+ XCRYPTO_PREFIX %+ _PKCS7_get_PEM_CRLs
%xdefine _PKCS7_get_PEM_certificates _ %+ XCRYPTO_PREFIX %+ _PKCS7_get_PEM_certificates
%xdefine _PKCS7_get_certificates _ %+ XCRYPTO_PREFIX %+ _PKCS7_get_certificates
%xdefine _PKCS7_get_raw_certificates _ %+ XCRYPTO_PREFIX %+ _PKCS7_get_raw_certificates
%xdefine _PKCS7_sign _ %+ XCRYPTO_PREFIX %+ _PKCS7_sign
%xdefine _PKCS7_type_is_data _ %+ XCRYPTO_PREFIX %+ _PKCS7_type_is_data
%xdefine _PKCS7_type_is_digest _ %+ XCRYPTO_PREFIX %+ _PKCS7_type_is_digest
%xdefine _PKCS7_type_is_encrypted _ %+ XCRYPTO_PREFIX %+ _PKCS7_type_is_encrypted
%xdefine _PKCS7_type_is_enveloped _ %+ XCRYPTO_PREFIX %+ _PKCS7_type_is_enveloped
%xdefine _PKCS7_type_is_signed _ %+ XCRYPTO_PREFIX %+ _PKCS7_type_is_signed
%xdefine _PKCS7_type_is_signedAndEnveloped _ %+ XCRYPTO_PREFIX %+ _PKCS7_type_is_signedAndEnveloped
%xdefine _PKCS8_PRIV_KEY_INFO_free _ %+ XCRYPTO_PREFIX %+ _PKCS8_PRIV_KEY_INFO_free
%xdefine _PKCS8_PRIV_KEY_INFO_it _ %+ XCRYPTO_PREFIX %+ _PKCS8_PRIV_KEY_INFO_it
%xdefine _PKCS8_PRIV_KEY_INFO_new _ %+ XCRYPTO_PREFIX %+ _PKCS8_PRIV_KEY_INFO_new
%xdefine _PKCS8_decrypt _ %+ XCRYPTO_PREFIX %+ _PKCS8_decrypt
%xdefine _PKCS8_encrypt _ %+ XCRYPTO_PREFIX %+ _PKCS8_encrypt
%xdefine _PKCS8_marshal_encrypted_private_key _ %+ XCRYPTO_PREFIX %+ _PKCS8_marshal_encrypted_private_key
%xdefine _PKCS8_parse_encrypted_private_key _ %+ XCRYPTO_PREFIX %+ _PKCS8_parse_encrypted_private_key
%xdefine _PKCS8_pkey_get0 _ %+ XCRYPTO_PREFIX %+ _PKCS8_pkey_get0
%xdefine _PKCS8_pkey_set0 _ %+ XCRYPTO_PREFIX %+ _PKCS8_pkey_set0
%xdefine _PKEY_USAGE_PERIOD_free _ %+ XCRYPTO_PREFIX %+ _PKEY_USAGE_PERIOD_free
%xdefine _PKEY_USAGE_PERIOD_it _ %+ XCRYPTO_PREFIX %+ _PKEY_USAGE_PERIOD_it
%xdefine _PKEY_USAGE_PERIOD_new _ %+ XCRYPTO_PREFIX %+ _PKEY_USAGE_PERIOD_new
%xdefine _PMBTOKEN_PRETOKEN_free _ %+ XCRYPTO_PREFIX %+ _PMBTOKEN_PRETOKEN_free
%xdefine _POLICYINFO_free _ %+ XCRYPTO_PREFIX %+ _POLICYINFO_free
%xdefine _POLICYINFO_it _ %+ XCRYPTO_PREFIX %+ _POLICYINFO_it
%xdefine _POLICYINFO_new _ %+ XCRYPTO_PREFIX %+ _POLICYINFO_new
%xdefine _POLICYQUALINFO_free _ %+ XCRYPTO_PREFIX %+ _POLICYQUALINFO_free
%xdefine _POLICYQUALINFO_it _ %+ XCRYPTO_PREFIX %+ _POLICYQUALINFO_it
%xdefine _POLICYQUALINFO_new _ %+ XCRYPTO_PREFIX %+ _POLICYQUALINFO_new
%xdefine _POLICY_CONSTRAINTS_free _ %+ XCRYPTO_PREFIX %+ _POLICY_CONSTRAINTS_free
%xdefine _POLICY_CONSTRAINTS_it _ %+ XCRYPTO_PREFIX %+ _POLICY_CONSTRAINTS_it
%xdefine _POLICY_CONSTRAINTS_new _ %+ XCRYPTO_PREFIX %+ _POLICY_CONSTRAINTS_new
%xdefine _POLICY_MAPPINGS_it _ %+ XCRYPTO_PREFIX %+ _POLICY_MAPPINGS_it
%xdefine _POLICY_MAPPING_free _ %+ XCRYPTO_PREFIX %+ _POLICY_MAPPING_free
%xdefine _POLICY_MAPPING_it _ %+ XCRYPTO_PREFIX %+ _POLICY_MAPPING_it
%xdefine _POLICY_MAPPING_new _ %+ XCRYPTO_PREFIX %+ _POLICY_MAPPING_new
%xdefine _PROXY_CERT_INFO_EXTENSION_free _ %+ XCRYPTO_PREFIX %+ _PROXY_CERT_INFO_EXTENSION_free
%xdefine _PROXY_CERT_INFO_EXTENSION_it _ %+ XCRYPTO_PREFIX %+ _PROXY_CERT_INFO_EXTENSION_it
%xdefine _PROXY_CERT_INFO_EXTENSION_new _ %+ XCRYPTO_PREFIX %+ _PROXY_CERT_INFO_EXTENSION_new
%xdefine _PROXY_POLICY_free _ %+ XCRYPTO_PREFIX %+ _PROXY_POLICY_free
%xdefine _PROXY_POLICY_it _ %+ XCRYPTO_PREFIX %+ _PROXY_POLICY_it
%xdefine _PROXY_POLICY_new _ %+ XCRYPTO_PREFIX %+ _PROXY_POLICY_new
%xdefine _RAND_SSLeay _ %+ XCRYPTO_PREFIX %+ _RAND_SSLeay
%xdefine _RAND_add _ %+ XCRYPTO_PREFIX %+ _RAND_add
%xdefine _RAND_bytes _ %+ XCRYPTO_PREFIX %+ _RAND_bytes
%xdefine _RAND_bytes_with_additional_data _ %+ XCRYPTO_PREFIX %+ _RAND_bytes_with_additional_data
%xdefine _RAND_cleanup _ %+ XCRYPTO_PREFIX %+ _RAND_cleanup
%xdefine _RAND_egd _ %+ XCRYPTO_PREFIX %+ _RAND_egd
%xdefine _RAND_enable_fork_unsafe_buffering _ %+ XCRYPTO_PREFIX %+ _RAND_enable_fork_unsafe_buffering
%xdefine _RAND_file_name _ %+ XCRYPTO_PREFIX %+ _RAND_file_name
%xdefine _RAND_get_rand_method _ %+ XCRYPTO_PREFIX %+ _RAND_get_rand_method
%xdefine _RAND_load_file _ %+ XCRYPTO_PREFIX %+ _RAND_load_file
%xdefine _RAND_poll _ %+ XCRYPTO_PREFIX %+ _RAND_poll
%xdefine _RAND_pseudo_bytes _ %+ XCRYPTO_PREFIX %+ _RAND_pseudo_bytes
%xdefine _RAND_seed _ %+ XCRYPTO_PREFIX %+ _RAND_seed
%xdefine _RAND_set_rand_method _ %+ XCRYPTO_PREFIX %+ _RAND_set_rand_method
%xdefine _RAND_set_urandom_fd _ %+ XCRYPTO_PREFIX %+ _RAND_set_urandom_fd
%xdefine _RAND_status _ %+ XCRYPTO_PREFIX %+ _RAND_status
%xdefine _RC4 _ %+ XCRYPTO_PREFIX %+ _RC4
%xdefine _RC4_set_key _ %+ XCRYPTO_PREFIX %+ _RC4_set_key
%xdefine _RSAPrivateKey_dup _ %+ XCRYPTO_PREFIX %+ _RSAPrivateKey_dup
%xdefine _RSAPublicKey_dup _ %+ XCRYPTO_PREFIX %+ _RSAPublicKey_dup
%xdefine _RSAZ_1024_mod_exp_avx2 _ %+ XCRYPTO_PREFIX %+ _RSAZ_1024_mod_exp_avx2
%xdefine _RSA_PSS_PARAMS_free _ %+ XCRYPTO_PREFIX %+ _RSA_PSS_PARAMS_free
%xdefine _RSA_PSS_PARAMS_it _ %+ XCRYPTO_PREFIX %+ _RSA_PSS_PARAMS_it
%xdefine _RSA_PSS_PARAMS_new _ %+ XCRYPTO_PREFIX %+ _RSA_PSS_PARAMS_new
%xdefine _RSA_add_pkcs1_prefix _ %+ XCRYPTO_PREFIX %+ _RSA_add_pkcs1_prefix
%xdefine _RSA_bits _ %+ XCRYPTO_PREFIX %+ _RSA_bits
%xdefine _RSA_blinding_on _ %+ XCRYPTO_PREFIX %+ _RSA_blinding_on
%xdefine _RSA_check_fips _ %+ XCRYPTO_PREFIX %+ _RSA_check_fips
%xdefine _RSA_check_key _ %+ XCRYPTO_PREFIX %+ _RSA_check_key
%xdefine _RSA_decrypt _ %+ XCRYPTO_PREFIX %+ _RSA_decrypt
%xdefine _RSA_default_method _ %+ XCRYPTO_PREFIX %+ _RSA_default_method
%xdefine _RSA_encrypt _ %+ XCRYPTO_PREFIX %+ _RSA_encrypt
%xdefine _RSA_flags _ %+ XCRYPTO_PREFIX %+ _RSA_flags
%xdefine _RSA_free _ %+ XCRYPTO_PREFIX %+ _RSA_free
%xdefine _RSA_generate_key_ex _ %+ XCRYPTO_PREFIX %+ _RSA_generate_key_ex
%xdefine _RSA_generate_key_fips _ %+ XCRYPTO_PREFIX %+ _RSA_generate_key_fips
%xdefine _RSA_get0_crt_params _ %+ XCRYPTO_PREFIX %+ _RSA_get0_crt_params
%xdefine _RSA_get0_d _ %+ XCRYPTO_PREFIX %+ _RSA_get0_d
%xdefine _RSA_get0_dmp1 _ %+ XCRYPTO_PREFIX %+ _RSA_get0_dmp1
%xdefine _RSA_get0_dmq1 _ %+ XCRYPTO_PREFIX %+ _RSA_get0_dmq1
%xdefine _RSA_get0_e _ %+ XCRYPTO_PREFIX %+ _RSA_get0_e
%xdefine _RSA_get0_factors _ %+ XCRYPTO_PREFIX %+ _RSA_get0_factors
%xdefine _RSA_get0_iqmp _ %+ XCRYPTO_PREFIX %+ _RSA_get0_iqmp
%xdefine _RSA_get0_key _ %+ XCRYPTO_PREFIX %+ _RSA_get0_key
%xdefine _RSA_get0_n _ %+ XCRYPTO_PREFIX %+ _RSA_get0_n
%xdefine _RSA_get0_p _ %+ XCRYPTO_PREFIX %+ _RSA_get0_p
%xdefine _RSA_get0_q _ %+ XCRYPTO_PREFIX %+ _RSA_get0_q
%xdefine _RSA_get_ex_data _ %+ XCRYPTO_PREFIX %+ _RSA_get_ex_data
%xdefine _RSA_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _RSA_get_ex_new_index
%xdefine _RSA_is_opaque _ %+ XCRYPTO_PREFIX %+ _RSA_is_opaque
%xdefine _RSA_marshal_private_key _ %+ XCRYPTO_PREFIX %+ _RSA_marshal_private_key
%xdefine _RSA_marshal_public_key _ %+ XCRYPTO_PREFIX %+ _RSA_marshal_public_key
%xdefine _RSA_new _ %+ XCRYPTO_PREFIX %+ _RSA_new
%xdefine _RSA_new_method _ %+ XCRYPTO_PREFIX %+ _RSA_new_method
%xdefine _RSA_padding_add_PKCS1_OAEP_mgf1 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_OAEP_mgf1
%xdefine _RSA_padding_add_PKCS1_PSS_mgf1 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_PSS_mgf1
%xdefine _RSA_padding_add_PKCS1_type_1 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_type_1
%xdefine _RSA_padding_add_PKCS1_type_2 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_type_2
%xdefine _RSA_padding_add_none _ %+ XCRYPTO_PREFIX %+ _RSA_padding_add_none
%xdefine _RSA_padding_check_PKCS1_OAEP_mgf1 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_check_PKCS1_OAEP_mgf1
%xdefine _RSA_padding_check_PKCS1_type_1 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_check_PKCS1_type_1
%xdefine _RSA_padding_check_PKCS1_type_2 _ %+ XCRYPTO_PREFIX %+ _RSA_padding_check_PKCS1_type_2
%xdefine _RSA_parse_private_key _ %+ XCRYPTO_PREFIX %+ _RSA_parse_private_key
%xdefine _RSA_parse_public_key _ %+ XCRYPTO_PREFIX %+ _RSA_parse_public_key
%xdefine _RSA_print _ %+ XCRYPTO_PREFIX %+ _RSA_print
%xdefine _RSA_private_decrypt _ %+ XCRYPTO_PREFIX %+ _RSA_private_decrypt
%xdefine _RSA_private_encrypt _ %+ XCRYPTO_PREFIX %+ _RSA_private_encrypt
%xdefine _RSA_private_key_from_bytes _ %+ XCRYPTO_PREFIX %+ _RSA_private_key_from_bytes
%xdefine _RSA_private_key_to_bytes _ %+ XCRYPTO_PREFIX %+ _RSA_private_key_to_bytes
%xdefine _RSA_private_transform _ %+ XCRYPTO_PREFIX %+ _RSA_private_transform
%xdefine _RSA_public_decrypt _ %+ XCRYPTO_PREFIX %+ _RSA_public_decrypt
%xdefine _RSA_public_encrypt _ %+ XCRYPTO_PREFIX %+ _RSA_public_encrypt
%xdefine _RSA_public_key_from_bytes _ %+ XCRYPTO_PREFIX %+ _RSA_public_key_from_bytes
%xdefine _RSA_public_key_to_bytes _ %+ XCRYPTO_PREFIX %+ _RSA_public_key_to_bytes
%xdefine _RSA_set0_crt_params _ %+ XCRYPTO_PREFIX %+ _RSA_set0_crt_params
%xdefine _RSA_set0_factors _ %+ XCRYPTO_PREFIX %+ _RSA_set0_factors
%xdefine _RSA_set0_key _ %+ XCRYPTO_PREFIX %+ _RSA_set0_key
%xdefine _RSA_set_ex_data _ %+ XCRYPTO_PREFIX %+ _RSA_set_ex_data
%xdefine _RSA_sign _ %+ XCRYPTO_PREFIX %+ _RSA_sign
%xdefine _RSA_sign_pss_mgf1 _ %+ XCRYPTO_PREFIX %+ _RSA_sign_pss_mgf1
%xdefine _RSA_sign_raw _ %+ XCRYPTO_PREFIX %+ _RSA_sign_raw
%xdefine _RSA_size _ %+ XCRYPTO_PREFIX %+ _RSA_size
%xdefine _RSA_up_ref _ %+ XCRYPTO_PREFIX %+ _RSA_up_ref
%xdefine _RSA_verify _ %+ XCRYPTO_PREFIX %+ _RSA_verify
%xdefine _RSA_verify_PKCS1_PSS_mgf1 _ %+ XCRYPTO_PREFIX %+ _RSA_verify_PKCS1_PSS_mgf1
%xdefine _RSA_verify_pss_mgf1 _ %+ XCRYPTO_PREFIX %+ _RSA_verify_pss_mgf1
%xdefine _RSA_verify_raw _ %+ XCRYPTO_PREFIX %+ _RSA_verify_raw
%xdefine _SHA1 _ %+ XCRYPTO_PREFIX %+ _SHA1
%xdefine _SHA1_Final _ %+ XCRYPTO_PREFIX %+ _SHA1_Final
%xdefine _SHA1_Init _ %+ XCRYPTO_PREFIX %+ _SHA1_Init
%xdefine _SHA1_Transform _ %+ XCRYPTO_PREFIX %+ _SHA1_Transform
%xdefine _SHA1_Update _ %+ XCRYPTO_PREFIX %+ _SHA1_Update
%xdefine _SHA224 _ %+ XCRYPTO_PREFIX %+ _SHA224
%xdefine _SHA224_Final _ %+ XCRYPTO_PREFIX %+ _SHA224_Final
%xdefine _SHA224_Init _ %+ XCRYPTO_PREFIX %+ _SHA224_Init
%xdefine _SHA224_Update _ %+ XCRYPTO_PREFIX %+ _SHA224_Update
%xdefine _SHA256 _ %+ XCRYPTO_PREFIX %+ _SHA256
%xdefine _SHA256_Final _ %+ XCRYPTO_PREFIX %+ _SHA256_Final
%xdefine _SHA256_Init _ %+ XCRYPTO_PREFIX %+ _SHA256_Init
%xdefine _SHA256_Transform _ %+ XCRYPTO_PREFIX %+ _SHA256_Transform
%xdefine _SHA256_TransformBlocks _ %+ XCRYPTO_PREFIX %+ _SHA256_TransformBlocks
%xdefine _SHA256_Update _ %+ XCRYPTO_PREFIX %+ _SHA256_Update
%xdefine _SHA384 _ %+ XCRYPTO_PREFIX %+ _SHA384
%xdefine _SHA384_Final _ %+ XCRYPTO_PREFIX %+ _SHA384_Final
%xdefine _SHA384_Init _ %+ XCRYPTO_PREFIX %+ _SHA384_Init
%xdefine _SHA384_Update _ %+ XCRYPTO_PREFIX %+ _SHA384_Update
%xdefine _SHA512 _ %+ XCRYPTO_PREFIX %+ _SHA512
%xdefine _SHA512_256 _ %+ XCRYPTO_PREFIX %+ _SHA512_256
%xdefine _SHA512_256_Final _ %+ XCRYPTO_PREFIX %+ _SHA512_256_Final
%xdefine _SHA512_256_Init _ %+ XCRYPTO_PREFIX %+ _SHA512_256_Init
%xdefine _SHA512_256_Update _ %+ XCRYPTO_PREFIX %+ _SHA512_256_Update
%xdefine _SHA512_Final _ %+ XCRYPTO_PREFIX %+ _SHA512_Final
%xdefine _SHA512_Init _ %+ XCRYPTO_PREFIX %+ _SHA512_Init
%xdefine _SHA512_Transform _ %+ XCRYPTO_PREFIX %+ _SHA512_Transform
%xdefine _SHA512_Update _ %+ XCRYPTO_PREFIX %+ _SHA512_Update
%xdefine _SIPHASH_24 _ %+ XCRYPTO_PREFIX %+ _SIPHASH_24
%xdefine _SPAKE2_CTX_free _ %+ XCRYPTO_PREFIX %+ _SPAKE2_CTX_free
%xdefine _SPAKE2_CTX_new _ %+ XCRYPTO_PREFIX %+ _SPAKE2_CTX_new
%xdefine _SPAKE2_generate_msg _ %+ XCRYPTO_PREFIX %+ _SPAKE2_generate_msg
%xdefine _SPAKE2_process_msg _ %+ XCRYPTO_PREFIX %+ _SPAKE2_process_msg
%xdefine _SSL_CIPHER_description _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_description
%xdefine _SSL_CIPHER_get_auth_nid _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_auth_nid
%xdefine _SSL_CIPHER_get_bits _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_bits
%xdefine _SSL_CIPHER_get_cipher_nid _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_cipher_nid
%xdefine _SSL_CIPHER_get_digest_nid _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_digest_nid
%xdefine _SSL_CIPHER_get_id _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_id
%xdefine _SSL_CIPHER_get_kx_name _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_kx_name
%xdefine _SSL_CIPHER_get_kx_nid _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_kx_nid
%xdefine _SSL_CIPHER_get_max_version _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_max_version
%xdefine _SSL_CIPHER_get_min_version _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_min_version
%xdefine _SSL_CIPHER_get_name _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_name
%xdefine _SSL_CIPHER_get_prf_nid _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_prf_nid
%xdefine _SSL_CIPHER_get_rfc_name _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_rfc_name
%xdefine _SSL_CIPHER_get_value _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_value
%xdefine _SSL_CIPHER_get_version _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_get_version
%xdefine _SSL_CIPHER_is_aead _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_is_aead
%xdefine _SSL_CIPHER_is_block_cipher _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_is_block_cipher
%xdefine _SSL_CIPHER_standard_name _ %+ XCRYPTO_PREFIX %+ _SSL_CIPHER_standard_name
%xdefine _SSL_COMP_add_compression_method _ %+ XCRYPTO_PREFIX %+ _SSL_COMP_add_compression_method
%xdefine _SSL_COMP_free_compression_methods _ %+ XCRYPTO_PREFIX %+ _SSL_COMP_free_compression_methods
%xdefine _SSL_COMP_get0_name _ %+ XCRYPTO_PREFIX %+ _SSL_COMP_get0_name
%xdefine _SSL_COMP_get_compression_methods _ %+ XCRYPTO_PREFIX %+ _SSL_COMP_get_compression_methods
%xdefine _SSL_COMP_get_id _ %+ XCRYPTO_PREFIX %+ _SSL_COMP_get_id
%xdefine _SSL_COMP_get_name _ %+ XCRYPTO_PREFIX %+ _SSL_COMP_get_name
%xdefine _SSL_CTX_add0_chain_cert _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_add0_chain_cert
%xdefine _SSL_CTX_add1_chain_cert _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_add1_chain_cert
%xdefine _SSL_CTX_add_cert_compression_alg _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_add_cert_compression_alg
%xdefine _SSL_CTX_add_client_CA _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_add_client_CA
%xdefine _SSL_CTX_add_extra_chain_cert _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_add_extra_chain_cert
%xdefine _SSL_CTX_add_session _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_add_session
%xdefine _SSL_CTX_check_private_key _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_check_private_key
%xdefine _SSL_CTX_cipher_in_group _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_cipher_in_group
%xdefine _SSL_CTX_clear_chain_certs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_clear_chain_certs
%xdefine _SSL_CTX_clear_extra_chain_certs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_clear_extra_chain_certs
%xdefine _SSL_CTX_clear_mode _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_clear_mode
%xdefine _SSL_CTX_clear_options _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_clear_options
%xdefine _SSL_CTX_enable_ocsp_stapling _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_enable_ocsp_stapling
%xdefine _SSL_CTX_enable_signed_cert_timestamps _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_enable_signed_cert_timestamps
%xdefine _SSL_CTX_enable_tls_channel_id _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_enable_tls_channel_id
%xdefine _SSL_CTX_flush_sessions _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_flush_sessions
%xdefine _SSL_CTX_free _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_free
%xdefine _SSL_CTX_get0_certificate _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get0_certificate
%xdefine _SSL_CTX_get0_chain _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get0_chain
%xdefine _SSL_CTX_get0_chain_certs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get0_chain_certs
%xdefine _SSL_CTX_get0_param _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get0_param
%xdefine _SSL_CTX_get0_privatekey _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get0_privatekey
%xdefine _SSL_CTX_get_cert_store _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_cert_store
%xdefine _SSL_CTX_get_channel_id_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_channel_id_cb
%xdefine _SSL_CTX_get_ciphers _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_ciphers
%xdefine _SSL_CTX_get_client_CA_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_client_CA_list
%xdefine _SSL_CTX_get_default_passwd_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_default_passwd_cb
%xdefine _SSL_CTX_get_default_passwd_cb_userdata _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_default_passwd_cb_userdata
%xdefine _SSL_CTX_get_ex_data _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_ex_data
%xdefine _SSL_CTX_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_ex_new_index
%xdefine _SSL_CTX_get_extra_chain_certs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_extra_chain_certs
%xdefine _SSL_CTX_get_info_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_info_callback
%xdefine _SSL_CTX_get_keylog_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_keylog_callback
%xdefine _SSL_CTX_get_max_cert_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_max_cert_list
%xdefine _SSL_CTX_get_max_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_max_proto_version
%xdefine _SSL_CTX_get_min_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_min_proto_version
%xdefine _SSL_CTX_get_mode _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_mode
%xdefine _SSL_CTX_get_options _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_options
%xdefine _SSL_CTX_get_quiet_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_quiet_shutdown
%xdefine _SSL_CTX_get_read_ahead _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_read_ahead
%xdefine _SSL_CTX_get_session_cache_mode _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_session_cache_mode
%xdefine _SSL_CTX_get_timeout _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_timeout
%xdefine _SSL_CTX_get_tlsext_ticket_keys _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_tlsext_ticket_keys
%xdefine _SSL_CTX_get_verify_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_verify_callback
%xdefine _SSL_CTX_get_verify_depth _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_verify_depth
%xdefine _SSL_CTX_get_verify_mode _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_get_verify_mode
%xdefine _SSL_CTX_load_verify_locations _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_load_verify_locations
%xdefine _SSL_CTX_need_tmp_RSA _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_need_tmp_RSA
%xdefine _SSL_CTX_new _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_new
%xdefine _SSL_CTX_remove_session _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_remove_session
%xdefine _SSL_CTX_sess_accept _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_accept
%xdefine _SSL_CTX_sess_accept_good _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_accept_good
%xdefine _SSL_CTX_sess_accept_renegotiate _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_accept_renegotiate
%xdefine _SSL_CTX_sess_cache_full _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_cache_full
%xdefine _SSL_CTX_sess_cb_hits _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_cb_hits
%xdefine _SSL_CTX_sess_connect _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_connect
%xdefine _SSL_CTX_sess_connect_good _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_connect_good
%xdefine _SSL_CTX_sess_connect_renegotiate _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_connect_renegotiate
%xdefine _SSL_CTX_sess_get_cache_size _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_cache_size
%xdefine _SSL_CTX_sess_get_get_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_get_cb
%xdefine _SSL_CTX_sess_get_new_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_new_cb
%xdefine _SSL_CTX_sess_get_remove_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_remove_cb
%xdefine _SSL_CTX_sess_hits _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_hits
%xdefine _SSL_CTX_sess_misses _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_misses
%xdefine _SSL_CTX_sess_number _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_number
%xdefine _SSL_CTX_sess_set_cache_size _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_cache_size
%xdefine _SSL_CTX_sess_set_get_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_get_cb
%xdefine _SSL_CTX_sess_set_new_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_new_cb
%xdefine _SSL_CTX_sess_set_remove_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_remove_cb
%xdefine _SSL_CTX_sess_timeouts _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_sess_timeouts
%xdefine _SSL_CTX_set0_buffer_pool _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set0_buffer_pool
%xdefine _SSL_CTX_set0_chain _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set0_chain
%xdefine _SSL_CTX_set0_client_CAs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set0_client_CAs
%xdefine _SSL_CTX_set0_verify_cert_store _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set0_verify_cert_store
%xdefine _SSL_CTX_set1_chain _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_chain
%xdefine _SSL_CTX_set1_curves _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_curves
%xdefine _SSL_CTX_set1_curves_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_curves_list
%xdefine _SSL_CTX_set1_param _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_param
%xdefine _SSL_CTX_set1_sigalgs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_sigalgs
%xdefine _SSL_CTX_set1_sigalgs_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_sigalgs_list
%xdefine _SSL_CTX_set1_tls_channel_id _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_tls_channel_id
%xdefine _SSL_CTX_set1_verify_cert_store _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set1_verify_cert_store
%xdefine _SSL_CTX_set_allow_unknown_alpn_protos _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_allow_unknown_alpn_protos
%xdefine _SSL_CTX_set_alpn_protos _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_alpn_protos
%xdefine _SSL_CTX_set_alpn_select_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_alpn_select_cb
%xdefine _SSL_CTX_set_cert_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_cert_cb
%xdefine _SSL_CTX_set_cert_store _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_cert_store
%xdefine _SSL_CTX_set_cert_verify_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_cert_verify_callback
%xdefine _SSL_CTX_set_chain_and_key _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_chain_and_key
%xdefine _SSL_CTX_set_channel_id_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_channel_id_cb
%xdefine _SSL_CTX_set_cipher_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_cipher_list
%xdefine _SSL_CTX_set_client_CA_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_client_CA_list
%xdefine _SSL_CTX_set_client_cert_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_client_cert_cb
%xdefine _SSL_CTX_set_current_time_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_current_time_cb
%xdefine _SSL_CTX_set_custom_verify _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_custom_verify
%xdefine _SSL_CTX_set_default_passwd_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_default_passwd_cb
%xdefine _SSL_CTX_set_default_passwd_cb_userdata _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_default_passwd_cb_userdata
%xdefine _SSL_CTX_set_default_verify_paths _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_default_verify_paths
%xdefine _SSL_CTX_set_dos_protection_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_dos_protection_cb
%xdefine _SSL_CTX_set_early_data_enabled _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_early_data_enabled
%xdefine _SSL_CTX_set_ex_data _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_ex_data
%xdefine _SSL_CTX_set_false_start_allowed_without_alpn _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_false_start_allowed_without_alpn
%xdefine _SSL_CTX_set_grease_enabled _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_grease_enabled
%xdefine _SSL_CTX_set_ignore_tls13_downgrade _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_ignore_tls13_downgrade
%xdefine _SSL_CTX_set_info_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_info_callback
%xdefine _SSL_CTX_set_keylog_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_keylog_callback
%xdefine _SSL_CTX_set_max_cert_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_max_cert_list
%xdefine _SSL_CTX_set_max_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_max_proto_version
%xdefine _SSL_CTX_set_max_send_fragment _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_max_send_fragment
%xdefine _SSL_CTX_set_min_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_min_proto_version
%xdefine _SSL_CTX_set_mode _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_mode
%xdefine _SSL_CTX_set_msg_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_msg_callback
%xdefine _SSL_CTX_set_msg_callback_arg _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_msg_callback_arg
%xdefine _SSL_CTX_set_next_proto_select_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_next_proto_select_cb
%xdefine _SSL_CTX_set_next_protos_advertised_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_next_protos_advertised_cb
%xdefine _SSL_CTX_set_ocsp_response _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_ocsp_response
%xdefine _SSL_CTX_set_options _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_options
%xdefine _SSL_CTX_set_private_key_method _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_private_key_method
%xdefine _SSL_CTX_set_psk_client_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_psk_client_callback
%xdefine _SSL_CTX_set_psk_server_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_psk_server_callback
%xdefine _SSL_CTX_set_purpose _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_purpose
%xdefine _SSL_CTX_set_quic_method _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_quic_method
%xdefine _SSL_CTX_set_quiet_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_quiet_shutdown
%xdefine _SSL_CTX_set_read_ahead _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_read_ahead
%xdefine _SSL_CTX_set_retain_only_sha256_of_client_certs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_retain_only_sha256_of_client_certs
%xdefine _SSL_CTX_set_reverify_on_resume _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_reverify_on_resume
%xdefine _SSL_CTX_set_select_certificate_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_select_certificate_cb
%xdefine _SSL_CTX_set_session_cache_mode _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_session_cache_mode
%xdefine _SSL_CTX_set_session_id_context _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_session_id_context
%xdefine _SSL_CTX_set_session_psk_dhe_timeout _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_session_psk_dhe_timeout
%xdefine _SSL_CTX_set_signed_cert_timestamp_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_signed_cert_timestamp_list
%xdefine _SSL_CTX_set_signing_algorithm_prefs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_signing_algorithm_prefs
%xdefine _SSL_CTX_set_srtp_profiles _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_srtp_profiles
%xdefine _SSL_CTX_set_strict_cipher_list _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_strict_cipher_list
%xdefine _SSL_CTX_set_ticket_aead_method _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_ticket_aead_method
%xdefine _SSL_CTX_set_timeout _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_timeout
%xdefine _SSL_CTX_set_tls_channel_id_enabled _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tls_channel_id_enabled
%xdefine _SSL_CTX_set_tlsext_servername_arg _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_servername_arg
%xdefine _SSL_CTX_set_tlsext_servername_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_servername_callback
%xdefine _SSL_CTX_set_tlsext_status_arg _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_status_arg
%xdefine _SSL_CTX_set_tlsext_status_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_status_cb
%xdefine _SSL_CTX_set_tlsext_ticket_key_cb _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_ticket_key_cb
%xdefine _SSL_CTX_set_tlsext_ticket_keys _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_ticket_keys
%xdefine _SSL_CTX_set_tlsext_use_srtp _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_use_srtp
%xdefine _SSL_CTX_set_tmp_dh _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_dh
%xdefine _SSL_CTX_set_tmp_dh_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_dh_callback
%xdefine _SSL_CTX_set_tmp_ecdh _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_ecdh
%xdefine _SSL_CTX_set_tmp_rsa _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_rsa
%xdefine _SSL_CTX_set_tmp_rsa_callback _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_rsa_callback
%xdefine _SSL_CTX_set_trust _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_trust
%xdefine _SSL_CTX_set_verify _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_verify
%xdefine _SSL_CTX_set_verify_algorithm_prefs _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_verify_algorithm_prefs
%xdefine _SSL_CTX_set_verify_depth _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_set_verify_depth
%xdefine _SSL_CTX_up_ref _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_up_ref
%xdefine _SSL_CTX_use_PrivateKey _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_PrivateKey
%xdefine _SSL_CTX_use_PrivateKey_ASN1 _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_PrivateKey_ASN1
%xdefine _SSL_CTX_use_PrivateKey_file _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_PrivateKey_file
%xdefine _SSL_CTX_use_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_RSAPrivateKey
%xdefine _SSL_CTX_use_RSAPrivateKey_ASN1 _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_RSAPrivateKey_ASN1
%xdefine _SSL_CTX_use_RSAPrivateKey_file _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_RSAPrivateKey_file
%xdefine _SSL_CTX_use_certificate _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate
%xdefine _SSL_CTX_use_certificate_ASN1 _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate_ASN1
%xdefine _SSL_CTX_use_certificate_chain_file _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate_chain_file
%xdefine _SSL_CTX_use_certificate_file _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate_file
%xdefine _SSL_CTX_use_psk_identity_hint _ %+ XCRYPTO_PREFIX %+ _SSL_CTX_use_psk_identity_hint
%xdefine _SSL_SESSION_copy_without_early_data _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_copy_without_early_data
%xdefine _SSL_SESSION_early_data_capable _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_early_data_capable
%xdefine _SSL_SESSION_free _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_free
%xdefine _SSL_SESSION_from_bytes _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_from_bytes
%xdefine _SSL_SESSION_get0_cipher _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_cipher
%xdefine _SSL_SESSION_get0_id_context _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_id_context
%xdefine _SSL_SESSION_get0_ocsp_response _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_ocsp_response
%xdefine _SSL_SESSION_get0_peer _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_peer
%xdefine _SSL_SESSION_get0_peer_certificates _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_peer_certificates
%xdefine _SSL_SESSION_get0_peer_sha256 _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_peer_sha256
%xdefine _SSL_SESSION_get0_signed_cert_timestamp_list _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_signed_cert_timestamp_list
%xdefine _SSL_SESSION_get0_ticket _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get0_ticket
%xdefine _SSL_SESSION_get_ex_data _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_ex_data
%xdefine _SSL_SESSION_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_ex_new_index
%xdefine _SSL_SESSION_get_id _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_id
%xdefine _SSL_SESSION_get_master_key _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_master_key
%xdefine _SSL_SESSION_get_protocol_version _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_protocol_version
%xdefine _SSL_SESSION_get_ticket_lifetime_hint _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_ticket_lifetime_hint
%xdefine _SSL_SESSION_get_time _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_time
%xdefine _SSL_SESSION_get_timeout _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_timeout
%xdefine _SSL_SESSION_get_version _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_get_version
%xdefine _SSL_SESSION_has_peer_sha256 _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_has_peer_sha256
%xdefine _SSL_SESSION_has_ticket _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_has_ticket
%xdefine _SSL_SESSION_is_resumable _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_is_resumable
%xdefine _SSL_SESSION_new _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_new
%xdefine _SSL_SESSION_set1_id _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set1_id
%xdefine _SSL_SESSION_set1_id_context _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set1_id_context
%xdefine _SSL_SESSION_set_ex_data _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set_ex_data
%xdefine _SSL_SESSION_set_protocol_version _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set_protocol_version
%xdefine _SSL_SESSION_set_ticket _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set_ticket
%xdefine _SSL_SESSION_set_time _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set_time
%xdefine _SSL_SESSION_set_timeout _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_set_timeout
%xdefine _SSL_SESSION_should_be_single_use _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_should_be_single_use
%xdefine _SSL_SESSION_to_bytes _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_to_bytes
%xdefine _SSL_SESSION_to_bytes_for_ticket _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_to_bytes_for_ticket
%xdefine _SSL_SESSION_up_ref _ %+ XCRYPTO_PREFIX %+ _SSL_SESSION_up_ref
%xdefine _SSL_accept _ %+ XCRYPTO_PREFIX %+ _SSL_accept
%xdefine _SSL_add0_chain_cert _ %+ XCRYPTO_PREFIX %+ _SSL_add0_chain_cert
%xdefine _SSL_add1_chain_cert _ %+ XCRYPTO_PREFIX %+ _SSL_add1_chain_cert
%xdefine _SSL_add_client_CA _ %+ XCRYPTO_PREFIX %+ _SSL_add_client_CA
%xdefine _SSL_add_file_cert_subjects_to_stack _ %+ XCRYPTO_PREFIX %+ _SSL_add_file_cert_subjects_to_stack
%xdefine _SSL_alert_desc_string _ %+ XCRYPTO_PREFIX %+ _SSL_alert_desc_string
%xdefine _SSL_alert_desc_string_long _ %+ XCRYPTO_PREFIX %+ _SSL_alert_desc_string_long
%xdefine _SSL_alert_from_verify_result _ %+ XCRYPTO_PREFIX %+ _SSL_alert_from_verify_result
%xdefine _SSL_alert_type_string _ %+ XCRYPTO_PREFIX %+ _SSL_alert_type_string
%xdefine _SSL_alert_type_string_long _ %+ XCRYPTO_PREFIX %+ _SSL_alert_type_string_long
%xdefine _SSL_cache_hit _ %+ XCRYPTO_PREFIX %+ _SSL_cache_hit
%xdefine _SSL_certs_clear _ %+ XCRYPTO_PREFIX %+ _SSL_certs_clear
%xdefine _SSL_check_private_key _ %+ XCRYPTO_PREFIX %+ _SSL_check_private_key
%xdefine _SSL_clear _ %+ XCRYPTO_PREFIX %+ _SSL_clear
%xdefine _SSL_clear_chain_certs _ %+ XCRYPTO_PREFIX %+ _SSL_clear_chain_certs
%xdefine _SSL_clear_mode _ %+ XCRYPTO_PREFIX %+ _SSL_clear_mode
%xdefine _SSL_clear_options _ %+ XCRYPTO_PREFIX %+ _SSL_clear_options
%xdefine _SSL_connect _ %+ XCRYPTO_PREFIX %+ _SSL_connect
%xdefine _SSL_cutthrough_complete _ %+ XCRYPTO_PREFIX %+ _SSL_cutthrough_complete
%xdefine _SSL_delegated_credential_used _ %+ XCRYPTO_PREFIX %+ _SSL_delegated_credential_used
%xdefine _SSL_do_handshake _ %+ XCRYPTO_PREFIX %+ _SSL_do_handshake
%xdefine _SSL_dup_CA_list _ %+ XCRYPTO_PREFIX %+ _SSL_dup_CA_list
%xdefine _SSL_early_callback_ctx_extension_get _ %+ XCRYPTO_PREFIX %+ _SSL_early_callback_ctx_extension_get
%xdefine _SSL_early_data_accepted _ %+ XCRYPTO_PREFIX %+ _SSL_early_data_accepted
%xdefine _SSL_enable_ocsp_stapling _ %+ XCRYPTO_PREFIX %+ _SSL_enable_ocsp_stapling
%xdefine _SSL_enable_signed_cert_timestamps _ %+ XCRYPTO_PREFIX %+ _SSL_enable_signed_cert_timestamps
%xdefine _SSL_enable_tls_channel_id _ %+ XCRYPTO_PREFIX %+ _SSL_enable_tls_channel_id
%xdefine _SSL_error_description _ %+ XCRYPTO_PREFIX %+ _SSL_error_description
%xdefine _SSL_export_keying_material _ %+ XCRYPTO_PREFIX %+ _SSL_export_keying_material
%xdefine _SSL_free _ %+ XCRYPTO_PREFIX %+ _SSL_free
%xdefine _SSL_generate_key_block _ %+ XCRYPTO_PREFIX %+ _SSL_generate_key_block
%xdefine _SSL_get0_alpn_selected _ %+ XCRYPTO_PREFIX %+ _SSL_get0_alpn_selected
%xdefine _SSL_get0_certificate_types _ %+ XCRYPTO_PREFIX %+ _SSL_get0_certificate_types
%xdefine _SSL_get0_chain_certs _ %+ XCRYPTO_PREFIX %+ _SSL_get0_chain_certs
%xdefine _SSL_get0_next_proto_negotiated _ %+ XCRYPTO_PREFIX %+ _SSL_get0_next_proto_negotiated
%xdefine _SSL_get0_ocsp_response _ %+ XCRYPTO_PREFIX %+ _SSL_get0_ocsp_response
%xdefine _SSL_get0_param _ %+ XCRYPTO_PREFIX %+ _SSL_get0_param
%xdefine _SSL_get0_peer_certificates _ %+ XCRYPTO_PREFIX %+ _SSL_get0_peer_certificates
%xdefine _SSL_get0_peer_verify_algorithms _ %+ XCRYPTO_PREFIX %+ _SSL_get0_peer_verify_algorithms
%xdefine _SSL_get0_server_requested_CAs _ %+ XCRYPTO_PREFIX %+ _SSL_get0_server_requested_CAs
%xdefine _SSL_get0_session_id_context _ %+ XCRYPTO_PREFIX %+ _SSL_get0_session_id_context
%xdefine _SSL_get0_signed_cert_timestamp_list _ %+ XCRYPTO_PREFIX %+ _SSL_get0_signed_cert_timestamp_list
%xdefine _SSL_get1_session _ %+ XCRYPTO_PREFIX %+ _SSL_get1_session
%xdefine _SSL_get_SSL_CTX _ %+ XCRYPTO_PREFIX %+ _SSL_get_SSL_CTX
%xdefine _SSL_get_certificate _ %+ XCRYPTO_PREFIX %+ _SSL_get_certificate
%xdefine _SSL_get_cipher_by_value _ %+ XCRYPTO_PREFIX %+ _SSL_get_cipher_by_value
%xdefine _SSL_get_cipher_list _ %+ XCRYPTO_PREFIX %+ _SSL_get_cipher_list
%xdefine _SSL_get_ciphers _ %+ XCRYPTO_PREFIX %+ _SSL_get_ciphers
%xdefine _SSL_get_client_CA_list _ %+ XCRYPTO_PREFIX %+ _SSL_get_client_CA_list
%xdefine _SSL_get_client_random _ %+ XCRYPTO_PREFIX %+ _SSL_get_client_random
%xdefine _SSL_get_current_cipher _ %+ XCRYPTO_PREFIX %+ _SSL_get_current_cipher
%xdefine _SSL_get_current_compression _ %+ XCRYPTO_PREFIX %+ _SSL_get_current_compression
%xdefine _SSL_get_current_expansion _ %+ XCRYPTO_PREFIX %+ _SSL_get_current_expansion
%xdefine _SSL_get_curve_id _ %+ XCRYPTO_PREFIX %+ _SSL_get_curve_id
%xdefine _SSL_get_curve_name _ %+ XCRYPTO_PREFIX %+ _SSL_get_curve_name
%xdefine _SSL_get_default_timeout _ %+ XCRYPTO_PREFIX %+ _SSL_get_default_timeout
%xdefine _SSL_get_early_data_reason _ %+ XCRYPTO_PREFIX %+ _SSL_get_early_data_reason
%xdefine _SSL_get_error _ %+ XCRYPTO_PREFIX %+ _SSL_get_error
%xdefine _SSL_get_ex_data _ %+ XCRYPTO_PREFIX %+ _SSL_get_ex_data
%xdefine _SSL_get_ex_data_X509_STORE_CTX_idx _ %+ XCRYPTO_PREFIX %+ _SSL_get_ex_data_X509_STORE_CTX_idx
%xdefine _SSL_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _SSL_get_ex_new_index
%xdefine _SSL_get_extms_support _ %+ XCRYPTO_PREFIX %+ _SSL_get_extms_support
%xdefine _SSL_get_fd _ %+ XCRYPTO_PREFIX %+ _SSL_get_fd
%xdefine _SSL_get_finished _ %+ XCRYPTO_PREFIX %+ _SSL_get_finished
%xdefine _SSL_get_info_callback _ %+ XCRYPTO_PREFIX %+ _SSL_get_info_callback
%xdefine _SSL_get_ivs _ %+ XCRYPTO_PREFIX %+ _SSL_get_ivs
%xdefine _SSL_get_key_block_len _ %+ XCRYPTO_PREFIX %+ _SSL_get_key_block_len
%xdefine _SSL_get_max_cert_list _ %+ XCRYPTO_PREFIX %+ _SSL_get_max_cert_list
%xdefine _SSL_get_max_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_get_max_proto_version
%xdefine _SSL_get_min_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_get_min_proto_version
%xdefine _SSL_get_mode _ %+ XCRYPTO_PREFIX %+ _SSL_get_mode
%xdefine _SSL_get_negotiated_token_binding_param _ %+ XCRYPTO_PREFIX %+ _SSL_get_negotiated_token_binding_param
%xdefine _SSL_get_options _ %+ XCRYPTO_PREFIX %+ _SSL_get_options
%xdefine _SSL_get_peer_cert_chain _ %+ XCRYPTO_PREFIX %+ _SSL_get_peer_cert_chain
%xdefine _SSL_get_peer_certificate _ %+ XCRYPTO_PREFIX %+ _SSL_get_peer_certificate
%xdefine _SSL_get_peer_finished _ %+ XCRYPTO_PREFIX %+ _SSL_get_peer_finished
%xdefine _SSL_get_peer_full_cert_chain _ %+ XCRYPTO_PREFIX %+ _SSL_get_peer_full_cert_chain
%xdefine _SSL_get_peer_quic_transport_params _ %+ XCRYPTO_PREFIX %+ _SSL_get_peer_quic_transport_params
%xdefine _SSL_get_peer_signature_algorithm _ %+ XCRYPTO_PREFIX %+ _SSL_get_peer_signature_algorithm
%xdefine _SSL_get_pending_cipher _ %+ XCRYPTO_PREFIX %+ _SSL_get_pending_cipher
%xdefine _SSL_get_privatekey _ %+ XCRYPTO_PREFIX %+ _SSL_get_privatekey
%xdefine _SSL_get_psk_identity _ %+ XCRYPTO_PREFIX %+ _SSL_get_psk_identity
%xdefine _SSL_get_psk_identity_hint _ %+ XCRYPTO_PREFIX %+ _SSL_get_psk_identity_hint
%xdefine _SSL_get_quiet_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_get_quiet_shutdown
%xdefine _SSL_get_rbio _ %+ XCRYPTO_PREFIX %+ _SSL_get_rbio
%xdefine _SSL_get_read_ahead _ %+ XCRYPTO_PREFIX %+ _SSL_get_read_ahead
%xdefine _SSL_get_read_sequence _ %+ XCRYPTO_PREFIX %+ _SSL_get_read_sequence
%xdefine _SSL_get_rfd _ %+ XCRYPTO_PREFIX %+ _SSL_get_rfd
%xdefine _SSL_get_secure_renegotiation_support _ %+ XCRYPTO_PREFIX %+ _SSL_get_secure_renegotiation_support
%xdefine _SSL_get_selected_srtp_profile _ %+ XCRYPTO_PREFIX %+ _SSL_get_selected_srtp_profile
%xdefine _SSL_get_server_random _ %+ XCRYPTO_PREFIX %+ _SSL_get_server_random
%xdefine _SSL_get_server_tmp_key _ %+ XCRYPTO_PREFIX %+ _SSL_get_server_tmp_key
%xdefine _SSL_get_servername _ %+ XCRYPTO_PREFIX %+ _SSL_get_servername
%xdefine _SSL_get_servername_type _ %+ XCRYPTO_PREFIX %+ _SSL_get_servername_type
%xdefine _SSL_get_session _ %+ XCRYPTO_PREFIX %+ _SSL_get_session
%xdefine _SSL_get_shared_ciphers _ %+ XCRYPTO_PREFIX %+ _SSL_get_shared_ciphers
%xdefine _SSL_get_shared_sigalgs _ %+ XCRYPTO_PREFIX %+ _SSL_get_shared_sigalgs
%xdefine _SSL_get_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_get_shutdown
%xdefine _SSL_get_signature_algorithm_digest _ %+ XCRYPTO_PREFIX %+ _SSL_get_signature_algorithm_digest
%xdefine _SSL_get_signature_algorithm_key_type _ %+ XCRYPTO_PREFIX %+ _SSL_get_signature_algorithm_key_type
%xdefine _SSL_get_signature_algorithm_name _ %+ XCRYPTO_PREFIX %+ _SSL_get_signature_algorithm_name
%xdefine _SSL_get_srtp_profiles _ %+ XCRYPTO_PREFIX %+ _SSL_get_srtp_profiles
%xdefine _SSL_get_ticket_age_skew _ %+ XCRYPTO_PREFIX %+ _SSL_get_ticket_age_skew
%xdefine _SSL_get_tls_channel_id _ %+ XCRYPTO_PREFIX %+ _SSL_get_tls_channel_id
%xdefine _SSL_get_tls_unique _ %+ XCRYPTO_PREFIX %+ _SSL_get_tls_unique
%xdefine _SSL_get_tlsext_status_ocsp_resp _ %+ XCRYPTO_PREFIX %+ _SSL_get_tlsext_status_ocsp_resp
%xdefine _SSL_get_tlsext_status_type _ %+ XCRYPTO_PREFIX %+ _SSL_get_tlsext_status_type
%xdefine _SSL_get_verify_callback _ %+ XCRYPTO_PREFIX %+ _SSL_get_verify_callback
%xdefine _SSL_get_verify_depth _ %+ XCRYPTO_PREFIX %+ _SSL_get_verify_depth
%xdefine _SSL_get_verify_mode _ %+ XCRYPTO_PREFIX %+ _SSL_get_verify_mode
%xdefine _SSL_get_verify_result _ %+ XCRYPTO_PREFIX %+ _SSL_get_verify_result
%xdefine _SSL_get_version _ %+ XCRYPTO_PREFIX %+ _SSL_get_version
%xdefine _SSL_get_wbio _ %+ XCRYPTO_PREFIX %+ _SSL_get_wbio
%xdefine _SSL_get_wfd _ %+ XCRYPTO_PREFIX %+ _SSL_get_wfd
%xdefine _SSL_get_write_sequence _ %+ XCRYPTO_PREFIX %+ _SSL_get_write_sequence
%xdefine _SSL_in_early_data _ %+ XCRYPTO_PREFIX %+ _SSL_in_early_data
%xdefine _SSL_in_false_start _ %+ XCRYPTO_PREFIX %+ _SSL_in_false_start
%xdefine _SSL_in_init _ %+ XCRYPTO_PREFIX %+ _SSL_in_init
%xdefine _SSL_is_dtls _ %+ XCRYPTO_PREFIX %+ _SSL_is_dtls
%xdefine _SSL_is_init_finished _ %+ XCRYPTO_PREFIX %+ _SSL_is_init_finished
%xdefine _SSL_is_server _ %+ XCRYPTO_PREFIX %+ _SSL_is_server
%xdefine _SSL_is_signature_algorithm_rsa_pss _ %+ XCRYPTO_PREFIX %+ _SSL_is_signature_algorithm_rsa_pss
%xdefine _SSL_is_tls13_downgrade _ %+ XCRYPTO_PREFIX %+ _SSL_is_tls13_downgrade
%xdefine _SSL_is_token_binding_negotiated _ %+ XCRYPTO_PREFIX %+ _SSL_is_token_binding_negotiated
%xdefine _SSL_key_update _ %+ XCRYPTO_PREFIX %+ _SSL_key_update
%xdefine _SSL_library_init _ %+ XCRYPTO_PREFIX %+ _SSL_library_init
%xdefine _SSL_load_client_CA_file _ %+ XCRYPTO_PREFIX %+ _SSL_load_client_CA_file
%xdefine _SSL_load_error_strings _ %+ XCRYPTO_PREFIX %+ _SSL_load_error_strings
%xdefine _SSL_magic_pending_session_ptr _ %+ XCRYPTO_PREFIX %+ _SSL_magic_pending_session_ptr
%xdefine _SSL_max_seal_overhead _ %+ XCRYPTO_PREFIX %+ _SSL_max_seal_overhead
%xdefine _SSL_need_tmp_RSA _ %+ XCRYPTO_PREFIX %+ _SSL_need_tmp_RSA
%xdefine _SSL_new _ %+ XCRYPTO_PREFIX %+ _SSL_new
%xdefine _SSL_num_renegotiations _ %+ XCRYPTO_PREFIX %+ _SSL_num_renegotiations
%xdefine _SSL_peek _ %+ XCRYPTO_PREFIX %+ _SSL_peek
%xdefine _SSL_pending _ %+ XCRYPTO_PREFIX %+ _SSL_pending
%xdefine _SSL_process_quic_post_handshake _ %+ XCRYPTO_PREFIX %+ _SSL_process_quic_post_handshake
%xdefine _SSL_provide_quic_data _ %+ XCRYPTO_PREFIX %+ _SSL_provide_quic_data
%xdefine _SSL_quic_max_handshake_flight_len _ %+ XCRYPTO_PREFIX %+ _SSL_quic_max_handshake_flight_len
%xdefine _SSL_quic_read_level _ %+ XCRYPTO_PREFIX %+ _SSL_quic_read_level
%xdefine _SSL_quic_write_level _ %+ XCRYPTO_PREFIX %+ _SSL_quic_write_level
%xdefine _SSL_read _ %+ XCRYPTO_PREFIX %+ _SSL_read
%xdefine _SSL_renegotiate _ %+ XCRYPTO_PREFIX %+ _SSL_renegotiate
%xdefine _SSL_renegotiate_pending _ %+ XCRYPTO_PREFIX %+ _SSL_renegotiate_pending
%xdefine _SSL_reset_early_data_reject _ %+ XCRYPTO_PREFIX %+ _SSL_reset_early_data_reject
%xdefine _SSL_select_next_proto _ %+ XCRYPTO_PREFIX %+ _SSL_select_next_proto
%xdefine _SSL_send_fatal_alert _ %+ XCRYPTO_PREFIX %+ _SSL_send_fatal_alert
%xdefine _SSL_session_reused _ %+ XCRYPTO_PREFIX %+ _SSL_session_reused
%xdefine _SSL_set0_chain _ %+ XCRYPTO_PREFIX %+ _SSL_set0_chain
%xdefine _SSL_set0_client_CAs _ %+ XCRYPTO_PREFIX %+ _SSL_set0_client_CAs
%xdefine _SSL_set0_rbio _ %+ XCRYPTO_PREFIX %+ _SSL_set0_rbio
%xdefine _SSL_set0_verify_cert_store _ %+ XCRYPTO_PREFIX %+ _SSL_set0_verify_cert_store
%xdefine _SSL_set0_wbio _ %+ XCRYPTO_PREFIX %+ _SSL_set0_wbio
%xdefine _SSL_set1_chain _ %+ XCRYPTO_PREFIX %+ _SSL_set1_chain
%xdefine _SSL_set1_curves _ %+ XCRYPTO_PREFIX %+ _SSL_set1_curves
%xdefine _SSL_set1_curves_list _ %+ XCRYPTO_PREFIX %+ _SSL_set1_curves_list
%xdefine _SSL_set1_delegated_credential _ %+ XCRYPTO_PREFIX %+ _SSL_set1_delegated_credential
%xdefine _SSL_set1_param _ %+ XCRYPTO_PREFIX %+ _SSL_set1_param
%xdefine _SSL_set1_sigalgs _ %+ XCRYPTO_PREFIX %+ _SSL_set1_sigalgs
%xdefine _SSL_set1_sigalgs_list _ %+ XCRYPTO_PREFIX %+ _SSL_set1_sigalgs_list
%xdefine _SSL_set1_tls_channel_id _ %+ XCRYPTO_PREFIX %+ _SSL_set1_tls_channel_id
%xdefine _SSL_set1_verify_cert_store _ %+ XCRYPTO_PREFIX %+ _SSL_set1_verify_cert_store
%xdefine _SSL_set_SSL_CTX _ %+ XCRYPTO_PREFIX %+ _SSL_set_SSL_CTX
%xdefine _SSL_set_accept_state _ %+ XCRYPTO_PREFIX %+ _SSL_set_accept_state
%xdefine _SSL_set_alpn_protos _ %+ XCRYPTO_PREFIX %+ _SSL_set_alpn_protos
%xdefine _SSL_set_bio _ %+ XCRYPTO_PREFIX %+ _SSL_set_bio
%xdefine _SSL_set_cert_cb _ %+ XCRYPTO_PREFIX %+ _SSL_set_cert_cb
%xdefine _SSL_set_chain_and_key _ %+ XCRYPTO_PREFIX %+ _SSL_set_chain_and_key
%xdefine _SSL_set_cipher_list _ %+ XCRYPTO_PREFIX %+ _SSL_set_cipher_list
%xdefine _SSL_set_client_CA_list _ %+ XCRYPTO_PREFIX %+ _SSL_set_client_CA_list
%xdefine _SSL_set_connect_state _ %+ XCRYPTO_PREFIX %+ _SSL_set_connect_state
%xdefine _SSL_set_custom_verify _ %+ XCRYPTO_PREFIX %+ _SSL_set_custom_verify
%xdefine _SSL_set_early_data_enabled _ %+ XCRYPTO_PREFIX %+ _SSL_set_early_data_enabled
%xdefine _SSL_set_enforce_rsa_key_usage _ %+ XCRYPTO_PREFIX %+ _SSL_set_enforce_rsa_key_usage
%xdefine _SSL_set_ex_data _ %+ XCRYPTO_PREFIX %+ _SSL_set_ex_data
%xdefine _SSL_set_fd _ %+ XCRYPTO_PREFIX %+ _SSL_set_fd
%xdefine _SSL_set_ignore_tls13_downgrade _ %+ XCRYPTO_PREFIX %+ _SSL_set_ignore_tls13_downgrade
%xdefine _SSL_set_info_callback _ %+ XCRYPTO_PREFIX %+ _SSL_set_info_callback
%xdefine _SSL_set_jdk11_workaround _ %+ XCRYPTO_PREFIX %+ _SSL_set_jdk11_workaround
%xdefine _SSL_set_max_cert_list _ %+ XCRYPTO_PREFIX %+ _SSL_set_max_cert_list
%xdefine _SSL_set_max_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_set_max_proto_version
%xdefine _SSL_set_max_send_fragment _ %+ XCRYPTO_PREFIX %+ _SSL_set_max_send_fragment
%xdefine _SSL_set_min_proto_version _ %+ XCRYPTO_PREFIX %+ _SSL_set_min_proto_version
%xdefine _SSL_set_mode _ %+ XCRYPTO_PREFIX %+ _SSL_set_mode
%xdefine _SSL_set_msg_callback _ %+ XCRYPTO_PREFIX %+ _SSL_set_msg_callback
%xdefine _SSL_set_msg_callback_arg _ %+ XCRYPTO_PREFIX %+ _SSL_set_msg_callback_arg
%xdefine _SSL_set_mtu _ %+ XCRYPTO_PREFIX %+ _SSL_set_mtu
%xdefine _SSL_set_ocsp_response _ %+ XCRYPTO_PREFIX %+ _SSL_set_ocsp_response
%xdefine _SSL_set_options _ %+ XCRYPTO_PREFIX %+ _SSL_set_options
%xdefine _SSL_set_private_key_method _ %+ XCRYPTO_PREFIX %+ _SSL_set_private_key_method
%xdefine _SSL_set_psk_client_callback _ %+ XCRYPTO_PREFIX %+ _SSL_set_psk_client_callback
%xdefine _SSL_set_psk_server_callback _ %+ XCRYPTO_PREFIX %+ _SSL_set_psk_server_callback
%xdefine _SSL_set_purpose _ %+ XCRYPTO_PREFIX %+ _SSL_set_purpose
%xdefine _SSL_set_quic_early_data_context _ %+ XCRYPTO_PREFIX %+ _SSL_set_quic_early_data_context
%xdefine _SSL_set_quic_method _ %+ XCRYPTO_PREFIX %+ _SSL_set_quic_method
%xdefine _SSL_set_quic_transport_params _ %+ XCRYPTO_PREFIX %+ _SSL_set_quic_transport_params
%xdefine _SSL_set_quiet_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_set_quiet_shutdown
%xdefine _SSL_set_read_ahead _ %+ XCRYPTO_PREFIX %+ _SSL_set_read_ahead
%xdefine _SSL_set_renegotiate_mode _ %+ XCRYPTO_PREFIX %+ _SSL_set_renegotiate_mode
%xdefine _SSL_set_retain_only_sha256_of_client_certs _ %+ XCRYPTO_PREFIX %+ _SSL_set_retain_only_sha256_of_client_certs
%xdefine _SSL_set_rfd _ %+ XCRYPTO_PREFIX %+ _SSL_set_rfd
%xdefine _SSL_set_session _ %+ XCRYPTO_PREFIX %+ _SSL_set_session
%xdefine _SSL_set_session_id_context _ %+ XCRYPTO_PREFIX %+ _SSL_set_session_id_context
%xdefine _SSL_set_shed_handshake_config _ %+ XCRYPTO_PREFIX %+ _SSL_set_shed_handshake_config
%xdefine _SSL_set_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_set_shutdown
%xdefine _SSL_set_signed_cert_timestamp_list _ %+ XCRYPTO_PREFIX %+ _SSL_set_signed_cert_timestamp_list
%xdefine _SSL_set_signing_algorithm_prefs _ %+ XCRYPTO_PREFIX %+ _SSL_set_signing_algorithm_prefs
%xdefine _SSL_set_srtp_profiles _ %+ XCRYPTO_PREFIX %+ _SSL_set_srtp_profiles
%xdefine _SSL_set_state _ %+ XCRYPTO_PREFIX %+ _SSL_set_state
%xdefine _SSL_set_strict_cipher_list _ %+ XCRYPTO_PREFIX %+ _SSL_set_strict_cipher_list
%xdefine _SSL_set_tls_channel_id_enabled _ %+ XCRYPTO_PREFIX %+ _SSL_set_tls_channel_id_enabled
%xdefine _SSL_set_tlsext_host_name _ %+ XCRYPTO_PREFIX %+ _SSL_set_tlsext_host_name
%xdefine _SSL_set_tlsext_status_ocsp_resp _ %+ XCRYPTO_PREFIX %+ _SSL_set_tlsext_status_ocsp_resp
%xdefine _SSL_set_tlsext_status_type _ %+ XCRYPTO_PREFIX %+ _SSL_set_tlsext_status_type
%xdefine _SSL_set_tlsext_use_srtp _ %+ XCRYPTO_PREFIX %+ _SSL_set_tlsext_use_srtp
%xdefine _SSL_set_tmp_dh _ %+ XCRYPTO_PREFIX %+ _SSL_set_tmp_dh
%xdefine _SSL_set_tmp_dh_callback _ %+ XCRYPTO_PREFIX %+ _SSL_set_tmp_dh_callback
%xdefine _SSL_set_tmp_ecdh _ %+ XCRYPTO_PREFIX %+ _SSL_set_tmp_ecdh
%xdefine _SSL_set_tmp_rsa _ %+ XCRYPTO_PREFIX %+ _SSL_set_tmp_rsa
%xdefine _SSL_set_tmp_rsa_callback _ %+ XCRYPTO_PREFIX %+ _SSL_set_tmp_rsa_callback
%xdefine _SSL_set_token_binding_params _ %+ XCRYPTO_PREFIX %+ _SSL_set_token_binding_params
%xdefine _SSL_set_trust _ %+ XCRYPTO_PREFIX %+ _SSL_set_trust
%xdefine _SSL_set_verify _ %+ XCRYPTO_PREFIX %+ _SSL_set_verify
%xdefine _SSL_set_verify_algorithm_prefs _ %+ XCRYPTO_PREFIX %+ _SSL_set_verify_algorithm_prefs
%xdefine _SSL_set_verify_depth _ %+ XCRYPTO_PREFIX %+ _SSL_set_verify_depth
%xdefine _SSL_set_verify_result _ %+ XCRYPTO_PREFIX %+ _SSL_set_verify_result
%xdefine _SSL_set_wfd _ %+ XCRYPTO_PREFIX %+ _SSL_set_wfd
%xdefine _SSL_shutdown _ %+ XCRYPTO_PREFIX %+ _SSL_shutdown
%xdefine _SSL_state _ %+ XCRYPTO_PREFIX %+ _SSL_state
%xdefine _SSL_state_string _ %+ XCRYPTO_PREFIX %+ _SSL_state_string
%xdefine _SSL_state_string_long _ %+ XCRYPTO_PREFIX %+ _SSL_state_string_long
%xdefine _SSL_total_renegotiations _ %+ XCRYPTO_PREFIX %+ _SSL_total_renegotiations
%xdefine _SSL_use_PrivateKey _ %+ XCRYPTO_PREFIX %+ _SSL_use_PrivateKey
%xdefine _SSL_use_PrivateKey_ASN1 _ %+ XCRYPTO_PREFIX %+ _SSL_use_PrivateKey_ASN1
%xdefine _SSL_use_PrivateKey_file _ %+ XCRYPTO_PREFIX %+ _SSL_use_PrivateKey_file
%xdefine _SSL_use_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _SSL_use_RSAPrivateKey
%xdefine _SSL_use_RSAPrivateKey_ASN1 _ %+ XCRYPTO_PREFIX %+ _SSL_use_RSAPrivateKey_ASN1
%xdefine _SSL_use_RSAPrivateKey_file _ %+ XCRYPTO_PREFIX %+ _SSL_use_RSAPrivateKey_file
%xdefine _SSL_use_certificate _ %+ XCRYPTO_PREFIX %+ _SSL_use_certificate
%xdefine _SSL_use_certificate_ASN1 _ %+ XCRYPTO_PREFIX %+ _SSL_use_certificate_ASN1
%xdefine _SSL_use_certificate_file _ %+ XCRYPTO_PREFIX %+ _SSL_use_certificate_file
%xdefine _SSL_use_psk_identity_hint _ %+ XCRYPTO_PREFIX %+ _SSL_use_psk_identity_hint
%xdefine _SSL_used_hello_retry_request _ %+ XCRYPTO_PREFIX %+ _SSL_used_hello_retry_request
%xdefine _SSL_version _ %+ XCRYPTO_PREFIX %+ _SSL_version
%xdefine _SSL_want _ %+ XCRYPTO_PREFIX %+ _SSL_want
%xdefine _SSL_write _ %+ XCRYPTO_PREFIX %+ _SSL_write
%xdefine _SSLeay _ %+ XCRYPTO_PREFIX %+ _SSLeay
%xdefine _SSLeay_version _ %+ XCRYPTO_PREFIX %+ _SSLeay_version
%xdefine _SSLv23_client_method _ %+ XCRYPTO_PREFIX %+ _SSLv23_client_method
%xdefine _SSLv23_method _ %+ XCRYPTO_PREFIX %+ _SSLv23_method
%xdefine _SSLv23_server_method _ %+ XCRYPTO_PREFIX %+ _SSLv23_server_method
%xdefine _SXNETID_free _ %+ XCRYPTO_PREFIX %+ _SXNETID_free
%xdefine _SXNETID_it _ %+ XCRYPTO_PREFIX %+ _SXNETID_it
%xdefine _SXNETID_new _ %+ XCRYPTO_PREFIX %+ _SXNETID_new
%xdefine _SXNET_add_id_INTEGER _ %+ XCRYPTO_PREFIX %+ _SXNET_add_id_INTEGER
%xdefine _SXNET_add_id_asc _ %+ XCRYPTO_PREFIX %+ _SXNET_add_id_asc
%xdefine _SXNET_add_id_ulong _ %+ XCRYPTO_PREFIX %+ _SXNET_add_id_ulong
%xdefine _SXNET_free _ %+ XCRYPTO_PREFIX %+ _SXNET_free
%xdefine _SXNET_get_id_INTEGER _ %+ XCRYPTO_PREFIX %+ _SXNET_get_id_INTEGER
%xdefine _SXNET_get_id_asc _ %+ XCRYPTO_PREFIX %+ _SXNET_get_id_asc
%xdefine _SXNET_get_id_ulong _ %+ XCRYPTO_PREFIX %+ _SXNET_get_id_ulong
%xdefine _SXNET_it _ %+ XCRYPTO_PREFIX %+ _SXNET_it
%xdefine _SXNET_new _ %+ XCRYPTO_PREFIX %+ _SXNET_new
%xdefine _TLS_client_method _ %+ XCRYPTO_PREFIX %+ _TLS_client_method
%xdefine _TLS_method _ %+ XCRYPTO_PREFIX %+ _TLS_method
%xdefine _TLS_server_method _ %+ XCRYPTO_PREFIX %+ _TLS_server_method
%xdefine _TLS_with_buffers_method _ %+ XCRYPTO_PREFIX %+ _TLS_with_buffers_method
%xdefine _TLSv1_1_client_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_1_client_method
%xdefine _TLSv1_1_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_1_method
%xdefine _TLSv1_1_server_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_1_server_method
%xdefine _TLSv1_2_client_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_2_client_method
%xdefine _TLSv1_2_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_2_method
%xdefine _TLSv1_2_server_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_2_server_method
%xdefine _TLSv1_client_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_client_method
%xdefine _TLSv1_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_method
%xdefine _TLSv1_server_method _ %+ XCRYPTO_PREFIX %+ _TLSv1_server_method
%xdefine _TRUST_TOKEN_CLIENT_add_key _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_add_key
%xdefine _TRUST_TOKEN_CLIENT_begin_issuance _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_begin_issuance
%xdefine _TRUST_TOKEN_CLIENT_begin_redemption _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_begin_redemption
%xdefine _TRUST_TOKEN_CLIENT_finish_issuance _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_finish_issuance
%xdefine _TRUST_TOKEN_CLIENT_finish_redemption _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_finish_redemption
%xdefine _TRUST_TOKEN_CLIENT_free _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_free
%xdefine _TRUST_TOKEN_CLIENT_new _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_new
%xdefine _TRUST_TOKEN_CLIENT_set_srr_key _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_set_srr_key
%xdefine _TRUST_TOKEN_ISSUER_add_key _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_add_key
%xdefine _TRUST_TOKEN_ISSUER_free _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_free
%xdefine _TRUST_TOKEN_ISSUER_issue _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_issue
%xdefine _TRUST_TOKEN_ISSUER_new _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_new
%xdefine _TRUST_TOKEN_ISSUER_redeem _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_redeem
%xdefine _TRUST_TOKEN_ISSUER_set_metadata_key _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_set_metadata_key
%xdefine _TRUST_TOKEN_ISSUER_set_srr_key _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_set_srr_key
%xdefine _TRUST_TOKEN_decode_private_metadata _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_decode_private_metadata
%xdefine _TRUST_TOKEN_experiment_v0 _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_experiment_v0
%xdefine _TRUST_TOKEN_experiment_v1 _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_experiment_v1
%xdefine _TRUST_TOKEN_free _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_free
%xdefine _TRUST_TOKEN_generate_key _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_generate_key
%xdefine _TRUST_TOKEN_new _ %+ XCRYPTO_PREFIX %+ _TRUST_TOKEN_new
%xdefine _USERNOTICE_free _ %+ XCRYPTO_PREFIX %+ _USERNOTICE_free
%xdefine _USERNOTICE_it _ %+ XCRYPTO_PREFIX %+ _USERNOTICE_it
%xdefine _USERNOTICE_new _ %+ XCRYPTO_PREFIX %+ _USERNOTICE_new
%xdefine _UTF8_getc _ %+ XCRYPTO_PREFIX %+ _UTF8_getc
%xdefine _UTF8_putc _ %+ XCRYPTO_PREFIX %+ _UTF8_putc
%xdefine _X25519 _ %+ XCRYPTO_PREFIX %+ _X25519
%xdefine _X25519_keypair _ %+ XCRYPTO_PREFIX %+ _X25519_keypair
%xdefine _X25519_public_from_private _ %+ XCRYPTO_PREFIX %+ _X25519_public_from_private
%xdefine _X509V3_EXT_CRL_add_nconf _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_CRL_add_nconf
%xdefine _X509V3_EXT_REQ_add_nconf _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_REQ_add_nconf
%xdefine _X509V3_EXT_add _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_add
%xdefine _X509V3_EXT_add_alias _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_add_alias
%xdefine _X509V3_EXT_add_list _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_add_list
%xdefine _X509V3_EXT_add_nconf _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_add_nconf
%xdefine _X509V3_EXT_add_nconf_sk _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_add_nconf_sk
%xdefine _X509V3_EXT_cleanup _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_cleanup
%xdefine _X509V3_EXT_d2i _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_d2i
%xdefine _X509V3_EXT_free _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_free
%xdefine _X509V3_EXT_get _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_get
%xdefine _X509V3_EXT_get_nid _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_get_nid
%xdefine _X509V3_EXT_i2d _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_i2d
%xdefine _X509V3_EXT_nconf _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_nconf
%xdefine _X509V3_EXT_nconf_nid _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_nconf_nid
%xdefine _X509V3_EXT_print _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_print
%xdefine _X509V3_EXT_print_fp _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_print_fp
%xdefine _X509V3_EXT_val_prn _ %+ XCRYPTO_PREFIX %+ _X509V3_EXT_val_prn
%xdefine _X509V3_NAME_from_section _ %+ XCRYPTO_PREFIX %+ _X509V3_NAME_from_section
%xdefine _X509V3_add1_i2d _ %+ XCRYPTO_PREFIX %+ _X509V3_add1_i2d
%xdefine _X509V3_add_standard_extensions _ %+ XCRYPTO_PREFIX %+ _X509V3_add_standard_extensions
%xdefine _X509V3_add_value _ %+ XCRYPTO_PREFIX %+ _X509V3_add_value
%xdefine _X509V3_add_value_bool _ %+ XCRYPTO_PREFIX %+ _X509V3_add_value_bool
%xdefine _X509V3_add_value_bool_nf _ %+ XCRYPTO_PREFIX %+ _X509V3_add_value_bool_nf
%xdefine _X509V3_add_value_int _ %+ XCRYPTO_PREFIX %+ _X509V3_add_value_int
%xdefine _X509V3_add_value_uchar _ %+ XCRYPTO_PREFIX %+ _X509V3_add_value_uchar
%xdefine _X509V3_conf_free _ %+ XCRYPTO_PREFIX %+ _X509V3_conf_free
%xdefine _X509V3_extensions_print _ %+ XCRYPTO_PREFIX %+ _X509V3_extensions_print
%xdefine _X509V3_get_d2i _ %+ XCRYPTO_PREFIX %+ _X509V3_get_d2i
%xdefine _X509V3_get_section _ %+ XCRYPTO_PREFIX %+ _X509V3_get_section
%xdefine _X509V3_get_string _ %+ XCRYPTO_PREFIX %+ _X509V3_get_string
%xdefine _X509V3_get_value_bool _ %+ XCRYPTO_PREFIX %+ _X509V3_get_value_bool
%xdefine _X509V3_get_value_int _ %+ XCRYPTO_PREFIX %+ _X509V3_get_value_int
%xdefine _X509V3_parse_list _ %+ XCRYPTO_PREFIX %+ _X509V3_parse_list
%xdefine _X509V3_section_free _ %+ XCRYPTO_PREFIX %+ _X509V3_section_free
%xdefine _X509V3_set_ctx _ %+ XCRYPTO_PREFIX %+ _X509V3_set_ctx
%xdefine _X509V3_set_nconf _ %+ XCRYPTO_PREFIX %+ _X509V3_set_nconf
%xdefine _X509V3_string_free _ %+ XCRYPTO_PREFIX %+ _X509V3_string_free
%xdefine _X509_ALGORS_it _ %+ XCRYPTO_PREFIX %+ _X509_ALGORS_it
%xdefine _X509_ALGOR_cmp _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_cmp
%xdefine _X509_ALGOR_dup _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_dup
%xdefine _X509_ALGOR_free _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_free
%xdefine _X509_ALGOR_get0 _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_get0
%xdefine _X509_ALGOR_it _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_it
%xdefine _X509_ALGOR_new _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_new
%xdefine _X509_ALGOR_set0 _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_set0
%xdefine _X509_ALGOR_set_md _ %+ XCRYPTO_PREFIX %+ _X509_ALGOR_set_md
%xdefine _X509_ATTRIBUTE_SET_it _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_SET_it
%xdefine _X509_ATTRIBUTE_count _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_count
%xdefine _X509_ATTRIBUTE_create _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create
%xdefine _X509_ATTRIBUTE_create_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create_by_NID
%xdefine _X509_ATTRIBUTE_create_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create_by_OBJ
%xdefine _X509_ATTRIBUTE_create_by_txt _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create_by_txt
%xdefine _X509_ATTRIBUTE_dup _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_dup
%xdefine _X509_ATTRIBUTE_free _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_free
%xdefine _X509_ATTRIBUTE_get0_data _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_get0_data
%xdefine _X509_ATTRIBUTE_get0_object _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_get0_object
%xdefine _X509_ATTRIBUTE_get0_type _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_get0_type
%xdefine _X509_ATTRIBUTE_it _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_it
%xdefine _X509_ATTRIBUTE_new _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_new
%xdefine _X509_ATTRIBUTE_set1_data _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_set1_data
%xdefine _X509_ATTRIBUTE_set1_object _ %+ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_set1_object
%xdefine _X509_CERT_AUX_free _ %+ XCRYPTO_PREFIX %+ _X509_CERT_AUX_free
%xdefine _X509_CERT_AUX_it _ %+ XCRYPTO_PREFIX %+ _X509_CERT_AUX_it
%xdefine _X509_CERT_AUX_new _ %+ XCRYPTO_PREFIX %+ _X509_CERT_AUX_new
%xdefine _X509_CERT_AUX_print _ %+ XCRYPTO_PREFIX %+ _X509_CERT_AUX_print
%xdefine _X509_CINF_free _ %+ XCRYPTO_PREFIX %+ _X509_CINF_free
%xdefine _X509_CINF_it _ %+ XCRYPTO_PREFIX %+ _X509_CINF_it
%xdefine _X509_CINF_new _ %+ XCRYPTO_PREFIX %+ _X509_CINF_new
%xdefine _X509_CRL_INFO_free _ %+ XCRYPTO_PREFIX %+ _X509_CRL_INFO_free
%xdefine _X509_CRL_INFO_it _ %+ XCRYPTO_PREFIX %+ _X509_CRL_INFO_it
%xdefine _X509_CRL_INFO_new _ %+ XCRYPTO_PREFIX %+ _X509_CRL_INFO_new
%xdefine _X509_CRL_METHOD_free _ %+ XCRYPTO_PREFIX %+ _X509_CRL_METHOD_free
%xdefine _X509_CRL_METHOD_new _ %+ XCRYPTO_PREFIX %+ _X509_CRL_METHOD_new
%xdefine _X509_CRL_add0_revoked _ %+ XCRYPTO_PREFIX %+ _X509_CRL_add0_revoked
%xdefine _X509_CRL_add1_ext_i2d _ %+ XCRYPTO_PREFIX %+ _X509_CRL_add1_ext_i2d
%xdefine _X509_CRL_add_ext _ %+ XCRYPTO_PREFIX %+ _X509_CRL_add_ext
%xdefine _X509_CRL_check_suiteb _ %+ XCRYPTO_PREFIX %+ _X509_CRL_check_suiteb
%xdefine _X509_CRL_cmp _ %+ XCRYPTO_PREFIX %+ _X509_CRL_cmp
%xdefine _X509_CRL_delete_ext _ %+ XCRYPTO_PREFIX %+ _X509_CRL_delete_ext
%xdefine _X509_CRL_diff _ %+ XCRYPTO_PREFIX %+ _X509_CRL_diff
%xdefine _X509_CRL_digest _ %+ XCRYPTO_PREFIX %+ _X509_CRL_digest
%xdefine _X509_CRL_dup _ %+ XCRYPTO_PREFIX %+ _X509_CRL_dup
%xdefine _X509_CRL_free _ %+ XCRYPTO_PREFIX %+ _X509_CRL_free
%xdefine _X509_CRL_get0_by_cert _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get0_by_cert
%xdefine _X509_CRL_get0_by_serial _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get0_by_serial
%xdefine _X509_CRL_get0_lastUpdate _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get0_lastUpdate
%xdefine _X509_CRL_get0_nextUpdate _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get0_nextUpdate
%xdefine _X509_CRL_get0_signature _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get0_signature
%xdefine _X509_CRL_get_ext _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_ext
%xdefine _X509_CRL_get_ext_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_ext_by_NID
%xdefine _X509_CRL_get_ext_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_ext_by_OBJ
%xdefine _X509_CRL_get_ext_by_critical _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_ext_by_critical
%xdefine _X509_CRL_get_ext_count _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_ext_count
%xdefine _X509_CRL_get_ext_d2i _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_ext_d2i
%xdefine _X509_CRL_get_meth_data _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_meth_data
%xdefine _X509_CRL_get_signature_nid _ %+ XCRYPTO_PREFIX %+ _X509_CRL_get_signature_nid
%xdefine _X509_CRL_it _ %+ XCRYPTO_PREFIX %+ _X509_CRL_it
%xdefine _X509_CRL_match _ %+ XCRYPTO_PREFIX %+ _X509_CRL_match
%xdefine _X509_CRL_new _ %+ XCRYPTO_PREFIX %+ _X509_CRL_new
%xdefine _X509_CRL_print _ %+ XCRYPTO_PREFIX %+ _X509_CRL_print
%xdefine _X509_CRL_print_fp _ %+ XCRYPTO_PREFIX %+ _X509_CRL_print_fp
%xdefine _X509_CRL_set_default_method _ %+ XCRYPTO_PREFIX %+ _X509_CRL_set_default_method
%xdefine _X509_CRL_set_issuer_name _ %+ XCRYPTO_PREFIX %+ _X509_CRL_set_issuer_name
%xdefine _X509_CRL_set_lastUpdate _ %+ XCRYPTO_PREFIX %+ _X509_CRL_set_lastUpdate
%xdefine _X509_CRL_set_meth_data _ %+ XCRYPTO_PREFIX %+ _X509_CRL_set_meth_data
%xdefine _X509_CRL_set_nextUpdate _ %+ XCRYPTO_PREFIX %+ _X509_CRL_set_nextUpdate
%xdefine _X509_CRL_set_version _ %+ XCRYPTO_PREFIX %+ _X509_CRL_set_version
%xdefine _X509_CRL_sign _ %+ XCRYPTO_PREFIX %+ _X509_CRL_sign
%xdefine _X509_CRL_sign_ctx _ %+ XCRYPTO_PREFIX %+ _X509_CRL_sign_ctx
%xdefine _X509_CRL_sort _ %+ XCRYPTO_PREFIX %+ _X509_CRL_sort
%xdefine _X509_CRL_up_ref _ %+ XCRYPTO_PREFIX %+ _X509_CRL_up_ref
%xdefine _X509_CRL_verify _ %+ XCRYPTO_PREFIX %+ _X509_CRL_verify
%xdefine _X509_EXTENSIONS_it _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSIONS_it
%xdefine _X509_EXTENSION_create_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_create_by_NID
%xdefine _X509_EXTENSION_create_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_create_by_OBJ
%xdefine _X509_EXTENSION_dup _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_dup
%xdefine _X509_EXTENSION_free _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_free
%xdefine _X509_EXTENSION_get_critical _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_get_critical
%xdefine _X509_EXTENSION_get_data _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_get_data
%xdefine _X509_EXTENSION_get_object _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_get_object
%xdefine _X509_EXTENSION_it _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_it
%xdefine _X509_EXTENSION_new _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_new
%xdefine _X509_EXTENSION_set_critical _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_set_critical
%xdefine _X509_EXTENSION_set_data _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_set_data
%xdefine _X509_EXTENSION_set_object _ %+ XCRYPTO_PREFIX %+ _X509_EXTENSION_set_object
%xdefine _X509_INFO_free _ %+ XCRYPTO_PREFIX %+ _X509_INFO_free
%xdefine _X509_INFO_new _ %+ XCRYPTO_PREFIX %+ _X509_INFO_new
%xdefine _X509_LOOKUP_by_alias _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_by_alias
%xdefine _X509_LOOKUP_by_fingerprint _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_by_fingerprint
%xdefine _X509_LOOKUP_by_issuer_serial _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_by_issuer_serial
%xdefine _X509_LOOKUP_by_subject _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_by_subject
%xdefine _X509_LOOKUP_ctrl _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_ctrl
%xdefine _X509_LOOKUP_file _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_file
%xdefine _X509_LOOKUP_free _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_free
%xdefine _X509_LOOKUP_hash_dir _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_hash_dir
%xdefine _X509_LOOKUP_init _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_init
%xdefine _X509_LOOKUP_new _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_new
%xdefine _X509_LOOKUP_shutdown _ %+ XCRYPTO_PREFIX %+ _X509_LOOKUP_shutdown
%xdefine _X509_NAME_ENTRIES_it _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRIES_it
%xdefine _X509_NAME_ENTRY_create_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_create_by_NID
%xdefine _X509_NAME_ENTRY_create_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_create_by_OBJ
%xdefine _X509_NAME_ENTRY_create_by_txt _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_create_by_txt
%xdefine _X509_NAME_ENTRY_dup _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_dup
%xdefine _X509_NAME_ENTRY_free _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_free
%xdefine _X509_NAME_ENTRY_get_data _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_get_data
%xdefine _X509_NAME_ENTRY_get_object _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_get_object
%xdefine _X509_NAME_ENTRY_it _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_it
%xdefine _X509_NAME_ENTRY_new _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_new
%xdefine _X509_NAME_ENTRY_set _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_set
%xdefine _X509_NAME_ENTRY_set_data _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_set_data
%xdefine _X509_NAME_ENTRY_set_object _ %+ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_set_object
%xdefine _X509_NAME_INTERNAL_it _ %+ XCRYPTO_PREFIX %+ _X509_NAME_INTERNAL_it
%xdefine _X509_NAME_add_entry _ %+ XCRYPTO_PREFIX %+ _X509_NAME_add_entry
%xdefine _X509_NAME_add_entry_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_NAME_add_entry_by_NID
%xdefine _X509_NAME_add_entry_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_NAME_add_entry_by_OBJ
%xdefine _X509_NAME_add_entry_by_txt _ %+ XCRYPTO_PREFIX %+ _X509_NAME_add_entry_by_txt
%xdefine _X509_NAME_cmp _ %+ XCRYPTO_PREFIX %+ _X509_NAME_cmp
%xdefine _X509_NAME_delete_entry _ %+ XCRYPTO_PREFIX %+ _X509_NAME_delete_entry
%xdefine _X509_NAME_digest _ %+ XCRYPTO_PREFIX %+ _X509_NAME_digest
%xdefine _X509_NAME_dup _ %+ XCRYPTO_PREFIX %+ _X509_NAME_dup
%xdefine _X509_NAME_entry_count _ %+ XCRYPTO_PREFIX %+ _X509_NAME_entry_count
%xdefine _X509_NAME_free _ %+ XCRYPTO_PREFIX %+ _X509_NAME_free
%xdefine _X509_NAME_get0_der _ %+ XCRYPTO_PREFIX %+ _X509_NAME_get0_der
%xdefine _X509_NAME_get_entry _ %+ XCRYPTO_PREFIX %+ _X509_NAME_get_entry
%xdefine _X509_NAME_get_index_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_NAME_get_index_by_NID
%xdefine _X509_NAME_get_index_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_NAME_get_index_by_OBJ
%xdefine _X509_NAME_get_text_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_NAME_get_text_by_NID
%xdefine _X509_NAME_get_text_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_NAME_get_text_by_OBJ
%xdefine _X509_NAME_hash _ %+ XCRYPTO_PREFIX %+ _X509_NAME_hash
%xdefine _X509_NAME_hash_old _ %+ XCRYPTO_PREFIX %+ _X509_NAME_hash_old
%xdefine _X509_NAME_it _ %+ XCRYPTO_PREFIX %+ _X509_NAME_it
%xdefine _X509_NAME_new _ %+ XCRYPTO_PREFIX %+ _X509_NAME_new
%xdefine _X509_NAME_oneline _ %+ XCRYPTO_PREFIX %+ _X509_NAME_oneline
%xdefine _X509_NAME_print _ %+ XCRYPTO_PREFIX %+ _X509_NAME_print
%xdefine _X509_NAME_print_ex _ %+ XCRYPTO_PREFIX %+ _X509_NAME_print_ex
%xdefine _X509_NAME_print_ex_fp _ %+ XCRYPTO_PREFIX %+ _X509_NAME_print_ex_fp
%xdefine _X509_NAME_set _ %+ XCRYPTO_PREFIX %+ _X509_NAME_set
%xdefine _X509_OBJECT_free_contents _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_free_contents
%xdefine _X509_OBJECT_get0_X509 _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_get0_X509
%xdefine _X509_OBJECT_get_type _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_get_type
%xdefine _X509_OBJECT_idx_by_subject _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_idx_by_subject
%xdefine _X509_OBJECT_retrieve_by_subject _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_retrieve_by_subject
%xdefine _X509_OBJECT_retrieve_match _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_retrieve_match
%xdefine _X509_OBJECT_up_ref_count _ %+ XCRYPTO_PREFIX %+ _X509_OBJECT_up_ref_count
%xdefine _X509_PKEY_free _ %+ XCRYPTO_PREFIX %+ _X509_PKEY_free
%xdefine _X509_PKEY_new _ %+ XCRYPTO_PREFIX %+ _X509_PKEY_new
%xdefine _X509_POLICY_NODE_print _ %+ XCRYPTO_PREFIX %+ _X509_POLICY_NODE_print
%xdefine _X509_PUBKEY_free _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_free
%xdefine _X509_PUBKEY_get _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_get
%xdefine _X509_PUBKEY_get0_param _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_get0_param
%xdefine _X509_PUBKEY_it _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_it
%xdefine _X509_PUBKEY_new _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_new
%xdefine _X509_PUBKEY_set _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_set
%xdefine _X509_PUBKEY_set0_param _ %+ XCRYPTO_PREFIX %+ _X509_PUBKEY_set0_param
%xdefine _X509_PURPOSE_add _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_add
%xdefine _X509_PURPOSE_cleanup _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_cleanup
%xdefine _X509_PURPOSE_get0 _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get0
%xdefine _X509_PURPOSE_get0_name _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get0_name
%xdefine _X509_PURPOSE_get0_sname _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get0_sname
%xdefine _X509_PURPOSE_get_by_id _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get_by_id
%xdefine _X509_PURPOSE_get_by_sname _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get_by_sname
%xdefine _X509_PURPOSE_get_count _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get_count
%xdefine _X509_PURPOSE_get_id _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get_id
%xdefine _X509_PURPOSE_get_trust _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_get_trust
%xdefine _X509_PURPOSE_set _ %+ XCRYPTO_PREFIX %+ _X509_PURPOSE_set
%xdefine _X509_REQ_INFO_free _ %+ XCRYPTO_PREFIX %+ _X509_REQ_INFO_free
%xdefine _X509_REQ_INFO_it _ %+ XCRYPTO_PREFIX %+ _X509_REQ_INFO_it
%xdefine _X509_REQ_INFO_new _ %+ XCRYPTO_PREFIX %+ _X509_REQ_INFO_new
%xdefine _X509_REQ_add1_attr _ %+ XCRYPTO_PREFIX %+ _X509_REQ_add1_attr
%xdefine _X509_REQ_add1_attr_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_REQ_add1_attr_by_NID
%xdefine _X509_REQ_add1_attr_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_REQ_add1_attr_by_OBJ
%xdefine _X509_REQ_add1_attr_by_txt _ %+ XCRYPTO_PREFIX %+ _X509_REQ_add1_attr_by_txt
%xdefine _X509_REQ_add_extensions _ %+ XCRYPTO_PREFIX %+ _X509_REQ_add_extensions
%xdefine _X509_REQ_add_extensions_nid _ %+ XCRYPTO_PREFIX %+ _X509_REQ_add_extensions_nid
%xdefine _X509_REQ_check_private_key _ %+ XCRYPTO_PREFIX %+ _X509_REQ_check_private_key
%xdefine _X509_REQ_delete_attr _ %+ XCRYPTO_PREFIX %+ _X509_REQ_delete_attr
%xdefine _X509_REQ_digest _ %+ XCRYPTO_PREFIX %+ _X509_REQ_digest
%xdefine _X509_REQ_dup _ %+ XCRYPTO_PREFIX %+ _X509_REQ_dup
%xdefine _X509_REQ_extension_nid _ %+ XCRYPTO_PREFIX %+ _X509_REQ_extension_nid
%xdefine _X509_REQ_free _ %+ XCRYPTO_PREFIX %+ _X509_REQ_free
%xdefine _X509_REQ_get0_signature _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get0_signature
%xdefine _X509_REQ_get1_email _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get1_email
%xdefine _X509_REQ_get_attr _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_attr
%xdefine _X509_REQ_get_attr_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_attr_by_NID
%xdefine _X509_REQ_get_attr_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_attr_by_OBJ
%xdefine _X509_REQ_get_attr_count _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_attr_count
%xdefine _X509_REQ_get_extension_nids _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_extension_nids
%xdefine _X509_REQ_get_extensions _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_extensions
%xdefine _X509_REQ_get_pubkey _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_pubkey
%xdefine _X509_REQ_get_signature_nid _ %+ XCRYPTO_PREFIX %+ _X509_REQ_get_signature_nid
%xdefine _X509_REQ_it _ %+ XCRYPTO_PREFIX %+ _X509_REQ_it
%xdefine _X509_REQ_new _ %+ XCRYPTO_PREFIX %+ _X509_REQ_new
%xdefine _X509_REQ_print _ %+ XCRYPTO_PREFIX %+ _X509_REQ_print
%xdefine _X509_REQ_print_ex _ %+ XCRYPTO_PREFIX %+ _X509_REQ_print_ex
%xdefine _X509_REQ_print_fp _ %+ XCRYPTO_PREFIX %+ _X509_REQ_print_fp
%xdefine _X509_REQ_set_extension_nids _ %+ XCRYPTO_PREFIX %+ _X509_REQ_set_extension_nids
%xdefine _X509_REQ_set_pubkey _ %+ XCRYPTO_PREFIX %+ _X509_REQ_set_pubkey
%xdefine _X509_REQ_set_subject_name _ %+ XCRYPTO_PREFIX %+ _X509_REQ_set_subject_name
%xdefine _X509_REQ_set_version _ %+ XCRYPTO_PREFIX %+ _X509_REQ_set_version
%xdefine _X509_REQ_sign _ %+ XCRYPTO_PREFIX %+ _X509_REQ_sign
%xdefine _X509_REQ_sign_ctx _ %+ XCRYPTO_PREFIX %+ _X509_REQ_sign_ctx
%xdefine _X509_REQ_to_X509 _ %+ XCRYPTO_PREFIX %+ _X509_REQ_to_X509
%xdefine _X509_REQ_verify _ %+ XCRYPTO_PREFIX %+ _X509_REQ_verify
%xdefine _X509_REVOKED_add1_ext_i2d _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_add1_ext_i2d
%xdefine _X509_REVOKED_add_ext _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_add_ext
%xdefine _X509_REVOKED_delete_ext _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_delete_ext
%xdefine _X509_REVOKED_dup _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_dup
%xdefine _X509_REVOKED_free _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_free
%xdefine _X509_REVOKED_get0_revocationDate _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get0_revocationDate
%xdefine _X509_REVOKED_get0_serialNumber _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get0_serialNumber
%xdefine _X509_REVOKED_get_ext _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext
%xdefine _X509_REVOKED_get_ext_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_by_NID
%xdefine _X509_REVOKED_get_ext_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_by_OBJ
%xdefine _X509_REVOKED_get_ext_by_critical _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_by_critical
%xdefine _X509_REVOKED_get_ext_count _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_count
%xdefine _X509_REVOKED_get_ext_d2i _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_d2i
%xdefine _X509_REVOKED_it _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_it
%xdefine _X509_REVOKED_new _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_new
%xdefine _X509_REVOKED_set_revocationDate _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_set_revocationDate
%xdefine _X509_REVOKED_set_serialNumber _ %+ XCRYPTO_PREFIX %+ _X509_REVOKED_set_serialNumber
%xdefine _X509_SIG_free _ %+ XCRYPTO_PREFIX %+ _X509_SIG_free
%xdefine _X509_SIG_it _ %+ XCRYPTO_PREFIX %+ _X509_SIG_it
%xdefine _X509_SIG_new _ %+ XCRYPTO_PREFIX %+ _X509_SIG_new
%xdefine _X509_STORE_CTX_cleanup _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_cleanup
%xdefine _X509_STORE_CTX_free _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_free
%xdefine _X509_STORE_CTX_get0_cert _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_cert
%xdefine _X509_STORE_CTX_get0_chain _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_chain
%xdefine _X509_STORE_CTX_get0_current_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_current_crl
%xdefine _X509_STORE_CTX_get0_current_issuer _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_current_issuer
%xdefine _X509_STORE_CTX_get0_param _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_param
%xdefine _X509_STORE_CTX_get0_parent_ctx _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_parent_ctx
%xdefine _X509_STORE_CTX_get0_policy_tree _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_policy_tree
%xdefine _X509_STORE_CTX_get0_store _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_store
%xdefine _X509_STORE_CTX_get0_untrusted _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_untrusted
%xdefine _X509_STORE_CTX_get1_chain _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get1_chain
%xdefine _X509_STORE_CTX_get1_issuer _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get1_issuer
%xdefine _X509_STORE_CTX_get_chain _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_chain
%xdefine _X509_STORE_CTX_get_current_cert _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_current_cert
%xdefine _X509_STORE_CTX_get_error _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_error
%xdefine _X509_STORE_CTX_get_error_depth _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_error_depth
%xdefine _X509_STORE_CTX_get_ex_data _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_ex_data
%xdefine _X509_STORE_CTX_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_ex_new_index
%xdefine _X509_STORE_CTX_get_explicit_policy _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_explicit_policy
%xdefine _X509_STORE_CTX_init _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_init
%xdefine _X509_STORE_CTX_new _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_new
%xdefine _X509_STORE_CTX_purpose_inherit _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_purpose_inherit
%xdefine _X509_STORE_CTX_set0_crls _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set0_crls
%xdefine _X509_STORE_CTX_set0_param _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set0_param
%xdefine _X509_STORE_CTX_set_cert _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_cert
%xdefine _X509_STORE_CTX_set_chain _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_chain
%xdefine _X509_STORE_CTX_set_default _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_default
%xdefine _X509_STORE_CTX_set_depth _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_depth
%xdefine _X509_STORE_CTX_set_error _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_error
%xdefine _X509_STORE_CTX_set_ex_data _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_ex_data
%xdefine _X509_STORE_CTX_set_flags _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_flags
%xdefine _X509_STORE_CTX_set_purpose _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_purpose
%xdefine _X509_STORE_CTX_set_time _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_time
%xdefine _X509_STORE_CTX_set_trust _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_trust
%xdefine _X509_STORE_CTX_set_verify_cb _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_verify_cb
%xdefine _X509_STORE_CTX_trusted_stack _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_trusted_stack
%xdefine _X509_STORE_CTX_zero _ %+ XCRYPTO_PREFIX %+ _X509_STORE_CTX_zero
%xdefine _X509_STORE_add_cert _ %+ XCRYPTO_PREFIX %+ _X509_STORE_add_cert
%xdefine _X509_STORE_add_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_add_crl
%xdefine _X509_STORE_add_lookup _ %+ XCRYPTO_PREFIX %+ _X509_STORE_add_lookup
%xdefine _X509_STORE_free _ %+ XCRYPTO_PREFIX %+ _X509_STORE_free
%xdefine _X509_STORE_get0_objects _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get0_objects
%xdefine _X509_STORE_get0_param _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get0_param
%xdefine _X509_STORE_get1_certs _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get1_certs
%xdefine _X509_STORE_get1_crls _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get1_crls
%xdefine _X509_STORE_get_by_subject _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_by_subject
%xdefine _X509_STORE_get_cert_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_cert_crl
%xdefine _X509_STORE_get_check_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_check_crl
%xdefine _X509_STORE_get_check_issued _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_check_issued
%xdefine _X509_STORE_get_check_revocation _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_check_revocation
%xdefine _X509_STORE_get_cleanup _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_cleanup
%xdefine _X509_STORE_get_get_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_get_crl
%xdefine _X509_STORE_get_get_issuer _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_get_issuer
%xdefine _X509_STORE_get_lookup_certs _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_lookup_certs
%xdefine _X509_STORE_get_lookup_crls _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_lookup_crls
%xdefine _X509_STORE_get_verify _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_verify
%xdefine _X509_STORE_get_verify_cb _ %+ XCRYPTO_PREFIX %+ _X509_STORE_get_verify_cb
%xdefine _X509_STORE_load_locations _ %+ XCRYPTO_PREFIX %+ _X509_STORE_load_locations
%xdefine _X509_STORE_new _ %+ XCRYPTO_PREFIX %+ _X509_STORE_new
%xdefine _X509_STORE_set0_additional_untrusted _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set0_additional_untrusted
%xdefine _X509_STORE_set1_param _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set1_param
%xdefine _X509_STORE_set_cert_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_cert_crl
%xdefine _X509_STORE_set_check_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_check_crl
%xdefine _X509_STORE_set_check_issued _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_check_issued
%xdefine _X509_STORE_set_check_revocation _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_check_revocation
%xdefine _X509_STORE_set_cleanup _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_cleanup
%xdefine _X509_STORE_set_default_paths _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_default_paths
%xdefine _X509_STORE_set_depth _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_depth
%xdefine _X509_STORE_set_flags _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_flags
%xdefine _X509_STORE_set_get_crl _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_get_crl
%xdefine _X509_STORE_set_get_issuer _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_get_issuer
%xdefine _X509_STORE_set_lookup_certs _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_lookup_certs
%xdefine _X509_STORE_set_lookup_crls _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_lookup_crls
%xdefine _X509_STORE_set_purpose _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_purpose
%xdefine _X509_STORE_set_trust _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_trust
%xdefine _X509_STORE_set_verify _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_verify
%xdefine _X509_STORE_set_verify_cb _ %+ XCRYPTO_PREFIX %+ _X509_STORE_set_verify_cb
%xdefine _X509_STORE_up_ref _ %+ XCRYPTO_PREFIX %+ _X509_STORE_up_ref
%xdefine _X509_TRUST_add _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_add
%xdefine _X509_TRUST_cleanup _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_cleanup
%xdefine _X509_TRUST_get0 _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_get0
%xdefine _X509_TRUST_get0_name _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_get0_name
%xdefine _X509_TRUST_get_by_id _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_get_by_id
%xdefine _X509_TRUST_get_count _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_get_count
%xdefine _X509_TRUST_get_flags _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_get_flags
%xdefine _X509_TRUST_get_trust _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_get_trust
%xdefine _X509_TRUST_set _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_set
%xdefine _X509_TRUST_set_default _ %+ XCRYPTO_PREFIX %+ _X509_TRUST_set_default
%xdefine _X509_VAL_free _ %+ XCRYPTO_PREFIX %+ _X509_VAL_free
%xdefine _X509_VAL_it _ %+ XCRYPTO_PREFIX %+ _X509_VAL_it
%xdefine _X509_VAL_new _ %+ XCRYPTO_PREFIX %+ _X509_VAL_new
%xdefine _X509_VERIFY_PARAM_add0_policy _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_add0_policy
%xdefine _X509_VERIFY_PARAM_add0_table _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_add0_table
%xdefine _X509_VERIFY_PARAM_add1_host _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_add1_host
%xdefine _X509_VERIFY_PARAM_clear_flags _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_clear_flags
%xdefine _X509_VERIFY_PARAM_free _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_free
%xdefine _X509_VERIFY_PARAM_get0 _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get0
%xdefine _X509_VERIFY_PARAM_get0_name _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get0_name
%xdefine _X509_VERIFY_PARAM_get0_peername _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get0_peername
%xdefine _X509_VERIFY_PARAM_get_count _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get_count
%xdefine _X509_VERIFY_PARAM_get_depth _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get_depth
%xdefine _X509_VERIFY_PARAM_get_flags _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get_flags
%xdefine _X509_VERIFY_PARAM_inherit _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_inherit
%xdefine _X509_VERIFY_PARAM_lookup _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_lookup
%xdefine _X509_VERIFY_PARAM_new _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_new
%xdefine _X509_VERIFY_PARAM_set1 _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1
%xdefine _X509_VERIFY_PARAM_set1_email _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_email
%xdefine _X509_VERIFY_PARAM_set1_host _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_host
%xdefine _X509_VERIFY_PARAM_set1_ip _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_ip
%xdefine _X509_VERIFY_PARAM_set1_ip_asc _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_ip_asc
%xdefine _X509_VERIFY_PARAM_set1_name _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_name
%xdefine _X509_VERIFY_PARAM_set1_policies _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_policies
%xdefine _X509_VERIFY_PARAM_set_depth _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_depth
%xdefine _X509_VERIFY_PARAM_set_flags _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_flags
%xdefine _X509_VERIFY_PARAM_set_hostflags _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_hostflags
%xdefine _X509_VERIFY_PARAM_set_purpose _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_purpose
%xdefine _X509_VERIFY_PARAM_set_time _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_time
%xdefine _X509_VERIFY_PARAM_set_trust _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_trust
%xdefine _X509_VERIFY_PARAM_table_cleanup _ %+ XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_table_cleanup
%xdefine _X509_add1_ext_i2d _ %+ XCRYPTO_PREFIX %+ _X509_add1_ext_i2d
%xdefine _X509_add1_reject_object _ %+ XCRYPTO_PREFIX %+ _X509_add1_reject_object
%xdefine _X509_add1_trust_object _ %+ XCRYPTO_PREFIX %+ _X509_add1_trust_object
%xdefine _X509_add_ext _ %+ XCRYPTO_PREFIX %+ _X509_add_ext
%xdefine _X509_alias_get0 _ %+ XCRYPTO_PREFIX %+ _X509_alias_get0
%xdefine _X509_alias_set1 _ %+ XCRYPTO_PREFIX %+ _X509_alias_set1
%xdefine _X509_chain_check_suiteb _ %+ XCRYPTO_PREFIX %+ _X509_chain_check_suiteb
%xdefine _X509_chain_up_ref _ %+ XCRYPTO_PREFIX %+ _X509_chain_up_ref
%xdefine _X509_check_akid _ %+ XCRYPTO_PREFIX %+ _X509_check_akid
%xdefine _X509_check_ca _ %+ XCRYPTO_PREFIX %+ _X509_check_ca
%xdefine _X509_check_email _ %+ XCRYPTO_PREFIX %+ _X509_check_email
%xdefine _X509_check_host _ %+ XCRYPTO_PREFIX %+ _X509_check_host
%xdefine _X509_check_ip _ %+ XCRYPTO_PREFIX %+ _X509_check_ip
%xdefine _X509_check_ip_asc _ %+ XCRYPTO_PREFIX %+ _X509_check_ip_asc
%xdefine _X509_check_issued _ %+ XCRYPTO_PREFIX %+ _X509_check_issued
%xdefine _X509_check_private_key _ %+ XCRYPTO_PREFIX %+ _X509_check_private_key
%xdefine _X509_check_purpose _ %+ XCRYPTO_PREFIX %+ _X509_check_purpose
%xdefine _X509_check_trust _ %+ XCRYPTO_PREFIX %+ _X509_check_trust
%xdefine _X509_cmp _ %+ XCRYPTO_PREFIX %+ _X509_cmp
%xdefine _X509_cmp_current_time _ %+ XCRYPTO_PREFIX %+ _X509_cmp_current_time
%xdefine _X509_cmp_time _ %+ XCRYPTO_PREFIX %+ _X509_cmp_time
%xdefine _X509_delete_ext _ %+ XCRYPTO_PREFIX %+ _X509_delete_ext
%xdefine _X509_digest _ %+ XCRYPTO_PREFIX %+ _X509_digest
%xdefine _X509_dup _ %+ XCRYPTO_PREFIX %+ _X509_dup
%xdefine _X509_email_free _ %+ XCRYPTO_PREFIX %+ _X509_email_free
%xdefine _X509_find_by_issuer_and_serial _ %+ XCRYPTO_PREFIX %+ _X509_find_by_issuer_and_serial
%xdefine _X509_find_by_subject _ %+ XCRYPTO_PREFIX %+ _X509_find_by_subject
%xdefine _X509_free _ %+ XCRYPTO_PREFIX %+ _X509_free
%xdefine _X509_get0_extensions _ %+ XCRYPTO_PREFIX %+ _X509_get0_extensions
%xdefine _X509_get0_notAfter _ %+ XCRYPTO_PREFIX %+ _X509_get0_notAfter
%xdefine _X509_get0_notBefore _ %+ XCRYPTO_PREFIX %+ _X509_get0_notBefore
%xdefine _X509_get0_pubkey_bitstr _ %+ XCRYPTO_PREFIX %+ _X509_get0_pubkey_bitstr
%xdefine _X509_get0_signature _ %+ XCRYPTO_PREFIX %+ _X509_get0_signature
%xdefine _X509_get0_tbs_sigalg _ %+ XCRYPTO_PREFIX %+ _X509_get0_tbs_sigalg
%xdefine _X509_get1_email _ %+ XCRYPTO_PREFIX %+ _X509_get1_email
%xdefine _X509_get1_ocsp _ %+ XCRYPTO_PREFIX %+ _X509_get1_ocsp
%xdefine _X509_get_default_cert_area _ %+ XCRYPTO_PREFIX %+ _X509_get_default_cert_area
%xdefine _X509_get_default_cert_dir _ %+ XCRYPTO_PREFIX %+ _X509_get_default_cert_dir
%xdefine _X509_get_default_cert_dir_env _ %+ XCRYPTO_PREFIX %+ _X509_get_default_cert_dir_env
%xdefine _X509_get_default_cert_file _ %+ XCRYPTO_PREFIX %+ _X509_get_default_cert_file
%xdefine _X509_get_default_cert_file_env _ %+ XCRYPTO_PREFIX %+ _X509_get_default_cert_file_env
%xdefine _X509_get_default_private_dir _ %+ XCRYPTO_PREFIX %+ _X509_get_default_private_dir
%xdefine _X509_get_ex_data _ %+ XCRYPTO_PREFIX %+ _X509_get_ex_data
%xdefine _X509_get_ex_new_index _ %+ XCRYPTO_PREFIX %+ _X509_get_ex_new_index
%xdefine _X509_get_ext _ %+ XCRYPTO_PREFIX %+ _X509_get_ext
%xdefine _X509_get_ext_by_NID _ %+ XCRYPTO_PREFIX %+ _X509_get_ext_by_NID
%xdefine _X509_get_ext_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509_get_ext_by_OBJ
%xdefine _X509_get_ext_by_critical _ %+ XCRYPTO_PREFIX %+ _X509_get_ext_by_critical
%xdefine _X509_get_ext_count _ %+ XCRYPTO_PREFIX %+ _X509_get_ext_count
%xdefine _X509_get_ext_d2i _ %+ XCRYPTO_PREFIX %+ _X509_get_ext_d2i
%xdefine _X509_get_extended_key_usage _ %+ XCRYPTO_PREFIX %+ _X509_get_extended_key_usage
%xdefine _X509_get_extension_flags _ %+ XCRYPTO_PREFIX %+ _X509_get_extension_flags
%xdefine _X509_get_issuer_name _ %+ XCRYPTO_PREFIX %+ _X509_get_issuer_name
%xdefine _X509_get_key_usage _ %+ XCRYPTO_PREFIX %+ _X509_get_key_usage
%xdefine _X509_get_pubkey _ %+ XCRYPTO_PREFIX %+ _X509_get_pubkey
%xdefine _X509_get_serialNumber _ %+ XCRYPTO_PREFIX %+ _X509_get_serialNumber
%xdefine _X509_get_signature_nid _ %+ XCRYPTO_PREFIX %+ _X509_get_signature_nid
%xdefine _X509_get_subject_name _ %+ XCRYPTO_PREFIX %+ _X509_get_subject_name
%xdefine _X509_getm_notAfter _ %+ XCRYPTO_PREFIX %+ _X509_getm_notAfter
%xdefine _X509_getm_notBefore _ %+ XCRYPTO_PREFIX %+ _X509_getm_notBefore
%xdefine _X509_gmtime_adj _ %+ XCRYPTO_PREFIX %+ _X509_gmtime_adj
%xdefine _X509_issuer_and_serial_cmp _ %+ XCRYPTO_PREFIX %+ _X509_issuer_and_serial_cmp
%xdefine _X509_issuer_and_serial_hash _ %+ XCRYPTO_PREFIX %+ _X509_issuer_and_serial_hash
%xdefine _X509_issuer_name_cmp _ %+ XCRYPTO_PREFIX %+ _X509_issuer_name_cmp
%xdefine _X509_issuer_name_hash _ %+ XCRYPTO_PREFIX %+ _X509_issuer_name_hash
%xdefine _X509_issuer_name_hash_old _ %+ XCRYPTO_PREFIX %+ _X509_issuer_name_hash_old
%xdefine _X509_it _ %+ XCRYPTO_PREFIX %+ _X509_it
%xdefine _X509_keyid_get0 _ %+ XCRYPTO_PREFIX %+ _X509_keyid_get0
%xdefine _X509_keyid_set1 _ %+ XCRYPTO_PREFIX %+ _X509_keyid_set1
%xdefine _X509_load_cert_crl_file _ %+ XCRYPTO_PREFIX %+ _X509_load_cert_crl_file
%xdefine _X509_load_cert_file _ %+ XCRYPTO_PREFIX %+ _X509_load_cert_file
%xdefine _X509_load_crl_file _ %+ XCRYPTO_PREFIX %+ _X509_load_crl_file
%xdefine _X509_new _ %+ XCRYPTO_PREFIX %+ _X509_new
%xdefine _X509_ocspid_print _ %+ XCRYPTO_PREFIX %+ _X509_ocspid_print
%xdefine _X509_parse_from_buffer _ %+ XCRYPTO_PREFIX %+ _X509_parse_from_buffer
%xdefine _X509_policy_check _ %+ XCRYPTO_PREFIX %+ _X509_policy_check
%xdefine _X509_policy_level_get0_node _ %+ XCRYPTO_PREFIX %+ _X509_policy_level_get0_node
%xdefine _X509_policy_level_node_count _ %+ XCRYPTO_PREFIX %+ _X509_policy_level_node_count
%xdefine _X509_policy_node_get0_parent _ %+ XCRYPTO_PREFIX %+ _X509_policy_node_get0_parent
%xdefine _X509_policy_node_get0_policy _ %+ XCRYPTO_PREFIX %+ _X509_policy_node_get0_policy
%xdefine _X509_policy_node_get0_qualifiers _ %+ XCRYPTO_PREFIX %+ _X509_policy_node_get0_qualifiers
%xdefine _X509_policy_tree_free _ %+ XCRYPTO_PREFIX %+ _X509_policy_tree_free
%xdefine _X509_policy_tree_get0_level _ %+ XCRYPTO_PREFIX %+ _X509_policy_tree_get0_level
%xdefine _X509_policy_tree_get0_policies _ %+ XCRYPTO_PREFIX %+ _X509_policy_tree_get0_policies
%xdefine _X509_policy_tree_get0_user_policies _ %+ XCRYPTO_PREFIX %+ _X509_policy_tree_get0_user_policies
%xdefine _X509_policy_tree_level_count _ %+ XCRYPTO_PREFIX %+ _X509_policy_tree_level_count
%xdefine _X509_print _ %+ XCRYPTO_PREFIX %+ _X509_print
%xdefine _X509_print_ex _ %+ XCRYPTO_PREFIX %+ _X509_print_ex
%xdefine _X509_print_ex_fp _ %+ XCRYPTO_PREFIX %+ _X509_print_ex_fp
%xdefine _X509_print_fp _ %+ XCRYPTO_PREFIX %+ _X509_print_fp
%xdefine _X509_pubkey_digest _ %+ XCRYPTO_PREFIX %+ _X509_pubkey_digest
%xdefine _X509_reject_clear _ %+ XCRYPTO_PREFIX %+ _X509_reject_clear
%xdefine _X509_set_ex_data _ %+ XCRYPTO_PREFIX %+ _X509_set_ex_data
%xdefine _X509_set_issuer_name _ %+ XCRYPTO_PREFIX %+ _X509_set_issuer_name
%xdefine _X509_set_notAfter _ %+ XCRYPTO_PREFIX %+ _X509_set_notAfter
%xdefine _X509_set_notBefore _ %+ XCRYPTO_PREFIX %+ _X509_set_notBefore
%xdefine _X509_set_pubkey _ %+ XCRYPTO_PREFIX %+ _X509_set_pubkey
%xdefine _X509_set_serialNumber _ %+ XCRYPTO_PREFIX %+ _X509_set_serialNumber
%xdefine _X509_set_subject_name _ %+ XCRYPTO_PREFIX %+ _X509_set_subject_name
%xdefine _X509_set_version _ %+ XCRYPTO_PREFIX %+ _X509_set_version
%xdefine _X509_sign _ %+ XCRYPTO_PREFIX %+ _X509_sign
%xdefine _X509_sign_ctx _ %+ XCRYPTO_PREFIX %+ _X509_sign_ctx
%xdefine _X509_signature_dump _ %+ XCRYPTO_PREFIX %+ _X509_signature_dump
%xdefine _X509_signature_print _ %+ XCRYPTO_PREFIX %+ _X509_signature_print
%xdefine _X509_subject_name_cmp _ %+ XCRYPTO_PREFIX %+ _X509_subject_name_cmp
%xdefine _X509_subject_name_hash _ %+ XCRYPTO_PREFIX %+ _X509_subject_name_hash
%xdefine _X509_subject_name_hash_old _ %+ XCRYPTO_PREFIX %+ _X509_subject_name_hash_old
%xdefine _X509_supported_extension _ %+ XCRYPTO_PREFIX %+ _X509_supported_extension
%xdefine _X509_time_adj _ %+ XCRYPTO_PREFIX %+ _X509_time_adj
%xdefine _X509_time_adj_ex _ %+ XCRYPTO_PREFIX %+ _X509_time_adj_ex
%xdefine _X509_to_X509_REQ _ %+ XCRYPTO_PREFIX %+ _X509_to_X509_REQ
%xdefine _X509_trust_clear _ %+ XCRYPTO_PREFIX %+ _X509_trust_clear
%xdefine _X509_up_ref _ %+ XCRYPTO_PREFIX %+ _X509_up_ref
%xdefine _X509_verify _ %+ XCRYPTO_PREFIX %+ _X509_verify
%xdefine _X509_verify_cert _ %+ XCRYPTO_PREFIX %+ _X509_verify_cert
%xdefine _X509_verify_cert_error_string _ %+ XCRYPTO_PREFIX %+ _X509_verify_cert_error_string
%xdefine _X509at_add1_attr _ %+ XCRYPTO_PREFIX %+ _X509at_add1_attr
%xdefine _X509at_add1_attr_by_NID _ %+ XCRYPTO_PREFIX %+ _X509at_add1_attr_by_NID
%xdefine _X509at_add1_attr_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509at_add1_attr_by_OBJ
%xdefine _X509at_add1_attr_by_txt _ %+ XCRYPTO_PREFIX %+ _X509at_add1_attr_by_txt
%xdefine _X509at_delete_attr _ %+ XCRYPTO_PREFIX %+ _X509at_delete_attr
%xdefine _X509at_get0_data_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509at_get0_data_by_OBJ
%xdefine _X509at_get_attr _ %+ XCRYPTO_PREFIX %+ _X509at_get_attr
%xdefine _X509at_get_attr_by_NID _ %+ XCRYPTO_PREFIX %+ _X509at_get_attr_by_NID
%xdefine _X509at_get_attr_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509at_get_attr_by_OBJ
%xdefine _X509at_get_attr_count _ %+ XCRYPTO_PREFIX %+ _X509at_get_attr_count
%xdefine _X509v3_add_ext _ %+ XCRYPTO_PREFIX %+ _X509v3_add_ext
%xdefine _X509v3_delete_ext _ %+ XCRYPTO_PREFIX %+ _X509v3_delete_ext
%xdefine _X509v3_get_ext _ %+ XCRYPTO_PREFIX %+ _X509v3_get_ext
%xdefine _X509v3_get_ext_by_NID _ %+ XCRYPTO_PREFIX %+ _X509v3_get_ext_by_NID
%xdefine _X509v3_get_ext_by_OBJ _ %+ XCRYPTO_PREFIX %+ _X509v3_get_ext_by_OBJ
%xdefine _X509v3_get_ext_by_critical _ %+ XCRYPTO_PREFIX %+ _X509v3_get_ext_by_critical
%xdefine _X509v3_get_ext_count _ %+ XCRYPTO_PREFIX %+ _X509v3_get_ext_count
%xdefine ___clang_at_available_requires_core_foundation_framework _ %+ XCRYPTO_PREFIX %+ ___clang_at_available_requires_core_foundation_framework
%xdefine ___clang_call_terminate _ %+ XCRYPTO_PREFIX %+ ___clang_call_terminate
%xdefine _a2i_GENERAL_NAME _ %+ XCRYPTO_PREFIX %+ _a2i_GENERAL_NAME
%xdefine _a2i_IPADDRESS _ %+ XCRYPTO_PREFIX %+ _a2i_IPADDRESS
%xdefine _a2i_IPADDRESS_NC _ %+ XCRYPTO_PREFIX %+ _a2i_IPADDRESS_NC
%xdefine _a2i_ipadd _ %+ XCRYPTO_PREFIX %+ _a2i_ipadd
%xdefine _aes128gcmsiv_aes_ks _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_aes_ks
%xdefine _aes128gcmsiv_aes_ks_enc_x1 _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_aes_ks_enc_x1
%xdefine _aes128gcmsiv_dec _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_dec
%xdefine _aes128gcmsiv_ecb_enc_block _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_ecb_enc_block
%xdefine _aes128gcmsiv_enc_msg_x4 _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_enc_msg_x4
%xdefine _aes128gcmsiv_enc_msg_x8 _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_enc_msg_x8
%xdefine _aes128gcmsiv_kdf _ %+ XCRYPTO_PREFIX %+ _aes128gcmsiv_kdf
%xdefine _aes256gcmsiv_aes_ks _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_aes_ks
%xdefine _aes256gcmsiv_aes_ks_enc_x1 _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_aes_ks_enc_x1
%xdefine _aes256gcmsiv_dec _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_dec
%xdefine _aes256gcmsiv_ecb_enc_block _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_ecb_enc_block
%xdefine _aes256gcmsiv_enc_msg_x4 _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_enc_msg_x4
%xdefine _aes256gcmsiv_enc_msg_x8 _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_enc_msg_x8
%xdefine _aes256gcmsiv_kdf _ %+ XCRYPTO_PREFIX %+ _aes256gcmsiv_kdf
%xdefine _aes_ctr_set_key _ %+ XCRYPTO_PREFIX %+ _aes_ctr_set_key
%xdefine _aes_hw_cbc_encrypt _ %+ XCRYPTO_PREFIX %+ _aes_hw_cbc_encrypt
%xdefine _aes_hw_ctr32_encrypt_blocks _ %+ XCRYPTO_PREFIX %+ _aes_hw_ctr32_encrypt_blocks
%xdefine _aes_hw_decrypt _ %+ XCRYPTO_PREFIX %+ _aes_hw_decrypt
%xdefine _aes_hw_ecb_encrypt _ %+ XCRYPTO_PREFIX %+ _aes_hw_ecb_encrypt
%xdefine _aes_hw_encrypt _ %+ XCRYPTO_PREFIX %+ _aes_hw_encrypt
%xdefine _aes_hw_set_decrypt_key _ %+ XCRYPTO_PREFIX %+ _aes_hw_set_decrypt_key
%xdefine _aes_hw_set_encrypt_key _ %+ XCRYPTO_PREFIX %+ _aes_hw_set_encrypt_key
%xdefine _aes_nohw_cbc_encrypt _ %+ XCRYPTO_PREFIX %+ _aes_nohw_cbc_encrypt
%xdefine _aes_nohw_ctr32_encrypt_blocks _ %+ XCRYPTO_PREFIX %+ _aes_nohw_ctr32_encrypt_blocks
%xdefine _aes_nohw_decrypt _ %+ XCRYPTO_PREFIX %+ _aes_nohw_decrypt
%xdefine _aes_nohw_encrypt _ %+ XCRYPTO_PREFIX %+ _aes_nohw_encrypt
%xdefine _aes_nohw_set_decrypt_key _ %+ XCRYPTO_PREFIX %+ _aes_nohw_set_decrypt_key
%xdefine _aes_nohw_set_encrypt_key _ %+ XCRYPTO_PREFIX %+ _aes_nohw_set_encrypt_key
%xdefine _aesgcmsiv_htable6_init _ %+ XCRYPTO_PREFIX %+ _aesgcmsiv_htable6_init
%xdefine _aesgcmsiv_htable_init _ %+ XCRYPTO_PREFIX %+ _aesgcmsiv_htable_init
%xdefine _aesgcmsiv_htable_polyval _ %+ XCRYPTO_PREFIX %+ _aesgcmsiv_htable_polyval
%xdefine _aesgcmsiv_polyval_horner _ %+ XCRYPTO_PREFIX %+ _aesgcmsiv_polyval_horner
%xdefine _aesni_gcm_decrypt _ %+ XCRYPTO_PREFIX %+ _aesni_gcm_decrypt
%xdefine _aesni_gcm_encrypt _ %+ XCRYPTO_PREFIX %+ _aesni_gcm_encrypt
%xdefine _asn1_do_adb _ %+ XCRYPTO_PREFIX %+ _asn1_do_adb
%xdefine _asn1_enc_free _ %+ XCRYPTO_PREFIX %+ _asn1_enc_free
%xdefine _asn1_enc_init _ %+ XCRYPTO_PREFIX %+ _asn1_enc_init
%xdefine _asn1_enc_restore _ %+ XCRYPTO_PREFIX %+ _asn1_enc_restore
%xdefine _asn1_enc_save _ %+ XCRYPTO_PREFIX %+ _asn1_enc_save
%xdefine _asn1_ex_c2i _ %+ XCRYPTO_PREFIX %+ _asn1_ex_c2i
%xdefine _asn1_ex_i2c _ %+ XCRYPTO_PREFIX %+ _asn1_ex_i2c
%xdefine _asn1_generalizedtime_to_tm _ %+ XCRYPTO_PREFIX %+ _asn1_generalizedtime_to_tm
%xdefine _asn1_get_choice_selector _ %+ XCRYPTO_PREFIX %+ _asn1_get_choice_selector
%xdefine _asn1_get_field_ptr _ %+ XCRYPTO_PREFIX %+ _asn1_get_field_ptr
%xdefine _asn1_item_combine_free _ %+ XCRYPTO_PREFIX %+ _asn1_item_combine_free
%xdefine _asn1_refcount_dec_and_test_zero _ %+ XCRYPTO_PREFIX %+ _asn1_refcount_dec_and_test_zero
%xdefine _asn1_refcount_set_one _ %+ XCRYPTO_PREFIX %+ _asn1_refcount_set_one
%xdefine _asn1_set_choice_selector _ %+ XCRYPTO_PREFIX %+ _asn1_set_choice_selector
%xdefine _asn1_utctime_to_tm _ %+ XCRYPTO_PREFIX %+ _asn1_utctime_to_tm
%xdefine _beeu_mod_inverse_vartime _ %+ XCRYPTO_PREFIX %+ _beeu_mod_inverse_vartime
%xdefine _bio_clear_socket_error _ %+ XCRYPTO_PREFIX %+ _bio_clear_socket_error
%xdefine _bio_fd_should_retry _ %+ XCRYPTO_PREFIX %+ _bio_fd_should_retry
%xdefine _bio_ip_and_port_to_socket_and_addr _ %+ XCRYPTO_PREFIX %+ _bio_ip_and_port_to_socket_and_addr
%xdefine _bio_sock_error _ %+ XCRYPTO_PREFIX %+ _bio_sock_error
%xdefine _bio_socket_nbio _ %+ XCRYPTO_PREFIX %+ _bio_socket_nbio
%xdefine _bn_abs_sub_consttime _ %+ XCRYPTO_PREFIX %+ _bn_abs_sub_consttime
%xdefine _bn_add_words _ %+ XCRYPTO_PREFIX %+ _bn_add_words
%xdefine _bn_copy_words _ %+ XCRYPTO_PREFIX %+ _bn_copy_words
%xdefine _bn_div_consttime _ %+ XCRYPTO_PREFIX %+ _bn_div_consttime
%xdefine _bn_expand _ %+ XCRYPTO_PREFIX %+ _bn_expand
%xdefine _bn_fits_in_words _ %+ XCRYPTO_PREFIX %+ _bn_fits_in_words
%xdefine _bn_from_montgomery _ %+ XCRYPTO_PREFIX %+ _bn_from_montgomery
%xdefine _bn_from_montgomery_small _ %+ XCRYPTO_PREFIX %+ _bn_from_montgomery_small
%xdefine _bn_gather5 _ %+ XCRYPTO_PREFIX %+ _bn_gather5
%xdefine _bn_in_range_words _ %+ XCRYPTO_PREFIX %+ _bn_in_range_words
%xdefine _bn_is_bit_set_words _ %+ XCRYPTO_PREFIX %+ _bn_is_bit_set_words
%xdefine _bn_is_relatively_prime _ %+ XCRYPTO_PREFIX %+ _bn_is_relatively_prime
%xdefine _bn_jacobi _ %+ XCRYPTO_PREFIX %+ _bn_jacobi
%xdefine _bn_lcm_consttime _ %+ XCRYPTO_PREFIX %+ _bn_lcm_consttime
%xdefine _bn_less_than_montgomery_R _ %+ XCRYPTO_PREFIX %+ _bn_less_than_montgomery_R
%xdefine _bn_less_than_words _ %+ XCRYPTO_PREFIX %+ _bn_less_than_words
%xdefine _bn_miller_rabin_init _ %+ XCRYPTO_PREFIX %+ _bn_miller_rabin_init
%xdefine _bn_miller_rabin_iteration _ %+ XCRYPTO_PREFIX %+ _bn_miller_rabin_iteration
%xdefine _bn_minimal_width _ %+ XCRYPTO_PREFIX %+ _bn_minimal_width
%xdefine _bn_mod_add_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_add_consttime
%xdefine _bn_mod_add_words _ %+ XCRYPTO_PREFIX %+ _bn_mod_add_words
%xdefine _bn_mod_exp_base_2_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_exp_base_2_consttime
%xdefine _bn_mod_exp_mont_small _ %+ XCRYPTO_PREFIX %+ _bn_mod_exp_mont_small
%xdefine _bn_mod_inverse0_prime_mont_small _ %+ XCRYPTO_PREFIX %+ _bn_mod_inverse0_prime_mont_small
%xdefine _bn_mod_inverse_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_inverse_consttime
%xdefine _bn_mod_inverse_prime _ %+ XCRYPTO_PREFIX %+ _bn_mod_inverse_prime
%xdefine _bn_mod_inverse_secret_prime _ %+ XCRYPTO_PREFIX %+ _bn_mod_inverse_secret_prime
%xdefine _bn_mod_lshift1_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_lshift1_consttime
%xdefine _bn_mod_lshift_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_lshift_consttime
%xdefine _bn_mod_mul_montgomery_small _ %+ XCRYPTO_PREFIX %+ _bn_mod_mul_montgomery_small
%xdefine _bn_mod_sub_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_sub_consttime
%xdefine _bn_mod_sub_words _ %+ XCRYPTO_PREFIX %+ _bn_mod_sub_words
%xdefine _bn_mod_u16_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mod_u16_consttime
%xdefine _bn_mont_n0 _ %+ XCRYPTO_PREFIX %+ _bn_mont_n0
%xdefine _bn_mul_add_words _ %+ XCRYPTO_PREFIX %+ _bn_mul_add_words
%xdefine _bn_mul_comba4 _ %+ XCRYPTO_PREFIX %+ _bn_mul_comba4
%xdefine _bn_mul_comba8 _ %+ XCRYPTO_PREFIX %+ _bn_mul_comba8
%xdefine _bn_mul_consttime _ %+ XCRYPTO_PREFIX %+ _bn_mul_consttime
%xdefine _bn_mul_mont _ %+ XCRYPTO_PREFIX %+ _bn_mul_mont
%xdefine _bn_mul_mont_gather5 _ %+ XCRYPTO_PREFIX %+ _bn_mul_mont_gather5
%xdefine _bn_mul_small _ %+ XCRYPTO_PREFIX %+ _bn_mul_small
%xdefine _bn_mul_words _ %+ XCRYPTO_PREFIX %+ _bn_mul_words
%xdefine _bn_odd_number_is_obviously_composite _ %+ XCRYPTO_PREFIX %+ _bn_odd_number_is_obviously_composite
%xdefine _bn_one_to_montgomery _ %+ XCRYPTO_PREFIX %+ _bn_one_to_montgomery
%xdefine _bn_power5 _ %+ XCRYPTO_PREFIX %+ _bn_power5
%xdefine _bn_rand_range_words _ %+ XCRYPTO_PREFIX %+ _bn_rand_range_words
%xdefine _bn_rand_secret_range _ %+ XCRYPTO_PREFIX %+ _bn_rand_secret_range
%xdefine _bn_reduce_once _ %+ XCRYPTO_PREFIX %+ _bn_reduce_once
%xdefine _bn_reduce_once_in_place _ %+ XCRYPTO_PREFIX %+ _bn_reduce_once_in_place
%xdefine _bn_resize_words _ %+ XCRYPTO_PREFIX %+ _bn_resize_words
%xdefine _bn_rshift1_words _ %+ XCRYPTO_PREFIX %+ _bn_rshift1_words
%xdefine _bn_rshift_secret_shift _ %+ XCRYPTO_PREFIX %+ _bn_rshift_secret_shift
%xdefine _bn_rshift_words _ %+ XCRYPTO_PREFIX %+ _bn_rshift_words
%xdefine _bn_scatter5 _ %+ XCRYPTO_PREFIX %+ _bn_scatter5
%xdefine _bn_select_words _ %+ XCRYPTO_PREFIX %+ _bn_select_words
%xdefine _bn_set_minimal_width _ %+ XCRYPTO_PREFIX %+ _bn_set_minimal_width
%xdefine _bn_set_words _ %+ XCRYPTO_PREFIX %+ _bn_set_words
%xdefine _bn_sqr8x_internal _ %+ XCRYPTO_PREFIX %+ _bn_sqr8x_internal
%xdefine _bn_sqr_comba4 _ %+ XCRYPTO_PREFIX %+ _bn_sqr_comba4
%xdefine _bn_sqr_comba8 _ %+ XCRYPTO_PREFIX %+ _bn_sqr_comba8
%xdefine _bn_sqr_consttime _ %+ XCRYPTO_PREFIX %+ _bn_sqr_consttime
%xdefine _bn_sqr_small _ %+ XCRYPTO_PREFIX %+ _bn_sqr_small
%xdefine _bn_sqr_words _ %+ XCRYPTO_PREFIX %+ _bn_sqr_words
%xdefine _bn_sqrx8x_internal _ %+ XCRYPTO_PREFIX %+ _bn_sqrx8x_internal
%xdefine _bn_sub_words _ %+ XCRYPTO_PREFIX %+ _bn_sub_words
%xdefine _bn_to_montgomery_small _ %+ XCRYPTO_PREFIX %+ _bn_to_montgomery_small
%xdefine _bn_uadd_consttime _ %+ XCRYPTO_PREFIX %+ _bn_uadd_consttime
%xdefine _bn_usub_consttime _ %+ XCRYPTO_PREFIX %+ _bn_usub_consttime
%xdefine _bn_wexpand _ %+ XCRYPTO_PREFIX %+ _bn_wexpand
%xdefine _boringssl_fips_self_test _ %+ XCRYPTO_PREFIX %+ _boringssl_fips_self_test
%xdefine _c2i_ASN1_BIT_STRING _ %+ XCRYPTO_PREFIX %+ _c2i_ASN1_BIT_STRING
%xdefine _c2i_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _c2i_ASN1_INTEGER
%xdefine _c2i_ASN1_OBJECT _ %+ XCRYPTO_PREFIX %+ _c2i_ASN1_OBJECT
%xdefine _cbb_add_latin1 _ %+ XCRYPTO_PREFIX %+ _cbb_add_latin1
%xdefine _cbb_add_ucs2_be _ %+ XCRYPTO_PREFIX %+ _cbb_add_ucs2_be
%xdefine _cbb_add_utf32_be _ %+ XCRYPTO_PREFIX %+ _cbb_add_utf32_be
%xdefine _cbb_add_utf8 _ %+ XCRYPTO_PREFIX %+ _cbb_add_utf8
%xdefine _cbb_get_utf8_len _ %+ XCRYPTO_PREFIX %+ _cbb_get_utf8_len
%xdefine _cbs_get_latin1 _ %+ XCRYPTO_PREFIX %+ _cbs_get_latin1
%xdefine _cbs_get_ucs2_be _ %+ XCRYPTO_PREFIX %+ _cbs_get_ucs2_be
%xdefine _cbs_get_utf32_be _ %+ XCRYPTO_PREFIX %+ _cbs_get_utf32_be
%xdefine _cbs_get_utf8 _ %+ XCRYPTO_PREFIX %+ _cbs_get_utf8
%xdefine _chacha20_poly1305_open _ %+ XCRYPTO_PREFIX %+ _chacha20_poly1305_open
%xdefine _chacha20_poly1305_seal _ %+ XCRYPTO_PREFIX %+ _chacha20_poly1305_seal
%xdefine _crypto_gcm_clmul_enabled _ %+ XCRYPTO_PREFIX %+ _crypto_gcm_clmul_enabled
%xdefine _d2i_ACCESS_DESCRIPTION _ %+ XCRYPTO_PREFIX %+ _d2i_ACCESS_DESCRIPTION
%xdefine _d2i_ASN1_BIT_STRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_BIT_STRING
%xdefine _d2i_ASN1_BMPSTRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_BMPSTRING
%xdefine _d2i_ASN1_BOOLEAN _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_BOOLEAN
%xdefine _d2i_ASN1_ENUMERATED _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_ENUMERATED
%xdefine _d2i_ASN1_GENERALIZEDTIME _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_GENERALIZEDTIME
%xdefine _d2i_ASN1_GENERALSTRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_GENERALSTRING
%xdefine _d2i_ASN1_IA5STRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_IA5STRING
%xdefine _d2i_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_INTEGER
%xdefine _d2i_ASN1_NULL _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_NULL
%xdefine _d2i_ASN1_OBJECT _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_OBJECT
%xdefine _d2i_ASN1_OCTET_STRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_OCTET_STRING
%xdefine _d2i_ASN1_PRINTABLE _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_PRINTABLE
%xdefine _d2i_ASN1_PRINTABLESTRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_PRINTABLESTRING
%xdefine _d2i_ASN1_SEQUENCE_ANY _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_SEQUENCE_ANY
%xdefine _d2i_ASN1_SET_ANY _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_SET_ANY
%xdefine _d2i_ASN1_T61STRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_T61STRING
%xdefine _d2i_ASN1_TIME _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_TIME
%xdefine _d2i_ASN1_TYPE _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_TYPE
%xdefine _d2i_ASN1_UNIVERSALSTRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_UNIVERSALSTRING
%xdefine _d2i_ASN1_UTCTIME _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_UTCTIME
%xdefine _d2i_ASN1_UTF8STRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_UTF8STRING
%xdefine _d2i_ASN1_VISIBLESTRING _ %+ XCRYPTO_PREFIX %+ _d2i_ASN1_VISIBLESTRING
%xdefine _d2i_AUTHORITY_INFO_ACCESS _ %+ XCRYPTO_PREFIX %+ _d2i_AUTHORITY_INFO_ACCESS
%xdefine _d2i_AUTHORITY_KEYID _ %+ XCRYPTO_PREFIX %+ _d2i_AUTHORITY_KEYID
%xdefine _d2i_AutoPrivateKey _ %+ XCRYPTO_PREFIX %+ _d2i_AutoPrivateKey
%xdefine _d2i_BASIC_CONSTRAINTS _ %+ XCRYPTO_PREFIX %+ _d2i_BASIC_CONSTRAINTS
%xdefine _d2i_CERTIFICATEPOLICIES _ %+ XCRYPTO_PREFIX %+ _d2i_CERTIFICATEPOLICIES
%xdefine _d2i_CRL_DIST_POINTS _ %+ XCRYPTO_PREFIX %+ _d2i_CRL_DIST_POINTS
%xdefine _d2i_DHparams _ %+ XCRYPTO_PREFIX %+ _d2i_DHparams
%xdefine _d2i_DHparams_bio _ %+ XCRYPTO_PREFIX %+ _d2i_DHparams_bio
%xdefine _d2i_DIRECTORYSTRING _ %+ XCRYPTO_PREFIX %+ _d2i_DIRECTORYSTRING
%xdefine _d2i_DISPLAYTEXT _ %+ XCRYPTO_PREFIX %+ _d2i_DISPLAYTEXT
%xdefine _d2i_DIST_POINT _ %+ XCRYPTO_PREFIX %+ _d2i_DIST_POINT
%xdefine _d2i_DIST_POINT_NAME _ %+ XCRYPTO_PREFIX %+ _d2i_DIST_POINT_NAME
%xdefine _d2i_DSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _d2i_DSAPrivateKey
%xdefine _d2i_DSAPrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _d2i_DSAPrivateKey_bio
%xdefine _d2i_DSAPrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _d2i_DSAPrivateKey_fp
%xdefine _d2i_DSAPublicKey _ %+ XCRYPTO_PREFIX %+ _d2i_DSAPublicKey
%xdefine _d2i_DSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _d2i_DSA_PUBKEY
%xdefine _d2i_DSA_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _d2i_DSA_PUBKEY_bio
%xdefine _d2i_DSA_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _d2i_DSA_PUBKEY_fp
%xdefine _d2i_DSA_SIG _ %+ XCRYPTO_PREFIX %+ _d2i_DSA_SIG
%xdefine _d2i_DSAparams _ %+ XCRYPTO_PREFIX %+ _d2i_DSAparams
%xdefine _d2i_ECDSA_SIG _ %+ XCRYPTO_PREFIX %+ _d2i_ECDSA_SIG
%xdefine _d2i_ECParameters _ %+ XCRYPTO_PREFIX %+ _d2i_ECParameters
%xdefine _d2i_ECPrivateKey _ %+ XCRYPTO_PREFIX %+ _d2i_ECPrivateKey
%xdefine _d2i_ECPrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _d2i_ECPrivateKey_bio
%xdefine _d2i_ECPrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _d2i_ECPrivateKey_fp
%xdefine _d2i_EC_PUBKEY _ %+ XCRYPTO_PREFIX %+ _d2i_EC_PUBKEY
%xdefine _d2i_EC_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _d2i_EC_PUBKEY_bio
%xdefine _d2i_EC_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _d2i_EC_PUBKEY_fp
%xdefine _d2i_EDIPARTYNAME _ %+ XCRYPTO_PREFIX %+ _d2i_EDIPARTYNAME
%xdefine _d2i_EXTENDED_KEY_USAGE _ %+ XCRYPTO_PREFIX %+ _d2i_EXTENDED_KEY_USAGE
%xdefine _d2i_GENERAL_NAME _ %+ XCRYPTO_PREFIX %+ _d2i_GENERAL_NAME
%xdefine _d2i_GENERAL_NAMES _ %+ XCRYPTO_PREFIX %+ _d2i_GENERAL_NAMES
%xdefine _d2i_ISSUING_DIST_POINT _ %+ XCRYPTO_PREFIX %+ _d2i_ISSUING_DIST_POINT
%xdefine _d2i_NETSCAPE_SPKAC _ %+ XCRYPTO_PREFIX %+ _d2i_NETSCAPE_SPKAC
%xdefine _d2i_NETSCAPE_SPKI _ %+ XCRYPTO_PREFIX %+ _d2i_NETSCAPE_SPKI
%xdefine _d2i_NOTICEREF _ %+ XCRYPTO_PREFIX %+ _d2i_NOTICEREF
%xdefine _d2i_OTHERNAME _ %+ XCRYPTO_PREFIX %+ _d2i_OTHERNAME
%xdefine _d2i_PKCS12 _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS12
%xdefine _d2i_PKCS12_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS12_bio
%xdefine _d2i_PKCS12_fp _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS12_fp
%xdefine _d2i_PKCS7 _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS7
%xdefine _d2i_PKCS7_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS7_bio
%xdefine _d2i_PKCS8PrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8PrivateKey_bio
%xdefine _d2i_PKCS8PrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8PrivateKey_fp
%xdefine _d2i_PKCS8_PRIV_KEY_INFO _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8_PRIV_KEY_INFO
%xdefine _d2i_PKCS8_PRIV_KEY_INFO_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8_PRIV_KEY_INFO_bio
%xdefine _d2i_PKCS8_PRIV_KEY_INFO_fp _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8_PRIV_KEY_INFO_fp
%xdefine _d2i_PKCS8_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8_bio
%xdefine _d2i_PKCS8_fp _ %+ XCRYPTO_PREFIX %+ _d2i_PKCS8_fp
%xdefine _d2i_PKEY_USAGE_PERIOD _ %+ XCRYPTO_PREFIX %+ _d2i_PKEY_USAGE_PERIOD
%xdefine _d2i_POLICYINFO _ %+ XCRYPTO_PREFIX %+ _d2i_POLICYINFO
%xdefine _d2i_POLICYQUALINFO _ %+ XCRYPTO_PREFIX %+ _d2i_POLICYQUALINFO
%xdefine _d2i_PROXY_CERT_INFO_EXTENSION _ %+ XCRYPTO_PREFIX %+ _d2i_PROXY_CERT_INFO_EXTENSION
%xdefine _d2i_PROXY_POLICY _ %+ XCRYPTO_PREFIX %+ _d2i_PROXY_POLICY
%xdefine _d2i_PUBKEY _ %+ XCRYPTO_PREFIX %+ _d2i_PUBKEY
%xdefine _d2i_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PUBKEY_bio
%xdefine _d2i_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _d2i_PUBKEY_fp
%xdefine _d2i_PrivateKey _ %+ XCRYPTO_PREFIX %+ _d2i_PrivateKey
%xdefine _d2i_PrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _d2i_PrivateKey_bio
%xdefine _d2i_PrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _d2i_PrivateKey_fp
%xdefine _d2i_PublicKey _ %+ XCRYPTO_PREFIX %+ _d2i_PublicKey
%xdefine _d2i_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _d2i_RSAPrivateKey
%xdefine _d2i_RSAPrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _d2i_RSAPrivateKey_bio
%xdefine _d2i_RSAPrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _d2i_RSAPrivateKey_fp
%xdefine _d2i_RSAPublicKey _ %+ XCRYPTO_PREFIX %+ _d2i_RSAPublicKey
%xdefine _d2i_RSAPublicKey_bio _ %+ XCRYPTO_PREFIX %+ _d2i_RSAPublicKey_bio
%xdefine _d2i_RSAPublicKey_fp _ %+ XCRYPTO_PREFIX %+ _d2i_RSAPublicKey_fp
%xdefine _d2i_RSA_PSS_PARAMS _ %+ XCRYPTO_PREFIX %+ _d2i_RSA_PSS_PARAMS
%xdefine _d2i_RSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _d2i_RSA_PUBKEY
%xdefine _d2i_RSA_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _d2i_RSA_PUBKEY_bio
%xdefine _d2i_RSA_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _d2i_RSA_PUBKEY_fp
%xdefine _d2i_SSL_SESSION _ %+ XCRYPTO_PREFIX %+ _d2i_SSL_SESSION
%xdefine _d2i_SSL_SESSION_bio _ %+ XCRYPTO_PREFIX %+ _d2i_SSL_SESSION_bio
%xdefine _d2i_SXNET _ %+ XCRYPTO_PREFIX %+ _d2i_SXNET
%xdefine _d2i_SXNETID _ %+ XCRYPTO_PREFIX %+ _d2i_SXNETID
%xdefine _d2i_USERNOTICE _ %+ XCRYPTO_PREFIX %+ _d2i_USERNOTICE
%xdefine _d2i_X509 _ %+ XCRYPTO_PREFIX %+ _d2i_X509
%xdefine _d2i_X509_ALGOR _ %+ XCRYPTO_PREFIX %+ _d2i_X509_ALGOR
%xdefine _d2i_X509_ALGORS _ %+ XCRYPTO_PREFIX %+ _d2i_X509_ALGORS
%xdefine _d2i_X509_ATTRIBUTE _ %+ XCRYPTO_PREFIX %+ _d2i_X509_ATTRIBUTE
%xdefine _d2i_X509_AUX _ %+ XCRYPTO_PREFIX %+ _d2i_X509_AUX
%xdefine _d2i_X509_CERT_AUX _ %+ XCRYPTO_PREFIX %+ _d2i_X509_CERT_AUX
%xdefine _d2i_X509_CINF _ %+ XCRYPTO_PREFIX %+ _d2i_X509_CINF
%xdefine _d2i_X509_CRL _ %+ XCRYPTO_PREFIX %+ _d2i_X509_CRL
%xdefine _d2i_X509_CRL_INFO _ %+ XCRYPTO_PREFIX %+ _d2i_X509_CRL_INFO
%xdefine _d2i_X509_CRL_bio _ %+ XCRYPTO_PREFIX %+ _d2i_X509_CRL_bio
%xdefine _d2i_X509_CRL_fp _ %+ XCRYPTO_PREFIX %+ _d2i_X509_CRL_fp
%xdefine _d2i_X509_EXTENSION _ %+ XCRYPTO_PREFIX %+ _d2i_X509_EXTENSION
%xdefine _d2i_X509_EXTENSIONS _ %+ XCRYPTO_PREFIX %+ _d2i_X509_EXTENSIONS
%xdefine _d2i_X509_NAME _ %+ XCRYPTO_PREFIX %+ _d2i_X509_NAME
%xdefine _d2i_X509_NAME_ENTRY _ %+ XCRYPTO_PREFIX %+ _d2i_X509_NAME_ENTRY
%xdefine _d2i_X509_PUBKEY _ %+ XCRYPTO_PREFIX %+ _d2i_X509_PUBKEY
%xdefine _d2i_X509_REQ _ %+ XCRYPTO_PREFIX %+ _d2i_X509_REQ
%xdefine _d2i_X509_REQ_INFO _ %+ XCRYPTO_PREFIX %+ _d2i_X509_REQ_INFO
%xdefine _d2i_X509_REQ_bio _ %+ XCRYPTO_PREFIX %+ _d2i_X509_REQ_bio
%xdefine _d2i_X509_REQ_fp _ %+ XCRYPTO_PREFIX %+ _d2i_X509_REQ_fp
%xdefine _d2i_X509_REVOKED _ %+ XCRYPTO_PREFIX %+ _d2i_X509_REVOKED
%xdefine _d2i_X509_SIG _ %+ XCRYPTO_PREFIX %+ _d2i_X509_SIG
%xdefine _d2i_X509_VAL _ %+ XCRYPTO_PREFIX %+ _d2i_X509_VAL
%xdefine _d2i_X509_bio _ %+ XCRYPTO_PREFIX %+ _d2i_X509_bio
%xdefine _d2i_X509_fp _ %+ XCRYPTO_PREFIX %+ _d2i_X509_fp
%xdefine _dsa_asn1_meth _ %+ XCRYPTO_PREFIX %+ _dsa_asn1_meth
%xdefine _ec_GFp_mont_add _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_add
%xdefine _ec_GFp_mont_dbl _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_dbl
%xdefine _ec_GFp_mont_felem_from_bytes _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_from_bytes
%xdefine _ec_GFp_mont_felem_mul _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_mul
%xdefine _ec_GFp_mont_felem_sqr _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_sqr
%xdefine _ec_GFp_mont_felem_to_bytes _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_to_bytes
%xdefine _ec_GFp_mont_group_finish _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_group_finish
%xdefine _ec_GFp_mont_group_init _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_group_init
%xdefine _ec_GFp_mont_group_set_curve _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_group_set_curve
%xdefine _ec_GFp_mont_init_precomp _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_init_precomp
%xdefine _ec_GFp_mont_mul _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_mul
%xdefine _ec_GFp_mont_mul_base _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_base
%xdefine _ec_GFp_mont_mul_batch _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_batch
%xdefine _ec_GFp_mont_mul_precomp _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_precomp
%xdefine _ec_GFp_mont_mul_public _ %+ XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_public
%xdefine _ec_GFp_nistp_recode_scalar_bits _ %+ XCRYPTO_PREFIX %+ _ec_GFp_nistp_recode_scalar_bits
%xdefine _ec_GFp_simple_cmp_x_coordinate _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_cmp_x_coordinate
%xdefine _ec_GFp_simple_felem_from_bytes _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_felem_from_bytes
%xdefine _ec_GFp_simple_felem_to_bytes _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_felem_to_bytes
%xdefine _ec_GFp_simple_group_finish _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_group_finish
%xdefine _ec_GFp_simple_group_get_curve _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_group_get_curve
%xdefine _ec_GFp_simple_group_init _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_group_init
%xdefine _ec_GFp_simple_group_set_curve _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_group_set_curve
%xdefine _ec_GFp_simple_invert _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_invert
%xdefine _ec_GFp_simple_is_at_infinity _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_is_at_infinity
%xdefine _ec_GFp_simple_is_on_curve _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_is_on_curve
%xdefine _ec_GFp_simple_point_copy _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_point_copy
%xdefine _ec_GFp_simple_point_init _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_point_init
%xdefine _ec_GFp_simple_point_set_to_infinity _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_point_set_to_infinity
%xdefine _ec_GFp_simple_points_equal _ %+ XCRYPTO_PREFIX %+ _ec_GFp_simple_points_equal
%xdefine _ec_affine_jacobian_equal _ %+ XCRYPTO_PREFIX %+ _ec_affine_jacobian_equal
%xdefine _ec_affine_select _ %+ XCRYPTO_PREFIX %+ _ec_affine_select
%xdefine _ec_affine_to_jacobian _ %+ XCRYPTO_PREFIX %+ _ec_affine_to_jacobian
%xdefine _ec_asn1_meth _ %+ XCRYPTO_PREFIX %+ _ec_asn1_meth
%xdefine _ec_bignum_to_felem _ %+ XCRYPTO_PREFIX %+ _ec_bignum_to_felem
%xdefine _ec_bignum_to_scalar _ %+ XCRYPTO_PREFIX %+ _ec_bignum_to_scalar
%xdefine _ec_cmp_x_coordinate _ %+ XCRYPTO_PREFIX %+ _ec_cmp_x_coordinate
%xdefine _ec_compute_wNAF _ %+ XCRYPTO_PREFIX %+ _ec_compute_wNAF
%xdefine _ec_felem_add _ %+ XCRYPTO_PREFIX %+ _ec_felem_add
%xdefine _ec_felem_equal _ %+ XCRYPTO_PREFIX %+ _ec_felem_equal
%xdefine _ec_felem_from_bytes _ %+ XCRYPTO_PREFIX %+ _ec_felem_from_bytes
%xdefine _ec_felem_neg _ %+ XCRYPTO_PREFIX %+ _ec_felem_neg
%xdefine _ec_felem_non_zero_mask _ %+ XCRYPTO_PREFIX %+ _ec_felem_non_zero_mask
%xdefine _ec_felem_select _ %+ XCRYPTO_PREFIX %+ _ec_felem_select
%xdefine _ec_felem_sub _ %+ XCRYPTO_PREFIX %+ _ec_felem_sub
%xdefine _ec_felem_to_bignum _ %+ XCRYPTO_PREFIX %+ _ec_felem_to_bignum
%xdefine _ec_felem_to_bytes _ %+ XCRYPTO_PREFIX %+ _ec_felem_to_bytes
%xdefine _ec_get_x_coordinate_as_bytes _ %+ XCRYPTO_PREFIX %+ _ec_get_x_coordinate_as_bytes
%xdefine _ec_get_x_coordinate_as_scalar _ %+ XCRYPTO_PREFIX %+ _ec_get_x_coordinate_as_scalar
%xdefine _ec_group_new _ %+ XCRYPTO_PREFIX %+ _ec_group_new
%xdefine _ec_hash_to_curve_p384_xmd_sha512_sswu_draft07 _ %+ XCRYPTO_PREFIX %+ _ec_hash_to_curve_p384_xmd_sha512_sswu_draft07
%xdefine _ec_hash_to_curve_p521_xmd_sha512_sswu_draft06 _ %+ XCRYPTO_PREFIX %+ _ec_hash_to_curve_p521_xmd_sha512_sswu_draft06
%xdefine _ec_hash_to_scalar_p384_xmd_sha512_draft07 _ %+ XCRYPTO_PREFIX %+ _ec_hash_to_scalar_p384_xmd_sha512_draft07
%xdefine _ec_hash_to_scalar_p521_xmd_sha512_draft06 _ %+ XCRYPTO_PREFIX %+ _ec_hash_to_scalar_p521_xmd_sha512_draft06
%xdefine _ec_init_precomp _ %+ XCRYPTO_PREFIX %+ _ec_init_precomp
%xdefine _ec_jacobian_to_affine _ %+ XCRYPTO_PREFIX %+ _ec_jacobian_to_affine
%xdefine _ec_jacobian_to_affine_batch _ %+ XCRYPTO_PREFIX %+ _ec_jacobian_to_affine_batch
%xdefine _ec_pkey_meth _ %+ XCRYPTO_PREFIX %+ _ec_pkey_meth
%xdefine _ec_point_from_uncompressed _ %+ XCRYPTO_PREFIX %+ _ec_point_from_uncompressed
%xdefine _ec_point_mul_scalar _ %+ XCRYPTO_PREFIX %+ _ec_point_mul_scalar
%xdefine _ec_point_mul_scalar_base _ %+ XCRYPTO_PREFIX %+ _ec_point_mul_scalar_base
%xdefine _ec_point_mul_scalar_batch _ %+ XCRYPTO_PREFIX %+ _ec_point_mul_scalar_batch
%xdefine _ec_point_mul_scalar_precomp _ %+ XCRYPTO_PREFIX %+ _ec_point_mul_scalar_precomp
%xdefine _ec_point_mul_scalar_public _ %+ XCRYPTO_PREFIX %+ _ec_point_mul_scalar_public
%xdefine _ec_point_select _ %+ XCRYPTO_PREFIX %+ _ec_point_select
%xdefine _ec_point_set_affine_coordinates _ %+ XCRYPTO_PREFIX %+ _ec_point_set_affine_coordinates
%xdefine _ec_point_to_bytes _ %+ XCRYPTO_PREFIX %+ _ec_point_to_bytes
%xdefine _ec_precomp_select _ %+ XCRYPTO_PREFIX %+ _ec_precomp_select
%xdefine _ec_random_nonzero_scalar _ %+ XCRYPTO_PREFIX %+ _ec_random_nonzero_scalar
%xdefine _ec_scalar_add _ %+ XCRYPTO_PREFIX %+ _ec_scalar_add
%xdefine _ec_scalar_equal_vartime _ %+ XCRYPTO_PREFIX %+ _ec_scalar_equal_vartime
%xdefine _ec_scalar_from_bytes _ %+ XCRYPTO_PREFIX %+ _ec_scalar_from_bytes
%xdefine _ec_scalar_from_montgomery _ %+ XCRYPTO_PREFIX %+ _ec_scalar_from_montgomery
%xdefine _ec_scalar_inv0_montgomery _ %+ XCRYPTO_PREFIX %+ _ec_scalar_inv0_montgomery
%xdefine _ec_scalar_is_zero _ %+ XCRYPTO_PREFIX %+ _ec_scalar_is_zero
%xdefine _ec_scalar_mul_montgomery _ %+ XCRYPTO_PREFIX %+ _ec_scalar_mul_montgomery
%xdefine _ec_scalar_neg _ %+ XCRYPTO_PREFIX %+ _ec_scalar_neg
%xdefine _ec_scalar_reduce _ %+ XCRYPTO_PREFIX %+ _ec_scalar_reduce
%xdefine _ec_scalar_select _ %+ XCRYPTO_PREFIX %+ _ec_scalar_select
%xdefine _ec_scalar_sub _ %+ XCRYPTO_PREFIX %+ _ec_scalar_sub
%xdefine _ec_scalar_to_bytes _ %+ XCRYPTO_PREFIX %+ _ec_scalar_to_bytes
%xdefine _ec_scalar_to_montgomery _ %+ XCRYPTO_PREFIX %+ _ec_scalar_to_montgomery
%xdefine _ec_scalar_to_montgomery_inv_vartime _ %+ XCRYPTO_PREFIX %+ _ec_scalar_to_montgomery_inv_vartime
%xdefine _ec_set_to_safe_point _ %+ XCRYPTO_PREFIX %+ _ec_set_to_safe_point
%xdefine _ec_simple_scalar_inv0_montgomery _ %+ XCRYPTO_PREFIX %+ _ec_simple_scalar_inv0_montgomery
%xdefine _ec_simple_scalar_to_montgomery_inv_vartime _ %+ XCRYPTO_PREFIX %+ _ec_simple_scalar_to_montgomery_inv_vartime
%xdefine _ecp_nistz256_avx2_select_w7 _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_avx2_select_w7
%xdefine _ecp_nistz256_mul_mont _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_mul_mont
%xdefine _ecp_nistz256_neg _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_neg
%xdefine _ecp_nistz256_ord_mul_mont _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_ord_mul_mont
%xdefine _ecp_nistz256_ord_sqr_mont _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_ord_sqr_mont
%xdefine _ecp_nistz256_point_add _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_point_add
%xdefine _ecp_nistz256_point_add_affine _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_point_add_affine
%xdefine _ecp_nistz256_point_double _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_point_double
%xdefine _ecp_nistz256_select_w5 _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_select_w5
%xdefine _ecp_nistz256_select_w7 _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_select_w7
%xdefine _ecp_nistz256_sqr_mont _ %+ XCRYPTO_PREFIX %+ _ecp_nistz256_sqr_mont
%xdefine _ed25519_asn1_meth _ %+ XCRYPTO_PREFIX %+ _ed25519_asn1_meth
%xdefine _ed25519_pkey_meth _ %+ XCRYPTO_PREFIX %+ _ed25519_pkey_meth
%xdefine _gcm_ghash_avx _ %+ XCRYPTO_PREFIX %+ _gcm_ghash_avx
%xdefine _gcm_ghash_clmul _ %+ XCRYPTO_PREFIX %+ _gcm_ghash_clmul
%xdefine _gcm_ghash_neon _ %+ XCRYPTO_PREFIX %+ _gcm_ghash_neon
%xdefine _gcm_ghash_nohw _ %+ XCRYPTO_PREFIX %+ _gcm_ghash_nohw
%xdefine _gcm_ghash_ssse3 _ %+ XCRYPTO_PREFIX %+ _gcm_ghash_ssse3
%xdefine _gcm_ghash_v8 _ %+ XCRYPTO_PREFIX %+ _gcm_ghash_v8
%xdefine _gcm_gmult_avx _ %+ XCRYPTO_PREFIX %+ _gcm_gmult_avx
%xdefine _gcm_gmult_clmul _ %+ XCRYPTO_PREFIX %+ _gcm_gmult_clmul
%xdefine _gcm_gmult_neon _ %+ XCRYPTO_PREFIX %+ _gcm_gmult_neon
%xdefine _gcm_gmult_nohw _ %+ XCRYPTO_PREFIX %+ _gcm_gmult_nohw
%xdefine _gcm_gmult_ssse3 _ %+ XCRYPTO_PREFIX %+ _gcm_gmult_ssse3
%xdefine _gcm_gmult_v8 _ %+ XCRYPTO_PREFIX %+ _gcm_gmult_v8
%xdefine _gcm_init_avx _ %+ XCRYPTO_PREFIX %+ _gcm_init_avx
%xdefine _gcm_init_clmul _ %+ XCRYPTO_PREFIX %+ _gcm_init_clmul
%xdefine _gcm_init_neon _ %+ XCRYPTO_PREFIX %+ _gcm_init_neon
%xdefine _gcm_init_nohw _ %+ XCRYPTO_PREFIX %+ _gcm_init_nohw
%xdefine _gcm_init_ssse3 _ %+ XCRYPTO_PREFIX %+ _gcm_init_ssse3
%xdefine _gcm_init_v8 _ %+ XCRYPTO_PREFIX %+ _gcm_init_v8
%xdefine _i2a_ACCESS_DESCRIPTION _ %+ XCRYPTO_PREFIX %+ _i2a_ACCESS_DESCRIPTION
%xdefine _i2a_ASN1_ENUMERATED _ %+ XCRYPTO_PREFIX %+ _i2a_ASN1_ENUMERATED
%xdefine _i2a_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _i2a_ASN1_INTEGER
%xdefine _i2a_ASN1_OBJECT _ %+ XCRYPTO_PREFIX %+ _i2a_ASN1_OBJECT
%xdefine _i2a_ASN1_STRING _ %+ XCRYPTO_PREFIX %+ _i2a_ASN1_STRING
%xdefine _i2c_ASN1_BIT_STRING _ %+ XCRYPTO_PREFIX %+ _i2c_ASN1_BIT_STRING
%xdefine _i2c_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _i2c_ASN1_INTEGER
%xdefine _i2d_ACCESS_DESCRIPTION _ %+ XCRYPTO_PREFIX %+ _i2d_ACCESS_DESCRIPTION
%xdefine _i2d_ASN1_BIT_STRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_BIT_STRING
%xdefine _i2d_ASN1_BMPSTRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_BMPSTRING
%xdefine _i2d_ASN1_BOOLEAN _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_BOOLEAN
%xdefine _i2d_ASN1_ENUMERATED _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_ENUMERATED
%xdefine _i2d_ASN1_GENERALIZEDTIME _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_GENERALIZEDTIME
%xdefine _i2d_ASN1_GENERALSTRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_GENERALSTRING
%xdefine _i2d_ASN1_IA5STRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_IA5STRING
%xdefine _i2d_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_INTEGER
%xdefine _i2d_ASN1_NULL _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_NULL
%xdefine _i2d_ASN1_OBJECT _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_OBJECT
%xdefine _i2d_ASN1_OCTET_STRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_OCTET_STRING
%xdefine _i2d_ASN1_PRINTABLE _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_PRINTABLE
%xdefine _i2d_ASN1_PRINTABLESTRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_PRINTABLESTRING
%xdefine _i2d_ASN1_SEQUENCE_ANY _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_SEQUENCE_ANY
%xdefine _i2d_ASN1_SET_ANY _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_SET_ANY
%xdefine _i2d_ASN1_T61STRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_T61STRING
%xdefine _i2d_ASN1_TIME _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_TIME
%xdefine _i2d_ASN1_TYPE _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_TYPE
%xdefine _i2d_ASN1_UNIVERSALSTRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_UNIVERSALSTRING
%xdefine _i2d_ASN1_UTCTIME _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_UTCTIME
%xdefine _i2d_ASN1_UTF8STRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_UTF8STRING
%xdefine _i2d_ASN1_VISIBLESTRING _ %+ XCRYPTO_PREFIX %+ _i2d_ASN1_VISIBLESTRING
%xdefine _i2d_AUTHORITY_INFO_ACCESS _ %+ XCRYPTO_PREFIX %+ _i2d_AUTHORITY_INFO_ACCESS
%xdefine _i2d_AUTHORITY_KEYID _ %+ XCRYPTO_PREFIX %+ _i2d_AUTHORITY_KEYID
%xdefine _i2d_BASIC_CONSTRAINTS _ %+ XCRYPTO_PREFIX %+ _i2d_BASIC_CONSTRAINTS
%xdefine _i2d_CERTIFICATEPOLICIES _ %+ XCRYPTO_PREFIX %+ _i2d_CERTIFICATEPOLICIES
%xdefine _i2d_CRL_DIST_POINTS _ %+ XCRYPTO_PREFIX %+ _i2d_CRL_DIST_POINTS
%xdefine _i2d_DHparams _ %+ XCRYPTO_PREFIX %+ _i2d_DHparams
%xdefine _i2d_DHparams_bio _ %+ XCRYPTO_PREFIX %+ _i2d_DHparams_bio
%xdefine _i2d_DIRECTORYSTRING _ %+ XCRYPTO_PREFIX %+ _i2d_DIRECTORYSTRING
%xdefine _i2d_DISPLAYTEXT _ %+ XCRYPTO_PREFIX %+ _i2d_DISPLAYTEXT
%xdefine _i2d_DIST_POINT _ %+ XCRYPTO_PREFIX %+ _i2d_DIST_POINT
%xdefine _i2d_DIST_POINT_NAME _ %+ XCRYPTO_PREFIX %+ _i2d_DIST_POINT_NAME
%xdefine _i2d_DSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _i2d_DSAPrivateKey
%xdefine _i2d_DSAPrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _i2d_DSAPrivateKey_bio
%xdefine _i2d_DSAPrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _i2d_DSAPrivateKey_fp
%xdefine _i2d_DSAPublicKey _ %+ XCRYPTO_PREFIX %+ _i2d_DSAPublicKey
%xdefine _i2d_DSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _i2d_DSA_PUBKEY
%xdefine _i2d_DSA_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _i2d_DSA_PUBKEY_bio
%xdefine _i2d_DSA_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _i2d_DSA_PUBKEY_fp
%xdefine _i2d_DSA_SIG _ %+ XCRYPTO_PREFIX %+ _i2d_DSA_SIG
%xdefine _i2d_DSAparams _ %+ XCRYPTO_PREFIX %+ _i2d_DSAparams
%xdefine _i2d_ECDSA_SIG _ %+ XCRYPTO_PREFIX %+ _i2d_ECDSA_SIG
%xdefine _i2d_ECParameters _ %+ XCRYPTO_PREFIX %+ _i2d_ECParameters
%xdefine _i2d_ECPrivateKey _ %+ XCRYPTO_PREFIX %+ _i2d_ECPrivateKey
%xdefine _i2d_ECPrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _i2d_ECPrivateKey_bio
%xdefine _i2d_ECPrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _i2d_ECPrivateKey_fp
%xdefine _i2d_EC_PUBKEY _ %+ XCRYPTO_PREFIX %+ _i2d_EC_PUBKEY
%xdefine _i2d_EC_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _i2d_EC_PUBKEY_bio
%xdefine _i2d_EC_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _i2d_EC_PUBKEY_fp
%xdefine _i2d_EDIPARTYNAME _ %+ XCRYPTO_PREFIX %+ _i2d_EDIPARTYNAME
%xdefine _i2d_EXTENDED_KEY_USAGE _ %+ XCRYPTO_PREFIX %+ _i2d_EXTENDED_KEY_USAGE
%xdefine _i2d_GENERAL_NAME _ %+ XCRYPTO_PREFIX %+ _i2d_GENERAL_NAME
%xdefine _i2d_GENERAL_NAMES _ %+ XCRYPTO_PREFIX %+ _i2d_GENERAL_NAMES
%xdefine _i2d_ISSUING_DIST_POINT _ %+ XCRYPTO_PREFIX %+ _i2d_ISSUING_DIST_POINT
%xdefine _i2d_NETSCAPE_SPKAC _ %+ XCRYPTO_PREFIX %+ _i2d_NETSCAPE_SPKAC
%xdefine _i2d_NETSCAPE_SPKI _ %+ XCRYPTO_PREFIX %+ _i2d_NETSCAPE_SPKI
%xdefine _i2d_NOTICEREF _ %+ XCRYPTO_PREFIX %+ _i2d_NOTICEREF
%xdefine _i2d_OTHERNAME _ %+ XCRYPTO_PREFIX %+ _i2d_OTHERNAME
%xdefine _i2d_PKCS12 _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS12
%xdefine _i2d_PKCS12_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS12_bio
%xdefine _i2d_PKCS12_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS12_fp
%xdefine _i2d_PKCS7 _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS7
%xdefine _i2d_PKCS7_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS7_bio
%xdefine _i2d_PKCS8PrivateKeyInfo_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKeyInfo_bio
%xdefine _i2d_PKCS8PrivateKeyInfo_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKeyInfo_fp
%xdefine _i2d_PKCS8PrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_bio
%xdefine _i2d_PKCS8PrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_fp
%xdefine _i2d_PKCS8PrivateKey_nid_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_nid_bio
%xdefine _i2d_PKCS8PrivateKey_nid_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_nid_fp
%xdefine _i2d_PKCS8_PRIV_KEY_INFO _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8_PRIV_KEY_INFO
%xdefine _i2d_PKCS8_PRIV_KEY_INFO_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8_PRIV_KEY_INFO_bio
%xdefine _i2d_PKCS8_PRIV_KEY_INFO_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8_PRIV_KEY_INFO_fp
%xdefine _i2d_PKCS8_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8_bio
%xdefine _i2d_PKCS8_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PKCS8_fp
%xdefine _i2d_PKEY_USAGE_PERIOD _ %+ XCRYPTO_PREFIX %+ _i2d_PKEY_USAGE_PERIOD
%xdefine _i2d_POLICYINFO _ %+ XCRYPTO_PREFIX %+ _i2d_POLICYINFO
%xdefine _i2d_POLICYQUALINFO _ %+ XCRYPTO_PREFIX %+ _i2d_POLICYQUALINFO
%xdefine _i2d_PROXY_CERT_INFO_EXTENSION _ %+ XCRYPTO_PREFIX %+ _i2d_PROXY_CERT_INFO_EXTENSION
%xdefine _i2d_PROXY_POLICY _ %+ XCRYPTO_PREFIX %+ _i2d_PROXY_POLICY
%xdefine _i2d_PUBKEY _ %+ XCRYPTO_PREFIX %+ _i2d_PUBKEY
%xdefine _i2d_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PUBKEY_bio
%xdefine _i2d_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PUBKEY_fp
%xdefine _i2d_PrivateKey _ %+ XCRYPTO_PREFIX %+ _i2d_PrivateKey
%xdefine _i2d_PrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _i2d_PrivateKey_bio
%xdefine _i2d_PrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _i2d_PrivateKey_fp
%xdefine _i2d_PublicKey _ %+ XCRYPTO_PREFIX %+ _i2d_PublicKey
%xdefine _i2d_RSAPrivateKey _ %+ XCRYPTO_PREFIX %+ _i2d_RSAPrivateKey
%xdefine _i2d_RSAPrivateKey_bio _ %+ XCRYPTO_PREFIX %+ _i2d_RSAPrivateKey_bio
%xdefine _i2d_RSAPrivateKey_fp _ %+ XCRYPTO_PREFIX %+ _i2d_RSAPrivateKey_fp
%xdefine _i2d_RSAPublicKey _ %+ XCRYPTO_PREFIX %+ _i2d_RSAPublicKey
%xdefine _i2d_RSAPublicKey_bio _ %+ XCRYPTO_PREFIX %+ _i2d_RSAPublicKey_bio
%xdefine _i2d_RSAPublicKey_fp _ %+ XCRYPTO_PREFIX %+ _i2d_RSAPublicKey_fp
%xdefine _i2d_RSA_PSS_PARAMS _ %+ XCRYPTO_PREFIX %+ _i2d_RSA_PSS_PARAMS
%xdefine _i2d_RSA_PUBKEY _ %+ XCRYPTO_PREFIX %+ _i2d_RSA_PUBKEY
%xdefine _i2d_RSA_PUBKEY_bio _ %+ XCRYPTO_PREFIX %+ _i2d_RSA_PUBKEY_bio
%xdefine _i2d_RSA_PUBKEY_fp _ %+ XCRYPTO_PREFIX %+ _i2d_RSA_PUBKEY_fp
%xdefine _i2d_SSL_SESSION _ %+ XCRYPTO_PREFIX %+ _i2d_SSL_SESSION
%xdefine _i2d_SSL_SESSION_bio _ %+ XCRYPTO_PREFIX %+ _i2d_SSL_SESSION_bio
%xdefine _i2d_SXNET _ %+ XCRYPTO_PREFIX %+ _i2d_SXNET
%xdefine _i2d_SXNETID _ %+ XCRYPTO_PREFIX %+ _i2d_SXNETID
%xdefine _i2d_USERNOTICE _ %+ XCRYPTO_PREFIX %+ _i2d_USERNOTICE
%xdefine _i2d_X509 _ %+ XCRYPTO_PREFIX %+ _i2d_X509
%xdefine _i2d_X509_ALGOR _ %+ XCRYPTO_PREFIX %+ _i2d_X509_ALGOR
%xdefine _i2d_X509_ALGORS _ %+ XCRYPTO_PREFIX %+ _i2d_X509_ALGORS
%xdefine _i2d_X509_ATTRIBUTE _ %+ XCRYPTO_PREFIX %+ _i2d_X509_ATTRIBUTE
%xdefine _i2d_X509_AUX _ %+ XCRYPTO_PREFIX %+ _i2d_X509_AUX
%xdefine _i2d_X509_CERT_AUX _ %+ XCRYPTO_PREFIX %+ _i2d_X509_CERT_AUX
%xdefine _i2d_X509_CINF _ %+ XCRYPTO_PREFIX %+ _i2d_X509_CINF
%xdefine _i2d_X509_CRL _ %+ XCRYPTO_PREFIX %+ _i2d_X509_CRL
%xdefine _i2d_X509_CRL_INFO _ %+ XCRYPTO_PREFIX %+ _i2d_X509_CRL_INFO
%xdefine _i2d_X509_CRL_bio _ %+ XCRYPTO_PREFIX %+ _i2d_X509_CRL_bio
%xdefine _i2d_X509_CRL_fp _ %+ XCRYPTO_PREFIX %+ _i2d_X509_CRL_fp
%xdefine _i2d_X509_EXTENSION _ %+ XCRYPTO_PREFIX %+ _i2d_X509_EXTENSION
%xdefine _i2d_X509_EXTENSIONS _ %+ XCRYPTO_PREFIX %+ _i2d_X509_EXTENSIONS
%xdefine _i2d_X509_NAME _ %+ XCRYPTO_PREFIX %+ _i2d_X509_NAME
%xdefine _i2d_X509_NAME_ENTRY _ %+ XCRYPTO_PREFIX %+ _i2d_X509_NAME_ENTRY
%xdefine _i2d_X509_PUBKEY _ %+ XCRYPTO_PREFIX %+ _i2d_X509_PUBKEY
%xdefine _i2d_X509_REQ _ %+ XCRYPTO_PREFIX %+ _i2d_X509_REQ
%xdefine _i2d_X509_REQ_INFO _ %+ XCRYPTO_PREFIX %+ _i2d_X509_REQ_INFO
%xdefine _i2d_X509_REQ_bio _ %+ XCRYPTO_PREFIX %+ _i2d_X509_REQ_bio
%xdefine _i2d_X509_REQ_fp _ %+ XCRYPTO_PREFIX %+ _i2d_X509_REQ_fp
%xdefine _i2d_X509_REVOKED _ %+ XCRYPTO_PREFIX %+ _i2d_X509_REVOKED
%xdefine _i2d_X509_SIG _ %+ XCRYPTO_PREFIX %+ _i2d_X509_SIG
%xdefine _i2d_X509_VAL _ %+ XCRYPTO_PREFIX %+ _i2d_X509_VAL
%xdefine _i2d_X509_bio _ %+ XCRYPTO_PREFIX %+ _i2d_X509_bio
%xdefine _i2d_X509_fp _ %+ XCRYPTO_PREFIX %+ _i2d_X509_fp
%xdefine _i2d_re_X509_CRL_tbs _ %+ XCRYPTO_PREFIX %+ _i2d_re_X509_CRL_tbs
%xdefine _i2d_re_X509_REQ_tbs _ %+ XCRYPTO_PREFIX %+ _i2d_re_X509_REQ_tbs
%xdefine _i2d_re_X509_tbs _ %+ XCRYPTO_PREFIX %+ _i2d_re_X509_tbs
%xdefine _i2o_ECPublicKey _ %+ XCRYPTO_PREFIX %+ _i2o_ECPublicKey
%xdefine _i2s_ASN1_ENUMERATED _ %+ XCRYPTO_PREFIX %+ _i2s_ASN1_ENUMERATED
%xdefine _i2s_ASN1_ENUMERATED_TABLE _ %+ XCRYPTO_PREFIX %+ _i2s_ASN1_ENUMERATED_TABLE
%xdefine _i2s_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _i2s_ASN1_INTEGER
%xdefine _i2s_ASN1_OCTET_STRING _ %+ XCRYPTO_PREFIX %+ _i2s_ASN1_OCTET_STRING
%xdefine _i2t_ASN1_OBJECT _ %+ XCRYPTO_PREFIX %+ _i2t_ASN1_OBJECT
%xdefine _i2v_ASN1_BIT_STRING _ %+ XCRYPTO_PREFIX %+ _i2v_ASN1_BIT_STRING
%xdefine _i2v_GENERAL_NAME _ %+ XCRYPTO_PREFIX %+ _i2v_GENERAL_NAME
%xdefine _i2v_GENERAL_NAMES _ %+ XCRYPTO_PREFIX %+ _i2v_GENERAL_NAMES
%xdefine _kBoringSSLRSASqrtTwo _ %+ XCRYPTO_PREFIX %+ _kBoringSSLRSASqrtTwo
%xdefine _kBoringSSLRSASqrtTwoLen _ %+ XCRYPTO_PREFIX %+ _kBoringSSLRSASqrtTwoLen
%xdefine _kOpenSSLReasonStringData _ %+ XCRYPTO_PREFIX %+ _kOpenSSLReasonStringData
%xdefine _kOpenSSLReasonValues _ %+ XCRYPTO_PREFIX %+ _kOpenSSLReasonValues
%xdefine _kOpenSSLReasonValuesLen _ %+ XCRYPTO_PREFIX %+ _kOpenSSLReasonValuesLen
%xdefine _level_add_node _ %+ XCRYPTO_PREFIX %+ _level_add_node
%xdefine _level_find_node _ %+ XCRYPTO_PREFIX %+ _level_find_node
%xdefine _lh_delete _ %+ XCRYPTO_PREFIX %+ _lh_delete
%xdefine _lh_doall_arg _ %+ XCRYPTO_PREFIX %+ _lh_doall_arg
%xdefine _lh_free _ %+ XCRYPTO_PREFIX %+ _lh_free
%xdefine _lh_insert _ %+ XCRYPTO_PREFIX %+ _lh_insert
%xdefine _lh_new _ %+ XCRYPTO_PREFIX %+ _lh_new
%xdefine _lh_num_items _ %+ XCRYPTO_PREFIX %+ _lh_num_items
%xdefine _lh_retrieve _ %+ XCRYPTO_PREFIX %+ _lh_retrieve
%xdefine _lh_retrieve_key _ %+ XCRYPTO_PREFIX %+ _lh_retrieve_key
%xdefine _lh_strhash _ %+ XCRYPTO_PREFIX %+ _lh_strhash
%xdefine _md4_block_data_order _ %+ XCRYPTO_PREFIX %+ _md4_block_data_order
%xdefine _md5_block_asm_data_order _ %+ XCRYPTO_PREFIX %+ _md5_block_asm_data_order
%xdefine _o2i_ECPublicKey _ %+ XCRYPTO_PREFIX %+ _o2i_ECPublicKey
%xdefine _pkcs12_iterations_acceptable _ %+ XCRYPTO_PREFIX %+ _pkcs12_iterations_acceptable
%xdefine _pkcs12_key_gen _ %+ XCRYPTO_PREFIX %+ _pkcs12_key_gen
%xdefine _pkcs12_pbe_encrypt_init _ %+ XCRYPTO_PREFIX %+ _pkcs12_pbe_encrypt_init
%xdefine _pkcs7_bundle _ %+ XCRYPTO_PREFIX %+ _pkcs7_bundle
%xdefine _pkcs7_parse_header _ %+ XCRYPTO_PREFIX %+ _pkcs7_parse_header
%xdefine _pkcs8_pbe_decrypt _ %+ XCRYPTO_PREFIX %+ _pkcs8_pbe_decrypt
%xdefine _pmbtoken_exp0_blind _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_blind
%xdefine _pmbtoken_exp0_client_key_from_bytes _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_client_key_from_bytes
%xdefine _pmbtoken_exp0_generate_key _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_generate_key
%xdefine _pmbtoken_exp0_issuer_key_from_bytes _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_issuer_key_from_bytes
%xdefine _pmbtoken_exp0_read _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_read
%xdefine _pmbtoken_exp0_sign _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_sign
%xdefine _pmbtoken_exp0_unblind _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp0_unblind
%xdefine _pmbtoken_exp1_blind _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_blind
%xdefine _pmbtoken_exp1_client_key_from_bytes _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_client_key_from_bytes
%xdefine _pmbtoken_exp1_generate_key _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_generate_key
%xdefine _pmbtoken_exp1_get_h_for_testing _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_get_h_for_testing
%xdefine _pmbtoken_exp1_issuer_key_from_bytes _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_issuer_key_from_bytes
%xdefine _pmbtoken_exp1_read _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_read
%xdefine _pmbtoken_exp1_sign _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_sign
%xdefine _pmbtoken_exp1_unblind _ %+ XCRYPTO_PREFIX %+ _pmbtoken_exp1_unblind
%xdefine _policy_cache_find_data _ %+ XCRYPTO_PREFIX %+ _policy_cache_find_data
%xdefine _policy_cache_free _ %+ XCRYPTO_PREFIX %+ _policy_cache_free
%xdefine _policy_cache_set _ %+ XCRYPTO_PREFIX %+ _policy_cache_set
%xdefine _policy_cache_set_mapping _ %+ XCRYPTO_PREFIX %+ _policy_cache_set_mapping
%xdefine _policy_data_free _ %+ XCRYPTO_PREFIX %+ _policy_data_free
%xdefine _policy_data_new _ %+ XCRYPTO_PREFIX %+ _policy_data_new
%xdefine _policy_node_cmp_new _ %+ XCRYPTO_PREFIX %+ _policy_node_cmp_new
%xdefine _policy_node_free _ %+ XCRYPTO_PREFIX %+ _policy_node_free
%xdefine _policy_node_match _ %+ XCRYPTO_PREFIX %+ _policy_node_match
%xdefine _poly_Rq_mul _ %+ XCRYPTO_PREFIX %+ _poly_Rq_mul
%xdefine _rand_fork_unsafe_buffering_enabled _ %+ XCRYPTO_PREFIX %+ _rand_fork_unsafe_buffering_enabled
%xdefine _rsa_asn1_meth _ %+ XCRYPTO_PREFIX %+ _rsa_asn1_meth
%xdefine _rsa_default_decrypt _ %+ XCRYPTO_PREFIX %+ _rsa_default_decrypt
%xdefine _rsa_default_private_transform _ %+ XCRYPTO_PREFIX %+ _rsa_default_private_transform
%xdefine _rsa_default_sign_raw _ %+ XCRYPTO_PREFIX %+ _rsa_default_sign_raw
%xdefine _rsa_default_size _ %+ XCRYPTO_PREFIX %+ _rsa_default_size
%xdefine _rsa_pkey_meth _ %+ XCRYPTO_PREFIX %+ _rsa_pkey_meth
%xdefine _rsaz_1024_gather5_avx2 _ %+ XCRYPTO_PREFIX %+ _rsaz_1024_gather5_avx2
%xdefine _rsaz_1024_mul_avx2 _ %+ XCRYPTO_PREFIX %+ _rsaz_1024_mul_avx2
%xdefine _rsaz_1024_norm2red_avx2 _ %+ XCRYPTO_PREFIX %+ _rsaz_1024_norm2red_avx2
%xdefine _rsaz_1024_red2norm_avx2 _ %+ XCRYPTO_PREFIX %+ _rsaz_1024_red2norm_avx2
%xdefine _rsaz_1024_scatter5_avx2 _ %+ XCRYPTO_PREFIX %+ _rsaz_1024_scatter5_avx2
%xdefine _rsaz_1024_sqr_avx2 _ %+ XCRYPTO_PREFIX %+ _rsaz_1024_sqr_avx2
%xdefine _s2i_ASN1_INTEGER _ %+ XCRYPTO_PREFIX %+ _s2i_ASN1_INTEGER
%xdefine _s2i_ASN1_OCTET_STRING _ %+ XCRYPTO_PREFIX %+ _s2i_ASN1_OCTET_STRING
%xdefine _sha1_block_data_order _ %+ XCRYPTO_PREFIX %+ _sha1_block_data_order
%xdefine _sha256_block_data_order _ %+ XCRYPTO_PREFIX %+ _sha256_block_data_order
%xdefine _sha512_block_data_order _ %+ XCRYPTO_PREFIX %+ _sha512_block_data_order
%xdefine _sk_CRYPTO_BUFFER_call_copy_func _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_call_copy_func
%xdefine _sk_CRYPTO_BUFFER_call_free_func _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_call_free_func
%xdefine _sk_CRYPTO_BUFFER_deep_copy _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_deep_copy
%xdefine _sk_CRYPTO_BUFFER_new_null _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_new_null
%xdefine _sk_CRYPTO_BUFFER_num _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_num
%xdefine _sk_CRYPTO_BUFFER_push _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_push
%xdefine _sk_CRYPTO_BUFFER_set _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_set
%xdefine _sk_CRYPTO_BUFFER_value _ %+ XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_value
%xdefine _sk_SRTP_PROTECTION_PROFILE_new_null _ %+ XCRYPTO_PREFIX %+ _sk_SRTP_PROTECTION_PROFILE_new_null
%xdefine _sk_SRTP_PROTECTION_PROFILE_num _ %+ XCRYPTO_PREFIX %+ _sk_SRTP_PROTECTION_PROFILE_num
%xdefine _sk_SRTP_PROTECTION_PROFILE_push _ %+ XCRYPTO_PREFIX %+ _sk_SRTP_PROTECTION_PROFILE_push
%xdefine _sk_SSL_CIPHER_call_cmp_func _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_call_cmp_func
%xdefine _sk_SSL_CIPHER_delete _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_delete
%xdefine _sk_SSL_CIPHER_dup _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_dup
%xdefine _sk_SSL_CIPHER_find _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_find
%xdefine _sk_SSL_CIPHER_new_null _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_new_null
%xdefine _sk_SSL_CIPHER_num _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_num
%xdefine _sk_SSL_CIPHER_push _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_push
%xdefine _sk_SSL_CIPHER_value _ %+ XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_value
%xdefine _sk_X509_NAME_call_cmp_func _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_call_cmp_func
%xdefine _sk_X509_NAME_call_copy_func _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_call_copy_func
%xdefine _sk_X509_NAME_call_free_func _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_call_free_func
%xdefine _sk_X509_NAME_deep_copy _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_deep_copy
%xdefine _sk_X509_NAME_find _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_find
%xdefine _sk_X509_NAME_free _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_free
%xdefine _sk_X509_NAME_new _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_new
%xdefine _sk_X509_NAME_new_null _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_new_null
%xdefine _sk_X509_NAME_pop_free _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_pop_free
%xdefine _sk_X509_NAME_push _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_push
%xdefine _sk_X509_NAME_set_cmp_func _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_set_cmp_func
%xdefine _sk_X509_NAME_sort _ %+ XCRYPTO_PREFIX %+ _sk_X509_NAME_sort
%xdefine _sk_X509_call_free_func _ %+ XCRYPTO_PREFIX %+ _sk_X509_call_free_func
%xdefine _sk_X509_new_null _ %+ XCRYPTO_PREFIX %+ _sk_X509_new_null
%xdefine _sk_X509_num _ %+ XCRYPTO_PREFIX %+ _sk_X509_num
%xdefine _sk_X509_pop_free _ %+ XCRYPTO_PREFIX %+ _sk_X509_pop_free
%xdefine _sk_X509_shift _ %+ XCRYPTO_PREFIX %+ _sk_X509_shift
%xdefine _sk_X509_value _ %+ XCRYPTO_PREFIX %+ _sk_X509_value
%xdefine _sk_deep_copy _ %+ XCRYPTO_PREFIX %+ _sk_deep_copy
%xdefine _sk_delete _ %+ XCRYPTO_PREFIX %+ _sk_delete
%xdefine _sk_delete_ptr _ %+ XCRYPTO_PREFIX %+ _sk_delete_ptr
%xdefine _sk_dup _ %+ XCRYPTO_PREFIX %+ _sk_dup
%xdefine _sk_find _ %+ XCRYPTO_PREFIX %+ _sk_find
%xdefine _sk_free _ %+ XCRYPTO_PREFIX %+ _sk_free
%xdefine _sk_insert _ %+ XCRYPTO_PREFIX %+ _sk_insert
%xdefine _sk_is_sorted _ %+ XCRYPTO_PREFIX %+ _sk_is_sorted
%xdefine _sk_new _ %+ XCRYPTO_PREFIX %+ _sk_new
%xdefine _sk_new_null _ %+ XCRYPTO_PREFIX %+ _sk_new_null
%xdefine _sk_num _ %+ XCRYPTO_PREFIX %+ _sk_num
%xdefine _sk_pop _ %+ XCRYPTO_PREFIX %+ _sk_pop
%xdefine _sk_pop_free _ %+ XCRYPTO_PREFIX %+ _sk_pop_free
%xdefine _sk_pop_free_ex _ %+ XCRYPTO_PREFIX %+ _sk_pop_free_ex
%xdefine _sk_push _ %+ XCRYPTO_PREFIX %+ _sk_push
%xdefine _sk_set _ %+ XCRYPTO_PREFIX %+ _sk_set
%xdefine _sk_set_cmp_func _ %+ XCRYPTO_PREFIX %+ _sk_set_cmp_func
%xdefine _sk_shift _ %+ XCRYPTO_PREFIX %+ _sk_shift
%xdefine _sk_sort _ %+ XCRYPTO_PREFIX %+ _sk_sort
%xdefine _sk_value _ %+ XCRYPTO_PREFIX %+ _sk_value
%xdefine _sk_zero _ %+ XCRYPTO_PREFIX %+ _sk_zero
%xdefine _tree_find_sk _ %+ XCRYPTO_PREFIX %+ _tree_find_sk
%xdefine _v2i_ASN1_BIT_STRING _ %+ XCRYPTO_PREFIX %+ _v2i_ASN1_BIT_STRING
%xdefine _v2i_GENERAL_NAME _ %+ XCRYPTO_PREFIX %+ _v2i_GENERAL_NAME
%xdefine _v2i_GENERAL_NAMES _ %+ XCRYPTO_PREFIX %+ _v2i_GENERAL_NAMES
%xdefine _v2i_GENERAL_NAME_ex _ %+ XCRYPTO_PREFIX %+ _v2i_GENERAL_NAME_ex
%xdefine _v3_akey_id _ %+ XCRYPTO_PREFIX %+ _v3_akey_id
%xdefine _v3_alt _ %+ XCRYPTO_PREFIX %+ _v3_alt
%xdefine _v3_bcons _ %+ XCRYPTO_PREFIX %+ _v3_bcons
%xdefine _v3_cpols _ %+ XCRYPTO_PREFIX %+ _v3_cpols
%xdefine _v3_crl_invdate _ %+ XCRYPTO_PREFIX %+ _v3_crl_invdate
%xdefine _v3_crl_num _ %+ XCRYPTO_PREFIX %+ _v3_crl_num
%xdefine _v3_crl_reason _ %+ XCRYPTO_PREFIX %+ _v3_crl_reason
%xdefine _v3_crld _ %+ XCRYPTO_PREFIX %+ _v3_crld
%xdefine _v3_delta_crl _ %+ XCRYPTO_PREFIX %+ _v3_delta_crl
%xdefine _v3_ext_ku _ %+ XCRYPTO_PREFIX %+ _v3_ext_ku
%xdefine _v3_freshest_crl _ %+ XCRYPTO_PREFIX %+ _v3_freshest_crl
%xdefine _v3_idp _ %+ XCRYPTO_PREFIX %+ _v3_idp
%xdefine _v3_info _ %+ XCRYPTO_PREFIX %+ _v3_info
%xdefine _v3_inhibit_anyp _ %+ XCRYPTO_PREFIX %+ _v3_inhibit_anyp
%xdefine _v3_key_usage _ %+ XCRYPTO_PREFIX %+ _v3_key_usage
%xdefine _v3_name_constraints _ %+ XCRYPTO_PREFIX %+ _v3_name_constraints
%xdefine _v3_ns_ia5_list _ %+ XCRYPTO_PREFIX %+ _v3_ns_ia5_list
%xdefine _v3_nscert _ %+ XCRYPTO_PREFIX %+ _v3_nscert
%xdefine _v3_ocsp_accresp _ %+ XCRYPTO_PREFIX %+ _v3_ocsp_accresp
%xdefine _v3_ocsp_nocheck _ %+ XCRYPTO_PREFIX %+ _v3_ocsp_nocheck
%xdefine _v3_pci _ %+ XCRYPTO_PREFIX %+ _v3_pci
%xdefine _v3_pkey_usage_period _ %+ XCRYPTO_PREFIX %+ _v3_pkey_usage_period
%xdefine _v3_policy_constraints _ %+ XCRYPTO_PREFIX %+ _v3_policy_constraints
%xdefine _v3_policy_mappings _ %+ XCRYPTO_PREFIX %+ _v3_policy_mappings
%xdefine _v3_sinfo _ %+ XCRYPTO_PREFIX %+ _v3_sinfo
%xdefine _v3_skey_id _ %+ XCRYPTO_PREFIX %+ _v3_skey_id
%xdefine _v3_sxnet _ %+ XCRYPTO_PREFIX %+ _v3_sxnet
%xdefine _vpaes_cbc_encrypt _ %+ XCRYPTO_PREFIX %+ _vpaes_cbc_encrypt
%xdefine _vpaes_ctr32_encrypt_blocks _ %+ XCRYPTO_PREFIX %+ _vpaes_ctr32_encrypt_blocks
%xdefine _vpaes_decrypt _ %+ XCRYPTO_PREFIX %+ _vpaes_decrypt
%xdefine _vpaes_encrypt _ %+ XCRYPTO_PREFIX %+ _vpaes_encrypt
%xdefine _vpaes_set_decrypt_key _ %+ XCRYPTO_PREFIX %+ _vpaes_set_decrypt_key
%xdefine _vpaes_set_encrypt_key _ %+ XCRYPTO_PREFIX %+ _vpaes_set_encrypt_key
%xdefine _x25519_asn1_meth _ %+ XCRYPTO_PREFIX %+ _x25519_asn1_meth
%xdefine _x25519_ge_add _ %+ XCRYPTO_PREFIX %+ _x25519_ge_add
%xdefine _x25519_ge_frombytes_vartime _ %+ XCRYPTO_PREFIX %+ _x25519_ge_frombytes_vartime
%xdefine _x25519_ge_p1p1_to_p2 _ %+ XCRYPTO_PREFIX %+ _x25519_ge_p1p1_to_p2
%xdefine _x25519_ge_p1p1_to_p3 _ %+ XCRYPTO_PREFIX %+ _x25519_ge_p1p1_to_p3
%xdefine _x25519_ge_p3_to_cached _ %+ XCRYPTO_PREFIX %+ _x25519_ge_p3_to_cached
%xdefine _x25519_ge_scalarmult _ %+ XCRYPTO_PREFIX %+ _x25519_ge_scalarmult
%xdefine _x25519_ge_scalarmult_base _ %+ XCRYPTO_PREFIX %+ _x25519_ge_scalarmult_base
%xdefine _x25519_ge_scalarmult_small_precomp _ %+ XCRYPTO_PREFIX %+ _x25519_ge_scalarmult_small_precomp
%xdefine _x25519_ge_sub _ %+ XCRYPTO_PREFIX %+ _x25519_ge_sub
%xdefine _x25519_ge_tobytes _ %+ XCRYPTO_PREFIX %+ _x25519_ge_tobytes
%xdefine _x25519_pkey_meth _ %+ XCRYPTO_PREFIX %+ _x25519_pkey_meth
%xdefine _x25519_sc_reduce _ %+ XCRYPTO_PREFIX %+ _x25519_sc_reduce
%xdefine _x509_digest_sign_algorithm _ %+ XCRYPTO_PREFIX %+ _x509_digest_sign_algorithm
%xdefine _x509_digest_verify_init _ %+ XCRYPTO_PREFIX %+ _x509_digest_verify_init
%xdefine _x509_print_rsa_pss_params _ %+ XCRYPTO_PREFIX %+ _x509_print_rsa_pss_params
%xdefine _x509_rsa_ctx_to_pss _ %+ XCRYPTO_PREFIX %+ _x509_rsa_ctx_to_pss
%xdefine _x509_rsa_pss_to_ctx _ %+ XCRYPTO_PREFIX %+ _x509_rsa_pss_to_ctx
%xdefine _x509v3_bytes_to_hex _ %+ XCRYPTO_PREFIX %+ _x509v3_bytes_to_hex
%xdefine _x509v3_hex_to_bytes _ %+ XCRYPTO_PREFIX %+ _x509v3_hex_to_bytes
%xdefine _x509v3_looks_like_dns_name _ %+ XCRYPTO_PREFIX %+ _x509v3_looks_like_dns_name
%xdefine _x509v3_name_cmp _ %+ XCRYPTO_PREFIX %+ _x509v3_name_cmp
%else
%xdefine ACCESS_DESCRIPTION_free XCRYPTO_PREFIX %+ _ACCESS_DESCRIPTION_free
%xdefine ACCESS_DESCRIPTION_it XCRYPTO_PREFIX %+ _ACCESS_DESCRIPTION_it
%xdefine ACCESS_DESCRIPTION_new XCRYPTO_PREFIX %+ _ACCESS_DESCRIPTION_new
%xdefine AES_CMAC XCRYPTO_PREFIX %+ _AES_CMAC
%xdefine AES_cbc_encrypt XCRYPTO_PREFIX %+ _AES_cbc_encrypt
%xdefine AES_cfb128_encrypt XCRYPTO_PREFIX %+ _AES_cfb128_encrypt
%xdefine AES_ctr128_encrypt XCRYPTO_PREFIX %+ _AES_ctr128_encrypt
%xdefine AES_decrypt XCRYPTO_PREFIX %+ _AES_decrypt
%xdefine AES_ecb_encrypt XCRYPTO_PREFIX %+ _AES_ecb_encrypt
%xdefine AES_encrypt XCRYPTO_PREFIX %+ _AES_encrypt
%xdefine AES_ofb128_encrypt XCRYPTO_PREFIX %+ _AES_ofb128_encrypt
%xdefine AES_set_decrypt_key XCRYPTO_PREFIX %+ _AES_set_decrypt_key
%xdefine AES_set_encrypt_key XCRYPTO_PREFIX %+ _AES_set_encrypt_key
%xdefine AES_unwrap_key XCRYPTO_PREFIX %+ _AES_unwrap_key
%xdefine AES_unwrap_key_padded XCRYPTO_PREFIX %+ _AES_unwrap_key_padded
%xdefine AES_wrap_key XCRYPTO_PREFIX %+ _AES_wrap_key
%xdefine AES_wrap_key_padded XCRYPTO_PREFIX %+ _AES_wrap_key_padded
%xdefine ASN1_ANY_it XCRYPTO_PREFIX %+ _ASN1_ANY_it
%xdefine ASN1_BIT_STRING_check XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_check
%xdefine ASN1_BIT_STRING_free XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_free
%xdefine ASN1_BIT_STRING_get_bit XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_get_bit
%xdefine ASN1_BIT_STRING_it XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_it
%xdefine ASN1_BIT_STRING_new XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_new
%xdefine ASN1_BIT_STRING_set XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_set
%xdefine ASN1_BIT_STRING_set_bit XCRYPTO_PREFIX %+ _ASN1_BIT_STRING_set_bit
%xdefine ASN1_BMPSTRING_free XCRYPTO_PREFIX %+ _ASN1_BMPSTRING_free
%xdefine ASN1_BMPSTRING_it XCRYPTO_PREFIX %+ _ASN1_BMPSTRING_it
%xdefine ASN1_BMPSTRING_new XCRYPTO_PREFIX %+ _ASN1_BMPSTRING_new
%xdefine ASN1_BOOLEAN_it XCRYPTO_PREFIX %+ _ASN1_BOOLEAN_it
%xdefine ASN1_ENUMERATED_free XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_free
%xdefine ASN1_ENUMERATED_get XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_get
%xdefine ASN1_ENUMERATED_it XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_it
%xdefine ASN1_ENUMERATED_new XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_new
%xdefine ASN1_ENUMERATED_set XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_set
%xdefine ASN1_ENUMERATED_to_BN XCRYPTO_PREFIX %+ _ASN1_ENUMERATED_to_BN
%xdefine ASN1_FBOOLEAN_it XCRYPTO_PREFIX %+ _ASN1_FBOOLEAN_it
%xdefine ASN1_GENERALIZEDTIME_adj XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_adj
%xdefine ASN1_GENERALIZEDTIME_check XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_check
%xdefine ASN1_GENERALIZEDTIME_free XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_free
%xdefine ASN1_GENERALIZEDTIME_it XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_it
%xdefine ASN1_GENERALIZEDTIME_new XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_new
%xdefine ASN1_GENERALIZEDTIME_print XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_print
%xdefine ASN1_GENERALIZEDTIME_set XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_set
%xdefine ASN1_GENERALIZEDTIME_set_string XCRYPTO_PREFIX %+ _ASN1_GENERALIZEDTIME_set_string
%xdefine ASN1_GENERALSTRING_free XCRYPTO_PREFIX %+ _ASN1_GENERALSTRING_free
%xdefine ASN1_GENERALSTRING_it XCRYPTO_PREFIX %+ _ASN1_GENERALSTRING_it
%xdefine ASN1_GENERALSTRING_new XCRYPTO_PREFIX %+ _ASN1_GENERALSTRING_new
%xdefine ASN1_IA5STRING_free XCRYPTO_PREFIX %+ _ASN1_IA5STRING_free
%xdefine ASN1_IA5STRING_it XCRYPTO_PREFIX %+ _ASN1_IA5STRING_it
%xdefine ASN1_IA5STRING_new XCRYPTO_PREFIX %+ _ASN1_IA5STRING_new
%xdefine ASN1_INTEGER_cmp XCRYPTO_PREFIX %+ _ASN1_INTEGER_cmp
%xdefine ASN1_INTEGER_dup XCRYPTO_PREFIX %+ _ASN1_INTEGER_dup
%xdefine ASN1_INTEGER_free XCRYPTO_PREFIX %+ _ASN1_INTEGER_free
%xdefine ASN1_INTEGER_get XCRYPTO_PREFIX %+ _ASN1_INTEGER_get
%xdefine ASN1_INTEGER_it XCRYPTO_PREFIX %+ _ASN1_INTEGER_it
%xdefine ASN1_INTEGER_new XCRYPTO_PREFIX %+ _ASN1_INTEGER_new
%xdefine ASN1_INTEGER_set XCRYPTO_PREFIX %+ _ASN1_INTEGER_set
%xdefine ASN1_INTEGER_set_uint64 XCRYPTO_PREFIX %+ _ASN1_INTEGER_set_uint64
%xdefine ASN1_INTEGER_to_BN XCRYPTO_PREFIX %+ _ASN1_INTEGER_to_BN
%xdefine ASN1_NULL_free XCRYPTO_PREFIX %+ _ASN1_NULL_free
%xdefine ASN1_NULL_it XCRYPTO_PREFIX %+ _ASN1_NULL_it
%xdefine ASN1_NULL_new XCRYPTO_PREFIX %+ _ASN1_NULL_new
%xdefine ASN1_OBJECT_create XCRYPTO_PREFIX %+ _ASN1_OBJECT_create
%xdefine ASN1_OBJECT_free XCRYPTO_PREFIX %+ _ASN1_OBJECT_free
%xdefine ASN1_OBJECT_it XCRYPTO_PREFIX %+ _ASN1_OBJECT_it
%xdefine ASN1_OBJECT_new XCRYPTO_PREFIX %+ _ASN1_OBJECT_new
%xdefine ASN1_OCTET_STRING_NDEF_it XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_NDEF_it
%xdefine ASN1_OCTET_STRING_cmp XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_cmp
%xdefine ASN1_OCTET_STRING_dup XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_dup
%xdefine ASN1_OCTET_STRING_free XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_free
%xdefine ASN1_OCTET_STRING_it XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_it
%xdefine ASN1_OCTET_STRING_new XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_new
%xdefine ASN1_OCTET_STRING_set XCRYPTO_PREFIX %+ _ASN1_OCTET_STRING_set
%xdefine ASN1_PRINTABLESTRING_free XCRYPTO_PREFIX %+ _ASN1_PRINTABLESTRING_free
%xdefine ASN1_PRINTABLESTRING_it XCRYPTO_PREFIX %+ _ASN1_PRINTABLESTRING_it
%xdefine ASN1_PRINTABLESTRING_new XCRYPTO_PREFIX %+ _ASN1_PRINTABLESTRING_new
%xdefine ASN1_PRINTABLE_free XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_free
%xdefine ASN1_PRINTABLE_it XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_it
%xdefine ASN1_PRINTABLE_new XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_new
%xdefine ASN1_PRINTABLE_type XCRYPTO_PREFIX %+ _ASN1_PRINTABLE_type
%xdefine ASN1_SEQUENCE_ANY_it XCRYPTO_PREFIX %+ _ASN1_SEQUENCE_ANY_it
%xdefine ASN1_SEQUENCE_it XCRYPTO_PREFIX %+ _ASN1_SEQUENCE_it
%xdefine ASN1_SET_ANY_it XCRYPTO_PREFIX %+ _ASN1_SET_ANY_it
%xdefine ASN1_STRING_TABLE_add XCRYPTO_PREFIX %+ _ASN1_STRING_TABLE_add
%xdefine ASN1_STRING_TABLE_cleanup XCRYPTO_PREFIX %+ _ASN1_STRING_TABLE_cleanup
%xdefine ASN1_STRING_TABLE_get XCRYPTO_PREFIX %+ _ASN1_STRING_TABLE_get
%xdefine ASN1_STRING_cmp XCRYPTO_PREFIX %+ _ASN1_STRING_cmp
%xdefine ASN1_STRING_copy XCRYPTO_PREFIX %+ _ASN1_STRING_copy
%xdefine ASN1_STRING_data XCRYPTO_PREFIX %+ _ASN1_STRING_data
%xdefine ASN1_STRING_dup XCRYPTO_PREFIX %+ _ASN1_STRING_dup
%xdefine ASN1_STRING_free XCRYPTO_PREFIX %+ _ASN1_STRING_free
%xdefine ASN1_STRING_get0_data XCRYPTO_PREFIX %+ _ASN1_STRING_get0_data
%xdefine ASN1_STRING_get_default_mask XCRYPTO_PREFIX %+ _ASN1_STRING_get_default_mask
%xdefine ASN1_STRING_length XCRYPTO_PREFIX %+ _ASN1_STRING_length
%xdefine ASN1_STRING_length_set XCRYPTO_PREFIX %+ _ASN1_STRING_length_set
%xdefine ASN1_STRING_new XCRYPTO_PREFIX %+ _ASN1_STRING_new
%xdefine ASN1_STRING_print XCRYPTO_PREFIX %+ _ASN1_STRING_print
%xdefine ASN1_STRING_print_ex XCRYPTO_PREFIX %+ _ASN1_STRING_print_ex
%xdefine ASN1_STRING_print_ex_fp XCRYPTO_PREFIX %+ _ASN1_STRING_print_ex_fp
%xdefine ASN1_STRING_set XCRYPTO_PREFIX %+ _ASN1_STRING_set
%xdefine ASN1_STRING_set0 XCRYPTO_PREFIX %+ _ASN1_STRING_set0
%xdefine ASN1_STRING_set_by_NID XCRYPTO_PREFIX %+ _ASN1_STRING_set_by_NID
%xdefine ASN1_STRING_set_default_mask XCRYPTO_PREFIX %+ _ASN1_STRING_set_default_mask
%xdefine ASN1_STRING_set_default_mask_asc XCRYPTO_PREFIX %+ _ASN1_STRING_set_default_mask_asc
%xdefine ASN1_STRING_to_UTF8 XCRYPTO_PREFIX %+ _ASN1_STRING_to_UTF8
%xdefine ASN1_STRING_type XCRYPTO_PREFIX %+ _ASN1_STRING_type
%xdefine ASN1_STRING_type_new XCRYPTO_PREFIX %+ _ASN1_STRING_type_new
%xdefine ASN1_T61STRING_free XCRYPTO_PREFIX %+ _ASN1_T61STRING_free
%xdefine ASN1_T61STRING_it XCRYPTO_PREFIX %+ _ASN1_T61STRING_it
%xdefine ASN1_T61STRING_new XCRYPTO_PREFIX %+ _ASN1_T61STRING_new
%xdefine ASN1_TBOOLEAN_it XCRYPTO_PREFIX %+ _ASN1_TBOOLEAN_it
%xdefine ASN1_TIME_adj XCRYPTO_PREFIX %+ _ASN1_TIME_adj
%xdefine ASN1_TIME_check XCRYPTO_PREFIX %+ _ASN1_TIME_check
%xdefine ASN1_TIME_diff XCRYPTO_PREFIX %+ _ASN1_TIME_diff
%xdefine ASN1_TIME_free XCRYPTO_PREFIX %+ _ASN1_TIME_free
%xdefine ASN1_TIME_it XCRYPTO_PREFIX %+ _ASN1_TIME_it
%xdefine ASN1_TIME_new XCRYPTO_PREFIX %+ _ASN1_TIME_new
%xdefine ASN1_TIME_print XCRYPTO_PREFIX %+ _ASN1_TIME_print
%xdefine ASN1_TIME_set XCRYPTO_PREFIX %+ _ASN1_TIME_set
%xdefine ASN1_TIME_set_string XCRYPTO_PREFIX %+ _ASN1_TIME_set_string
%xdefine ASN1_TIME_to_generalizedtime XCRYPTO_PREFIX %+ _ASN1_TIME_to_generalizedtime
%xdefine ASN1_TYPE_cmp XCRYPTO_PREFIX %+ _ASN1_TYPE_cmp
%xdefine ASN1_TYPE_free XCRYPTO_PREFIX %+ _ASN1_TYPE_free
%xdefine ASN1_TYPE_get XCRYPTO_PREFIX %+ _ASN1_TYPE_get
%xdefine ASN1_TYPE_new XCRYPTO_PREFIX %+ _ASN1_TYPE_new
%xdefine ASN1_TYPE_set XCRYPTO_PREFIX %+ _ASN1_TYPE_set
%xdefine ASN1_TYPE_set1 XCRYPTO_PREFIX %+ _ASN1_TYPE_set1
%xdefine ASN1_UNIVERSALSTRING_free XCRYPTO_PREFIX %+ _ASN1_UNIVERSALSTRING_free
%xdefine ASN1_UNIVERSALSTRING_it XCRYPTO_PREFIX %+ _ASN1_UNIVERSALSTRING_it
%xdefine ASN1_UNIVERSALSTRING_new XCRYPTO_PREFIX %+ _ASN1_UNIVERSALSTRING_new
%xdefine ASN1_UTCTIME_adj XCRYPTO_PREFIX %+ _ASN1_UTCTIME_adj
%xdefine ASN1_UTCTIME_check XCRYPTO_PREFIX %+ _ASN1_UTCTIME_check
%xdefine ASN1_UTCTIME_cmp_time_t XCRYPTO_PREFIX %+ _ASN1_UTCTIME_cmp_time_t
%xdefine ASN1_UTCTIME_free XCRYPTO_PREFIX %+ _ASN1_UTCTIME_free
%xdefine ASN1_UTCTIME_it XCRYPTO_PREFIX %+ _ASN1_UTCTIME_it
%xdefine ASN1_UTCTIME_new XCRYPTO_PREFIX %+ _ASN1_UTCTIME_new
%xdefine ASN1_UTCTIME_print XCRYPTO_PREFIX %+ _ASN1_UTCTIME_print
%xdefine ASN1_UTCTIME_set XCRYPTO_PREFIX %+ _ASN1_UTCTIME_set
%xdefine ASN1_UTCTIME_set_string XCRYPTO_PREFIX %+ _ASN1_UTCTIME_set_string
%xdefine ASN1_UTF8STRING_free XCRYPTO_PREFIX %+ _ASN1_UTF8STRING_free
%xdefine ASN1_UTF8STRING_it XCRYPTO_PREFIX %+ _ASN1_UTF8STRING_it
%xdefine ASN1_UTF8STRING_new XCRYPTO_PREFIX %+ _ASN1_UTF8STRING_new
%xdefine ASN1_VISIBLESTRING_free XCRYPTO_PREFIX %+ _ASN1_VISIBLESTRING_free
%xdefine ASN1_VISIBLESTRING_it XCRYPTO_PREFIX %+ _ASN1_VISIBLESTRING_it
%xdefine ASN1_VISIBLESTRING_new XCRYPTO_PREFIX %+ _ASN1_VISIBLESTRING_new
%xdefine ASN1_digest XCRYPTO_PREFIX %+ _ASN1_digest
%xdefine ASN1_generate_nconf XCRYPTO_PREFIX %+ _ASN1_generate_nconf
%xdefine ASN1_generate_v3 XCRYPTO_PREFIX %+ _ASN1_generate_v3
%xdefine ASN1_get_object XCRYPTO_PREFIX %+ _ASN1_get_object
%xdefine ASN1_item_d2i XCRYPTO_PREFIX %+ _ASN1_item_d2i
%xdefine ASN1_item_d2i_bio XCRYPTO_PREFIX %+ _ASN1_item_d2i_bio
%xdefine ASN1_item_d2i_fp XCRYPTO_PREFIX %+ _ASN1_item_d2i_fp
%xdefine ASN1_item_digest XCRYPTO_PREFIX %+ _ASN1_item_digest
%xdefine ASN1_item_dup XCRYPTO_PREFIX %+ _ASN1_item_dup
%xdefine ASN1_item_ex_d2i XCRYPTO_PREFIX %+ _ASN1_item_ex_d2i
%xdefine ASN1_item_ex_free XCRYPTO_PREFIX %+ _ASN1_item_ex_free
%xdefine ASN1_item_ex_i2d XCRYPTO_PREFIX %+ _ASN1_item_ex_i2d
%xdefine ASN1_item_ex_new XCRYPTO_PREFIX %+ _ASN1_item_ex_new
%xdefine ASN1_item_free XCRYPTO_PREFIX %+ _ASN1_item_free
%xdefine ASN1_item_i2d XCRYPTO_PREFIX %+ _ASN1_item_i2d
%xdefine ASN1_item_i2d_bio XCRYPTO_PREFIX %+ _ASN1_item_i2d_bio
%xdefine ASN1_item_i2d_fp XCRYPTO_PREFIX %+ _ASN1_item_i2d_fp
%xdefine ASN1_item_ndef_i2d XCRYPTO_PREFIX %+ _ASN1_item_ndef_i2d
%xdefine ASN1_item_new XCRYPTO_PREFIX %+ _ASN1_item_new
%xdefine ASN1_item_pack XCRYPTO_PREFIX %+ _ASN1_item_pack
%xdefine ASN1_item_sign XCRYPTO_PREFIX %+ _ASN1_item_sign
%xdefine ASN1_item_sign_ctx XCRYPTO_PREFIX %+ _ASN1_item_sign_ctx
%xdefine ASN1_item_unpack XCRYPTO_PREFIX %+ _ASN1_item_unpack
%xdefine ASN1_item_verify XCRYPTO_PREFIX %+ _ASN1_item_verify
%xdefine ASN1_mbstring_copy XCRYPTO_PREFIX %+ _ASN1_mbstring_copy
%xdefine ASN1_mbstring_ncopy XCRYPTO_PREFIX %+ _ASN1_mbstring_ncopy
%xdefine ASN1_object_size XCRYPTO_PREFIX %+ _ASN1_object_size
%xdefine ASN1_primitive_free XCRYPTO_PREFIX %+ _ASN1_primitive_free
%xdefine ASN1_primitive_new XCRYPTO_PREFIX %+ _ASN1_primitive_new
%xdefine ASN1_put_eoc XCRYPTO_PREFIX %+ _ASN1_put_eoc
%xdefine ASN1_put_object XCRYPTO_PREFIX %+ _ASN1_put_object
%xdefine ASN1_tag2bit XCRYPTO_PREFIX %+ _ASN1_tag2bit
%xdefine ASN1_tag2str XCRYPTO_PREFIX %+ _ASN1_tag2str
%xdefine ASN1_template_free XCRYPTO_PREFIX %+ _ASN1_template_free
%xdefine ASN1_template_new XCRYPTO_PREFIX %+ _ASN1_template_new
%xdefine AUTHORITY_INFO_ACCESS_free XCRYPTO_PREFIX %+ _AUTHORITY_INFO_ACCESS_free
%xdefine AUTHORITY_INFO_ACCESS_it XCRYPTO_PREFIX %+ _AUTHORITY_INFO_ACCESS_it
%xdefine AUTHORITY_INFO_ACCESS_new XCRYPTO_PREFIX %+ _AUTHORITY_INFO_ACCESS_new
%xdefine AUTHORITY_KEYID_free XCRYPTO_PREFIX %+ _AUTHORITY_KEYID_free
%xdefine AUTHORITY_KEYID_it XCRYPTO_PREFIX %+ _AUTHORITY_KEYID_it
%xdefine AUTHORITY_KEYID_new XCRYPTO_PREFIX %+ _AUTHORITY_KEYID_new
%xdefine BASIC_CONSTRAINTS_free XCRYPTO_PREFIX %+ _BASIC_CONSTRAINTS_free
%xdefine BASIC_CONSTRAINTS_it XCRYPTO_PREFIX %+ _BASIC_CONSTRAINTS_it
%xdefine BASIC_CONSTRAINTS_new XCRYPTO_PREFIX %+ _BASIC_CONSTRAINTS_new
%xdefine BIO_append_filename XCRYPTO_PREFIX %+ _BIO_append_filename
%xdefine BIO_callback_ctrl XCRYPTO_PREFIX %+ _BIO_callback_ctrl
%xdefine BIO_clear_flags XCRYPTO_PREFIX %+ _BIO_clear_flags
%xdefine BIO_clear_retry_flags XCRYPTO_PREFIX %+ _BIO_clear_retry_flags
%xdefine BIO_copy_next_retry XCRYPTO_PREFIX %+ _BIO_copy_next_retry
%xdefine BIO_ctrl XCRYPTO_PREFIX %+ _BIO_ctrl
%xdefine BIO_ctrl_get_read_request XCRYPTO_PREFIX %+ _BIO_ctrl_get_read_request
%xdefine BIO_ctrl_get_write_guarantee XCRYPTO_PREFIX %+ _BIO_ctrl_get_write_guarantee
%xdefine BIO_ctrl_pending XCRYPTO_PREFIX %+ _BIO_ctrl_pending
%xdefine BIO_do_connect XCRYPTO_PREFIX %+ _BIO_do_connect
%xdefine BIO_eof XCRYPTO_PREFIX %+ _BIO_eof
%xdefine BIO_f_ssl XCRYPTO_PREFIX %+ _BIO_f_ssl
%xdefine BIO_find_type XCRYPTO_PREFIX %+ _BIO_find_type
%xdefine BIO_flush XCRYPTO_PREFIX %+ _BIO_flush
%xdefine BIO_free XCRYPTO_PREFIX %+ _BIO_free
%xdefine BIO_free_all XCRYPTO_PREFIX %+ _BIO_free_all
%xdefine BIO_get_data XCRYPTO_PREFIX %+ _BIO_get_data
%xdefine BIO_get_fd XCRYPTO_PREFIX %+ _BIO_get_fd
%xdefine BIO_get_fp XCRYPTO_PREFIX %+ _BIO_get_fp
%xdefine BIO_get_init XCRYPTO_PREFIX %+ _BIO_get_init
%xdefine BIO_get_mem_data XCRYPTO_PREFIX %+ _BIO_get_mem_data
%xdefine BIO_get_mem_ptr XCRYPTO_PREFIX %+ _BIO_get_mem_ptr
%xdefine BIO_get_new_index XCRYPTO_PREFIX %+ _BIO_get_new_index
%xdefine BIO_get_retry_flags XCRYPTO_PREFIX %+ _BIO_get_retry_flags
%xdefine BIO_get_retry_reason XCRYPTO_PREFIX %+ _BIO_get_retry_reason
%xdefine BIO_get_shutdown XCRYPTO_PREFIX %+ _BIO_get_shutdown
%xdefine BIO_gets XCRYPTO_PREFIX %+ _BIO_gets
%xdefine BIO_hexdump XCRYPTO_PREFIX %+ _BIO_hexdump
%xdefine BIO_indent XCRYPTO_PREFIX %+ _BIO_indent
%xdefine BIO_int_ctrl XCRYPTO_PREFIX %+ _BIO_int_ctrl
%xdefine BIO_mem_contents XCRYPTO_PREFIX %+ _BIO_mem_contents
%xdefine BIO_meth_free XCRYPTO_PREFIX %+ _BIO_meth_free
%xdefine BIO_meth_new XCRYPTO_PREFIX %+ _BIO_meth_new
%xdefine BIO_meth_set_create XCRYPTO_PREFIX %+ _BIO_meth_set_create
%xdefine BIO_meth_set_ctrl XCRYPTO_PREFIX %+ _BIO_meth_set_ctrl
%xdefine BIO_meth_set_destroy XCRYPTO_PREFIX %+ _BIO_meth_set_destroy
%xdefine BIO_meth_set_gets XCRYPTO_PREFIX %+ _BIO_meth_set_gets
%xdefine BIO_meth_set_puts XCRYPTO_PREFIX %+ _BIO_meth_set_puts
%xdefine BIO_meth_set_read XCRYPTO_PREFIX %+ _BIO_meth_set_read
%xdefine BIO_meth_set_write XCRYPTO_PREFIX %+ _BIO_meth_set_write
%xdefine BIO_method_type XCRYPTO_PREFIX %+ _BIO_method_type
%xdefine BIO_new XCRYPTO_PREFIX %+ _BIO_new
%xdefine BIO_new_bio_pair XCRYPTO_PREFIX %+ _BIO_new_bio_pair
%xdefine BIO_new_connect XCRYPTO_PREFIX %+ _BIO_new_connect
%xdefine BIO_new_fd XCRYPTO_PREFIX %+ _BIO_new_fd
%xdefine BIO_new_file XCRYPTO_PREFIX %+ _BIO_new_file
%xdefine BIO_new_fp XCRYPTO_PREFIX %+ _BIO_new_fp
%xdefine BIO_new_mem_buf XCRYPTO_PREFIX %+ _BIO_new_mem_buf
%xdefine BIO_new_socket XCRYPTO_PREFIX %+ _BIO_new_socket
%xdefine BIO_next XCRYPTO_PREFIX %+ _BIO_next
%xdefine BIO_number_read XCRYPTO_PREFIX %+ _BIO_number_read
%xdefine BIO_number_written XCRYPTO_PREFIX %+ _BIO_number_written
%xdefine BIO_pending XCRYPTO_PREFIX %+ _BIO_pending
%xdefine BIO_pop XCRYPTO_PREFIX %+ _BIO_pop
%xdefine BIO_printf XCRYPTO_PREFIX %+ _BIO_printf
%xdefine BIO_ptr_ctrl XCRYPTO_PREFIX %+ _BIO_ptr_ctrl
%xdefine BIO_push XCRYPTO_PREFIX %+ _BIO_push
%xdefine BIO_puts XCRYPTO_PREFIX %+ _BIO_puts
%xdefine BIO_read XCRYPTO_PREFIX %+ _BIO_read
%xdefine BIO_read_asn1 XCRYPTO_PREFIX %+ _BIO_read_asn1
%xdefine BIO_read_filename XCRYPTO_PREFIX %+ _BIO_read_filename
%xdefine BIO_reset XCRYPTO_PREFIX %+ _BIO_reset
%xdefine BIO_rw_filename XCRYPTO_PREFIX %+ _BIO_rw_filename
%xdefine BIO_s_connect XCRYPTO_PREFIX %+ _BIO_s_connect
%xdefine BIO_s_fd XCRYPTO_PREFIX %+ _BIO_s_fd
%xdefine BIO_s_file XCRYPTO_PREFIX %+ _BIO_s_file
%xdefine BIO_s_mem XCRYPTO_PREFIX %+ _BIO_s_mem
%xdefine BIO_s_socket XCRYPTO_PREFIX %+ _BIO_s_socket
%xdefine BIO_set_close XCRYPTO_PREFIX %+ _BIO_set_close
%xdefine BIO_set_conn_hostname XCRYPTO_PREFIX %+ _BIO_set_conn_hostname
%xdefine BIO_set_conn_int_port XCRYPTO_PREFIX %+ _BIO_set_conn_int_port
%xdefine BIO_set_conn_port XCRYPTO_PREFIX %+ _BIO_set_conn_port
%xdefine BIO_set_data XCRYPTO_PREFIX %+ _BIO_set_data
%xdefine BIO_set_fd XCRYPTO_PREFIX %+ _BIO_set_fd
%xdefine BIO_set_flags XCRYPTO_PREFIX %+ _BIO_set_flags
%xdefine BIO_set_fp XCRYPTO_PREFIX %+ _BIO_set_fp
%xdefine BIO_set_init XCRYPTO_PREFIX %+ _BIO_set_init
%xdefine BIO_set_mem_buf XCRYPTO_PREFIX %+ _BIO_set_mem_buf
%xdefine BIO_set_mem_eof_return XCRYPTO_PREFIX %+ _BIO_set_mem_eof_return
%xdefine BIO_set_nbio XCRYPTO_PREFIX %+ _BIO_set_nbio
%xdefine BIO_set_retry_read XCRYPTO_PREFIX %+ _BIO_set_retry_read
%xdefine BIO_set_retry_special XCRYPTO_PREFIX %+ _BIO_set_retry_special
%xdefine BIO_set_retry_write XCRYPTO_PREFIX %+ _BIO_set_retry_write
%xdefine BIO_set_shutdown XCRYPTO_PREFIX %+ _BIO_set_shutdown
%xdefine BIO_set_ssl XCRYPTO_PREFIX %+ _BIO_set_ssl
%xdefine BIO_set_write_buffer_size XCRYPTO_PREFIX %+ _BIO_set_write_buffer_size
%xdefine BIO_should_io_special XCRYPTO_PREFIX %+ _BIO_should_io_special
%xdefine BIO_should_read XCRYPTO_PREFIX %+ _BIO_should_read
%xdefine BIO_should_retry XCRYPTO_PREFIX %+ _BIO_should_retry
%xdefine BIO_should_write XCRYPTO_PREFIX %+ _BIO_should_write
%xdefine BIO_shutdown_wr XCRYPTO_PREFIX %+ _BIO_shutdown_wr
%xdefine BIO_snprintf XCRYPTO_PREFIX %+ _BIO_snprintf
%xdefine BIO_test_flags XCRYPTO_PREFIX %+ _BIO_test_flags
%xdefine BIO_up_ref XCRYPTO_PREFIX %+ _BIO_up_ref
%xdefine BIO_vfree XCRYPTO_PREFIX %+ _BIO_vfree
%xdefine BIO_vsnprintf XCRYPTO_PREFIX %+ _BIO_vsnprintf
%xdefine BIO_wpending XCRYPTO_PREFIX %+ _BIO_wpending
%xdefine BIO_write XCRYPTO_PREFIX %+ _BIO_write
%xdefine BIO_write_all XCRYPTO_PREFIX %+ _BIO_write_all
%xdefine BIO_write_filename XCRYPTO_PREFIX %+ _BIO_write_filename
%xdefine BN_BLINDING_convert XCRYPTO_PREFIX %+ _BN_BLINDING_convert
%xdefine BN_BLINDING_free XCRYPTO_PREFIX %+ _BN_BLINDING_free
%xdefine BN_BLINDING_invalidate XCRYPTO_PREFIX %+ _BN_BLINDING_invalidate
%xdefine BN_BLINDING_invert XCRYPTO_PREFIX %+ _BN_BLINDING_invert
%xdefine BN_BLINDING_new XCRYPTO_PREFIX %+ _BN_BLINDING_new
%xdefine BN_CTX_end XCRYPTO_PREFIX %+ _BN_CTX_end
%xdefine BN_CTX_free XCRYPTO_PREFIX %+ _BN_CTX_free
%xdefine BN_CTX_get XCRYPTO_PREFIX %+ _BN_CTX_get
%xdefine BN_CTX_new XCRYPTO_PREFIX %+ _BN_CTX_new
%xdefine BN_CTX_start XCRYPTO_PREFIX %+ _BN_CTX_start
%xdefine BN_GENCB_call XCRYPTO_PREFIX %+ _BN_GENCB_call
%xdefine BN_GENCB_set XCRYPTO_PREFIX %+ _BN_GENCB_set
%xdefine BN_MONT_CTX_copy XCRYPTO_PREFIX %+ _BN_MONT_CTX_copy
%xdefine BN_MONT_CTX_free XCRYPTO_PREFIX %+ _BN_MONT_CTX_free
%xdefine BN_MONT_CTX_new XCRYPTO_PREFIX %+ _BN_MONT_CTX_new
%xdefine BN_MONT_CTX_new_consttime XCRYPTO_PREFIX %+ _BN_MONT_CTX_new_consttime
%xdefine BN_MONT_CTX_new_for_modulus XCRYPTO_PREFIX %+ _BN_MONT_CTX_new_for_modulus
%xdefine BN_MONT_CTX_set XCRYPTO_PREFIX %+ _BN_MONT_CTX_set
%xdefine BN_MONT_CTX_set_locked XCRYPTO_PREFIX %+ _BN_MONT_CTX_set_locked
%xdefine BN_abs_is_word XCRYPTO_PREFIX %+ _BN_abs_is_word
%xdefine BN_add XCRYPTO_PREFIX %+ _BN_add
%xdefine BN_add_word XCRYPTO_PREFIX %+ _BN_add_word
%xdefine BN_asc2bn XCRYPTO_PREFIX %+ _BN_asc2bn
%xdefine BN_bin2bn XCRYPTO_PREFIX %+ _BN_bin2bn
%xdefine BN_bn2bin XCRYPTO_PREFIX %+ _BN_bn2bin
%xdefine BN_bn2bin_padded XCRYPTO_PREFIX %+ _BN_bn2bin_padded
%xdefine BN_bn2binpad XCRYPTO_PREFIX %+ _BN_bn2binpad
%xdefine BN_bn2cbb_padded XCRYPTO_PREFIX %+ _BN_bn2cbb_padded
%xdefine BN_bn2dec XCRYPTO_PREFIX %+ _BN_bn2dec
%xdefine BN_bn2hex XCRYPTO_PREFIX %+ _BN_bn2hex
%xdefine BN_bn2le_padded XCRYPTO_PREFIX %+ _BN_bn2le_padded
%xdefine BN_bn2mpi XCRYPTO_PREFIX %+ _BN_bn2mpi
%xdefine BN_clear XCRYPTO_PREFIX %+ _BN_clear
%xdefine BN_clear_bit XCRYPTO_PREFIX %+ _BN_clear_bit
%xdefine BN_clear_free XCRYPTO_PREFIX %+ _BN_clear_free
%xdefine BN_cmp XCRYPTO_PREFIX %+ _BN_cmp
%xdefine BN_cmp_word XCRYPTO_PREFIX %+ _BN_cmp_word
%xdefine BN_copy XCRYPTO_PREFIX %+ _BN_copy
%xdefine BN_count_low_zero_bits XCRYPTO_PREFIX %+ _BN_count_low_zero_bits
%xdefine BN_dec2bn XCRYPTO_PREFIX %+ _BN_dec2bn
%xdefine BN_div XCRYPTO_PREFIX %+ _BN_div
%xdefine BN_div_word XCRYPTO_PREFIX %+ _BN_div_word
%xdefine BN_dup XCRYPTO_PREFIX %+ _BN_dup
%xdefine BN_enhanced_miller_rabin_primality_test XCRYPTO_PREFIX %+ _BN_enhanced_miller_rabin_primality_test
%xdefine BN_equal_consttime XCRYPTO_PREFIX %+ _BN_equal_consttime
%xdefine BN_exp XCRYPTO_PREFIX %+ _BN_exp
%xdefine BN_free XCRYPTO_PREFIX %+ _BN_free
%xdefine BN_from_montgomery XCRYPTO_PREFIX %+ _BN_from_montgomery
%xdefine BN_gcd XCRYPTO_PREFIX %+ _BN_gcd
%xdefine BN_generate_prime_ex XCRYPTO_PREFIX %+ _BN_generate_prime_ex
%xdefine BN_get_rfc3526_prime_1536 XCRYPTO_PREFIX %+ _BN_get_rfc3526_prime_1536
%xdefine BN_get_u64 XCRYPTO_PREFIX %+ _BN_get_u64
%xdefine BN_get_word XCRYPTO_PREFIX %+ _BN_get_word
%xdefine BN_hex2bn XCRYPTO_PREFIX %+ _BN_hex2bn
%xdefine BN_init XCRYPTO_PREFIX %+ _BN_init
%xdefine BN_is_bit_set XCRYPTO_PREFIX %+ _BN_is_bit_set
%xdefine BN_is_negative XCRYPTO_PREFIX %+ _BN_is_negative
%xdefine BN_is_odd XCRYPTO_PREFIX %+ _BN_is_odd
%xdefine BN_is_one XCRYPTO_PREFIX %+ _BN_is_one
%xdefine BN_is_pow2 XCRYPTO_PREFIX %+ _BN_is_pow2
%xdefine BN_is_prime_ex XCRYPTO_PREFIX %+ _BN_is_prime_ex
%xdefine BN_is_prime_fasttest_ex XCRYPTO_PREFIX %+ _BN_is_prime_fasttest_ex
%xdefine BN_is_word XCRYPTO_PREFIX %+ _BN_is_word
%xdefine BN_is_zero XCRYPTO_PREFIX %+ _BN_is_zero
%xdefine BN_le2bn XCRYPTO_PREFIX %+ _BN_le2bn
%xdefine BN_lshift XCRYPTO_PREFIX %+ _BN_lshift
%xdefine BN_lshift1 XCRYPTO_PREFIX %+ _BN_lshift1
%xdefine BN_marshal_asn1 XCRYPTO_PREFIX %+ _BN_marshal_asn1
%xdefine BN_mask_bits XCRYPTO_PREFIX %+ _BN_mask_bits
%xdefine BN_mod_add XCRYPTO_PREFIX %+ _BN_mod_add
%xdefine BN_mod_add_quick XCRYPTO_PREFIX %+ _BN_mod_add_quick
%xdefine BN_mod_exp XCRYPTO_PREFIX %+ _BN_mod_exp
%xdefine BN_mod_exp2_mont XCRYPTO_PREFIX %+ _BN_mod_exp2_mont
%xdefine BN_mod_exp_mont XCRYPTO_PREFIX %+ _BN_mod_exp_mont
%xdefine BN_mod_exp_mont_consttime XCRYPTO_PREFIX %+ _BN_mod_exp_mont_consttime
%xdefine BN_mod_exp_mont_word XCRYPTO_PREFIX %+ _BN_mod_exp_mont_word
%xdefine BN_mod_inverse XCRYPTO_PREFIX %+ _BN_mod_inverse
%xdefine BN_mod_inverse_blinded XCRYPTO_PREFIX %+ _BN_mod_inverse_blinded
%xdefine BN_mod_inverse_odd XCRYPTO_PREFIX %+ _BN_mod_inverse_odd
%xdefine BN_mod_lshift XCRYPTO_PREFIX %+ _BN_mod_lshift
%xdefine BN_mod_lshift1 XCRYPTO_PREFIX %+ _BN_mod_lshift1
%xdefine BN_mod_lshift1_quick XCRYPTO_PREFIX %+ _BN_mod_lshift1_quick
%xdefine BN_mod_lshift_quick XCRYPTO_PREFIX %+ _BN_mod_lshift_quick
%xdefine BN_mod_mul XCRYPTO_PREFIX %+ _BN_mod_mul
%xdefine BN_mod_mul_montgomery XCRYPTO_PREFIX %+ _BN_mod_mul_montgomery
%xdefine BN_mod_pow2 XCRYPTO_PREFIX %+ _BN_mod_pow2
%xdefine BN_mod_sqr XCRYPTO_PREFIX %+ _BN_mod_sqr
%xdefine BN_mod_sqrt XCRYPTO_PREFIX %+ _BN_mod_sqrt
%xdefine BN_mod_sub XCRYPTO_PREFIX %+ _BN_mod_sub
%xdefine BN_mod_sub_quick XCRYPTO_PREFIX %+ _BN_mod_sub_quick
%xdefine BN_mod_word XCRYPTO_PREFIX %+ _BN_mod_word
%xdefine BN_mpi2bn XCRYPTO_PREFIX %+ _BN_mpi2bn
%xdefine BN_mul XCRYPTO_PREFIX %+ _BN_mul
%xdefine BN_mul_word XCRYPTO_PREFIX %+ _BN_mul_word
%xdefine BN_new XCRYPTO_PREFIX %+ _BN_new
%xdefine BN_nnmod XCRYPTO_PREFIX %+ _BN_nnmod
%xdefine BN_nnmod_pow2 XCRYPTO_PREFIX %+ _BN_nnmod_pow2
%xdefine BN_num_bits XCRYPTO_PREFIX %+ _BN_num_bits
%xdefine BN_num_bits_word XCRYPTO_PREFIX %+ _BN_num_bits_word
%xdefine BN_num_bytes XCRYPTO_PREFIX %+ _BN_num_bytes
%xdefine BN_one XCRYPTO_PREFIX %+ _BN_one
%xdefine BN_parse_asn1_unsigned XCRYPTO_PREFIX %+ _BN_parse_asn1_unsigned
%xdefine BN_primality_test XCRYPTO_PREFIX %+ _BN_primality_test
%xdefine BN_print XCRYPTO_PREFIX %+ _BN_print
%xdefine BN_print_fp XCRYPTO_PREFIX %+ _BN_print_fp
%xdefine BN_pseudo_rand XCRYPTO_PREFIX %+ _BN_pseudo_rand
%xdefine BN_pseudo_rand_range XCRYPTO_PREFIX %+ _BN_pseudo_rand_range
%xdefine BN_rand XCRYPTO_PREFIX %+ _BN_rand
%xdefine BN_rand_range XCRYPTO_PREFIX %+ _BN_rand_range
%xdefine BN_rand_range_ex XCRYPTO_PREFIX %+ _BN_rand_range_ex
%xdefine BN_rshift XCRYPTO_PREFIX %+ _BN_rshift
%xdefine BN_rshift1 XCRYPTO_PREFIX %+ _BN_rshift1
%xdefine BN_set_bit XCRYPTO_PREFIX %+ _BN_set_bit
%xdefine BN_set_negative XCRYPTO_PREFIX %+ _BN_set_negative
%xdefine BN_set_u64 XCRYPTO_PREFIX %+ _BN_set_u64
%xdefine BN_set_word XCRYPTO_PREFIX %+ _BN_set_word
%xdefine BN_sqr XCRYPTO_PREFIX %+ _BN_sqr
%xdefine BN_sqrt XCRYPTO_PREFIX %+ _BN_sqrt
%xdefine BN_sub XCRYPTO_PREFIX %+ _BN_sub
%xdefine BN_sub_word XCRYPTO_PREFIX %+ _BN_sub_word
%xdefine BN_to_ASN1_ENUMERATED XCRYPTO_PREFIX %+ _BN_to_ASN1_ENUMERATED
%xdefine BN_to_ASN1_INTEGER XCRYPTO_PREFIX %+ _BN_to_ASN1_INTEGER
%xdefine BN_to_montgomery XCRYPTO_PREFIX %+ _BN_to_montgomery
%xdefine BN_uadd XCRYPTO_PREFIX %+ _BN_uadd
%xdefine BN_ucmp XCRYPTO_PREFIX %+ _BN_ucmp
%xdefine BN_usub XCRYPTO_PREFIX %+ _BN_usub
%xdefine BN_value_one XCRYPTO_PREFIX %+ _BN_value_one
%xdefine BN_zero XCRYPTO_PREFIX %+ _BN_zero
%xdefine BORINGSSL_self_test XCRYPTO_PREFIX %+ _BORINGSSL_self_test
%xdefine BUF_MEM_append XCRYPTO_PREFIX %+ _BUF_MEM_append
%xdefine BUF_MEM_free XCRYPTO_PREFIX %+ _BUF_MEM_free
%xdefine BUF_MEM_grow XCRYPTO_PREFIX %+ _BUF_MEM_grow
%xdefine BUF_MEM_grow_clean XCRYPTO_PREFIX %+ _BUF_MEM_grow_clean
%xdefine BUF_MEM_new XCRYPTO_PREFIX %+ _BUF_MEM_new
%xdefine BUF_MEM_reserve XCRYPTO_PREFIX %+ _BUF_MEM_reserve
%xdefine BUF_memdup XCRYPTO_PREFIX %+ _BUF_memdup
%xdefine BUF_strdup XCRYPTO_PREFIX %+ _BUF_strdup
%xdefine BUF_strlcat XCRYPTO_PREFIX %+ _BUF_strlcat
%xdefine BUF_strlcpy XCRYPTO_PREFIX %+ _BUF_strlcpy
%xdefine BUF_strndup XCRYPTO_PREFIX %+ _BUF_strndup
%xdefine BUF_strnlen XCRYPTO_PREFIX %+ _BUF_strnlen
%xdefine CBB_add_asn1 XCRYPTO_PREFIX %+ _CBB_add_asn1
%xdefine CBB_add_asn1_bool XCRYPTO_PREFIX %+ _CBB_add_asn1_bool
%xdefine CBB_add_asn1_int64 XCRYPTO_PREFIX %+ _CBB_add_asn1_int64
%xdefine CBB_add_asn1_octet_string XCRYPTO_PREFIX %+ _CBB_add_asn1_octet_string
%xdefine CBB_add_asn1_oid_from_text XCRYPTO_PREFIX %+ _CBB_add_asn1_oid_from_text
%xdefine CBB_add_asn1_uint64 XCRYPTO_PREFIX %+ _CBB_add_asn1_uint64
%xdefine CBB_add_bytes XCRYPTO_PREFIX %+ _CBB_add_bytes
%xdefine CBB_add_space XCRYPTO_PREFIX %+ _CBB_add_space
%xdefine CBB_add_u16 XCRYPTO_PREFIX %+ _CBB_add_u16
%xdefine CBB_add_u16_length_prefixed XCRYPTO_PREFIX %+ _CBB_add_u16_length_prefixed
%xdefine CBB_add_u16le XCRYPTO_PREFIX %+ _CBB_add_u16le
%xdefine CBB_add_u24 XCRYPTO_PREFIX %+ _CBB_add_u24
%xdefine CBB_add_u24_length_prefixed XCRYPTO_PREFIX %+ _CBB_add_u24_length_prefixed
%xdefine CBB_add_u32 XCRYPTO_PREFIX %+ _CBB_add_u32
%xdefine CBB_add_u32le XCRYPTO_PREFIX %+ _CBB_add_u32le
%xdefine CBB_add_u64 XCRYPTO_PREFIX %+ _CBB_add_u64
%xdefine CBB_add_u64le XCRYPTO_PREFIX %+ _CBB_add_u64le
%xdefine CBB_add_u8 XCRYPTO_PREFIX %+ _CBB_add_u8
%xdefine CBB_add_u8_length_prefixed XCRYPTO_PREFIX %+ _CBB_add_u8_length_prefixed
%xdefine CBB_cleanup XCRYPTO_PREFIX %+ _CBB_cleanup
%xdefine CBB_data XCRYPTO_PREFIX %+ _CBB_data
%xdefine CBB_did_write XCRYPTO_PREFIX %+ _CBB_did_write
%xdefine CBB_discard_child XCRYPTO_PREFIX %+ _CBB_discard_child
%xdefine CBB_finish XCRYPTO_PREFIX %+ _CBB_finish
%xdefine CBB_finish_i2d XCRYPTO_PREFIX %+ _CBB_finish_i2d
%xdefine CBB_flush XCRYPTO_PREFIX %+ _CBB_flush
%xdefine CBB_flush_asn1_set_of XCRYPTO_PREFIX %+ _CBB_flush_asn1_set_of
%xdefine CBB_init XCRYPTO_PREFIX %+ _CBB_init
%xdefine CBB_init_fixed XCRYPTO_PREFIX %+ _CBB_init_fixed
%xdefine CBB_len XCRYPTO_PREFIX %+ _CBB_len
%xdefine CBB_reserve XCRYPTO_PREFIX %+ _CBB_reserve
%xdefine CBB_zero XCRYPTO_PREFIX %+ _CBB_zero
%xdefine CBS_asn1_ber_to_der XCRYPTO_PREFIX %+ _CBS_asn1_ber_to_der
%xdefine CBS_asn1_bitstring_has_bit XCRYPTO_PREFIX %+ _CBS_asn1_bitstring_has_bit
%xdefine CBS_asn1_oid_to_text XCRYPTO_PREFIX %+ _CBS_asn1_oid_to_text
%xdefine CBS_contains_zero_byte XCRYPTO_PREFIX %+ _CBS_contains_zero_byte
%xdefine CBS_copy_bytes XCRYPTO_PREFIX %+ _CBS_copy_bytes
%xdefine CBS_data XCRYPTO_PREFIX %+ _CBS_data
%xdefine CBS_get_any_asn1 XCRYPTO_PREFIX %+ _CBS_get_any_asn1
%xdefine CBS_get_any_asn1_element XCRYPTO_PREFIX %+ _CBS_get_any_asn1_element
%xdefine CBS_get_any_ber_asn1_element XCRYPTO_PREFIX %+ _CBS_get_any_ber_asn1_element
%xdefine CBS_get_asn1 XCRYPTO_PREFIX %+ _CBS_get_asn1
%xdefine CBS_get_asn1_bool XCRYPTO_PREFIX %+ _CBS_get_asn1_bool
%xdefine CBS_get_asn1_element XCRYPTO_PREFIX %+ _CBS_get_asn1_element
%xdefine CBS_get_asn1_implicit_string XCRYPTO_PREFIX %+ _CBS_get_asn1_implicit_string
%xdefine CBS_get_asn1_int64 XCRYPTO_PREFIX %+ _CBS_get_asn1_int64
%xdefine CBS_get_asn1_uint64 XCRYPTO_PREFIX %+ _CBS_get_asn1_uint64
%xdefine CBS_get_bytes XCRYPTO_PREFIX %+ _CBS_get_bytes
%xdefine CBS_get_last_u8 XCRYPTO_PREFIX %+ _CBS_get_last_u8
%xdefine CBS_get_optional_asn1 XCRYPTO_PREFIX %+ _CBS_get_optional_asn1
%xdefine CBS_get_optional_asn1_bool XCRYPTO_PREFIX %+ _CBS_get_optional_asn1_bool
%xdefine CBS_get_optional_asn1_octet_string XCRYPTO_PREFIX %+ _CBS_get_optional_asn1_octet_string
%xdefine CBS_get_optional_asn1_uint64 XCRYPTO_PREFIX %+ _CBS_get_optional_asn1_uint64
%xdefine CBS_get_u16 XCRYPTO_PREFIX %+ _CBS_get_u16
%xdefine CBS_get_u16_length_prefixed XCRYPTO_PREFIX %+ _CBS_get_u16_length_prefixed
%xdefine CBS_get_u16le XCRYPTO_PREFIX %+ _CBS_get_u16le
%xdefine CBS_get_u24 XCRYPTO_PREFIX %+ _CBS_get_u24
%xdefine CBS_get_u24_length_prefixed XCRYPTO_PREFIX %+ _CBS_get_u24_length_prefixed
%xdefine CBS_get_u32 XCRYPTO_PREFIX %+ _CBS_get_u32
%xdefine CBS_get_u32le XCRYPTO_PREFIX %+ _CBS_get_u32le
%xdefine CBS_get_u64 XCRYPTO_PREFIX %+ _CBS_get_u64
%xdefine CBS_get_u64le XCRYPTO_PREFIX %+ _CBS_get_u64le
%xdefine CBS_get_u8 XCRYPTO_PREFIX %+ _CBS_get_u8
%xdefine CBS_get_u8_length_prefixed XCRYPTO_PREFIX %+ _CBS_get_u8_length_prefixed
%xdefine CBS_init XCRYPTO_PREFIX %+ _CBS_init
%xdefine CBS_is_valid_asn1_bitstring XCRYPTO_PREFIX %+ _CBS_is_valid_asn1_bitstring
%xdefine CBS_len XCRYPTO_PREFIX %+ _CBS_len
%xdefine CBS_mem_equal XCRYPTO_PREFIX %+ _CBS_mem_equal
%xdefine CBS_peek_asn1_tag XCRYPTO_PREFIX %+ _CBS_peek_asn1_tag
%xdefine CBS_skip XCRYPTO_PREFIX %+ _CBS_skip
%xdefine CBS_stow XCRYPTO_PREFIX %+ _CBS_stow
%xdefine CBS_strdup XCRYPTO_PREFIX %+ _CBS_strdup
%xdefine CERTIFICATEPOLICIES_free XCRYPTO_PREFIX %+ _CERTIFICATEPOLICIES_free
%xdefine CERTIFICATEPOLICIES_it XCRYPTO_PREFIX %+ _CERTIFICATEPOLICIES_it
%xdefine CERTIFICATEPOLICIES_new XCRYPTO_PREFIX %+ _CERTIFICATEPOLICIES_new
%xdefine CMAC_CTX_copy XCRYPTO_PREFIX %+ _CMAC_CTX_copy
%xdefine CMAC_CTX_free XCRYPTO_PREFIX %+ _CMAC_CTX_free
%xdefine CMAC_CTX_new XCRYPTO_PREFIX %+ _CMAC_CTX_new
%xdefine CMAC_Final XCRYPTO_PREFIX %+ _CMAC_Final
%xdefine CMAC_Init XCRYPTO_PREFIX %+ _CMAC_Init
%xdefine CMAC_Reset XCRYPTO_PREFIX %+ _CMAC_Reset
%xdefine CMAC_Update XCRYPTO_PREFIX %+ _CMAC_Update
%xdefine CONF_VALUE_new XCRYPTO_PREFIX %+ _CONF_VALUE_new
%xdefine CONF_modules_free XCRYPTO_PREFIX %+ _CONF_modules_free
%xdefine CONF_modules_load_file XCRYPTO_PREFIX %+ _CONF_modules_load_file
%xdefine CONF_parse_list XCRYPTO_PREFIX %+ _CONF_parse_list
%xdefine CRL_DIST_POINTS_free XCRYPTO_PREFIX %+ _CRL_DIST_POINTS_free
%xdefine CRL_DIST_POINTS_it XCRYPTO_PREFIX %+ _CRL_DIST_POINTS_it
%xdefine CRL_DIST_POINTS_new XCRYPTO_PREFIX %+ _CRL_DIST_POINTS_new
%xdefine CRYPTO_BUFFER_POOL_free XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_POOL_free
%xdefine CRYPTO_BUFFER_POOL_new XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_POOL_new
%xdefine CRYPTO_BUFFER_alloc XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_alloc
%xdefine CRYPTO_BUFFER_data XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_data
%xdefine CRYPTO_BUFFER_free XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_free
%xdefine CRYPTO_BUFFER_init_CBS XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_init_CBS
%xdefine CRYPTO_BUFFER_len XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_len
%xdefine CRYPTO_BUFFER_new XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_new
%xdefine CRYPTO_BUFFER_new_from_CBS XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_new_from_CBS
%xdefine CRYPTO_BUFFER_up_ref XCRYPTO_PREFIX %+ _CRYPTO_BUFFER_up_ref
%xdefine CRYPTO_MUTEX_cleanup XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_cleanup
%xdefine CRYPTO_MUTEX_init XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_init
%xdefine CRYPTO_MUTEX_lock_read XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_lock_read
%xdefine CRYPTO_MUTEX_lock_write XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_lock_write
%xdefine CRYPTO_MUTEX_unlock_read XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_unlock_read
%xdefine CRYPTO_MUTEX_unlock_write XCRYPTO_PREFIX %+ _CRYPTO_MUTEX_unlock_write
%xdefine CRYPTO_POLYVAL_finish XCRYPTO_PREFIX %+ _CRYPTO_POLYVAL_finish
%xdefine CRYPTO_POLYVAL_init XCRYPTO_PREFIX %+ _CRYPTO_POLYVAL_init
%xdefine CRYPTO_POLYVAL_update_blocks XCRYPTO_PREFIX %+ _CRYPTO_POLYVAL_update_blocks
%xdefine CRYPTO_STATIC_MUTEX_lock_read XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_lock_read
%xdefine CRYPTO_STATIC_MUTEX_lock_write XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_lock_write
%xdefine CRYPTO_STATIC_MUTEX_unlock_read XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_unlock_read
%xdefine CRYPTO_STATIC_MUTEX_unlock_write XCRYPTO_PREFIX %+ _CRYPTO_STATIC_MUTEX_unlock_write
%xdefine CRYPTO_THREADID_current XCRYPTO_PREFIX %+ _CRYPTO_THREADID_current
%xdefine CRYPTO_THREADID_set_callback XCRYPTO_PREFIX %+ _CRYPTO_THREADID_set_callback
%xdefine CRYPTO_THREADID_set_numeric XCRYPTO_PREFIX %+ _CRYPTO_THREADID_set_numeric
%xdefine CRYPTO_THREADID_set_pointer XCRYPTO_PREFIX %+ _CRYPTO_THREADID_set_pointer
%xdefine CRYPTO_cbc128_decrypt XCRYPTO_PREFIX %+ _CRYPTO_cbc128_decrypt
%xdefine CRYPTO_cbc128_encrypt XCRYPTO_PREFIX %+ _CRYPTO_cbc128_encrypt
%xdefine CRYPTO_cfb128_1_encrypt XCRYPTO_PREFIX %+ _CRYPTO_cfb128_1_encrypt
%xdefine CRYPTO_cfb128_8_encrypt XCRYPTO_PREFIX %+ _CRYPTO_cfb128_8_encrypt
%xdefine CRYPTO_cfb128_encrypt XCRYPTO_PREFIX %+ _CRYPTO_cfb128_encrypt
%xdefine CRYPTO_chacha_20 XCRYPTO_PREFIX %+ _CRYPTO_chacha_20
%xdefine CRYPTO_cleanup_all_ex_data XCRYPTO_PREFIX %+ _CRYPTO_cleanup_all_ex_data
%xdefine CRYPTO_ctr128_encrypt XCRYPTO_PREFIX %+ _CRYPTO_ctr128_encrypt
%xdefine CRYPTO_ctr128_encrypt_ctr32 XCRYPTO_PREFIX %+ _CRYPTO_ctr128_encrypt_ctr32
%xdefine CRYPTO_fork_detect_ignore_madv_wipeonfork_for_testing XCRYPTO_PREFIX %+ _CRYPTO_fork_detect_ignore_madv_wipeonfork_for_testing
%xdefine CRYPTO_free_ex_data XCRYPTO_PREFIX %+ _CRYPTO_free_ex_data
%xdefine CRYPTO_gcm128_aad XCRYPTO_PREFIX %+ _CRYPTO_gcm128_aad
%xdefine CRYPTO_gcm128_decrypt XCRYPTO_PREFIX %+ _CRYPTO_gcm128_decrypt
%xdefine CRYPTO_gcm128_decrypt_ctr32 XCRYPTO_PREFIX %+ _CRYPTO_gcm128_decrypt_ctr32
%xdefine CRYPTO_gcm128_encrypt XCRYPTO_PREFIX %+ _CRYPTO_gcm128_encrypt
%xdefine CRYPTO_gcm128_encrypt_ctr32 XCRYPTO_PREFIX %+ _CRYPTO_gcm128_encrypt_ctr32
%xdefine CRYPTO_gcm128_finish XCRYPTO_PREFIX %+ _CRYPTO_gcm128_finish
%xdefine CRYPTO_gcm128_init_key XCRYPTO_PREFIX %+ _CRYPTO_gcm128_init_key
%xdefine CRYPTO_gcm128_setiv XCRYPTO_PREFIX %+ _CRYPTO_gcm128_setiv
%xdefine CRYPTO_gcm128_tag XCRYPTO_PREFIX %+ _CRYPTO_gcm128_tag
%xdefine CRYPTO_get_dynlock_create_callback XCRYPTO_PREFIX %+ _CRYPTO_get_dynlock_create_callback
%xdefine CRYPTO_get_dynlock_destroy_callback XCRYPTO_PREFIX %+ _CRYPTO_get_dynlock_destroy_callback
%xdefine CRYPTO_get_dynlock_lock_callback XCRYPTO_PREFIX %+ _CRYPTO_get_dynlock_lock_callback
%xdefine CRYPTO_get_ex_data XCRYPTO_PREFIX %+ _CRYPTO_get_ex_data
%xdefine CRYPTO_get_ex_new_index XCRYPTO_PREFIX %+ _CRYPTO_get_ex_new_index
%xdefine CRYPTO_get_fork_generation XCRYPTO_PREFIX %+ _CRYPTO_get_fork_generation
%xdefine CRYPTO_get_lock_name XCRYPTO_PREFIX %+ _CRYPTO_get_lock_name
%xdefine CRYPTO_get_locking_callback XCRYPTO_PREFIX %+ _CRYPTO_get_locking_callback
%xdefine CRYPTO_get_thread_local XCRYPTO_PREFIX %+ _CRYPTO_get_thread_local
%xdefine CRYPTO_ghash_init XCRYPTO_PREFIX %+ _CRYPTO_ghash_init
%xdefine CRYPTO_has_asm XCRYPTO_PREFIX %+ _CRYPTO_has_asm
%xdefine CRYPTO_hchacha20 XCRYPTO_PREFIX %+ _CRYPTO_hchacha20
%xdefine CRYPTO_is_ARMv8_AES_capable XCRYPTO_PREFIX %+ _CRYPTO_is_ARMv8_AES_capable
%xdefine CRYPTO_is_ARMv8_PMULL_capable XCRYPTO_PREFIX %+ _CRYPTO_is_ARMv8_PMULL_capable
%xdefine CRYPTO_is_NEON_capable_at_runtime XCRYPTO_PREFIX %+ _CRYPTO_is_NEON_capable_at_runtime
%xdefine CRYPTO_is_confidential_build XCRYPTO_PREFIX %+ _CRYPTO_is_confidential_build
%xdefine CRYPTO_library_init XCRYPTO_PREFIX %+ _CRYPTO_library_init
%xdefine CRYPTO_malloc_init XCRYPTO_PREFIX %+ _CRYPTO_malloc_init
%xdefine CRYPTO_memcmp XCRYPTO_PREFIX %+ _CRYPTO_memcmp
%xdefine CRYPTO_new_ex_data XCRYPTO_PREFIX %+ _CRYPTO_new_ex_data
%xdefine CRYPTO_num_locks XCRYPTO_PREFIX %+ _CRYPTO_num_locks
%xdefine CRYPTO_ofb128_encrypt XCRYPTO_PREFIX %+ _CRYPTO_ofb128_encrypt
%xdefine CRYPTO_once XCRYPTO_PREFIX %+ _CRYPTO_once
%xdefine CRYPTO_poly1305_finish XCRYPTO_PREFIX %+ _CRYPTO_poly1305_finish
%xdefine CRYPTO_poly1305_init XCRYPTO_PREFIX %+ _CRYPTO_poly1305_init
%xdefine CRYPTO_poly1305_update XCRYPTO_PREFIX %+ _CRYPTO_poly1305_update
%xdefine CRYPTO_rdrand XCRYPTO_PREFIX %+ _CRYPTO_rdrand
%xdefine CRYPTO_rdrand_multiple8_buf XCRYPTO_PREFIX %+ _CRYPTO_rdrand_multiple8_buf
%xdefine CRYPTO_refcount_dec_and_test_zero XCRYPTO_PREFIX %+ _CRYPTO_refcount_dec_and_test_zero
%xdefine CRYPTO_refcount_inc XCRYPTO_PREFIX %+ _CRYPTO_refcount_inc
%xdefine CRYPTO_set_add_lock_callback XCRYPTO_PREFIX %+ _CRYPTO_set_add_lock_callback
%xdefine CRYPTO_set_dynlock_create_callback XCRYPTO_PREFIX %+ _CRYPTO_set_dynlock_create_callback
%xdefine CRYPTO_set_dynlock_destroy_callback XCRYPTO_PREFIX %+ _CRYPTO_set_dynlock_destroy_callback
%xdefine CRYPTO_set_dynlock_lock_callback XCRYPTO_PREFIX %+ _CRYPTO_set_dynlock_lock_callback
%xdefine CRYPTO_set_ex_data XCRYPTO_PREFIX %+ _CRYPTO_set_ex_data
%xdefine CRYPTO_set_id_callback XCRYPTO_PREFIX %+ _CRYPTO_set_id_callback
%xdefine CRYPTO_set_locking_callback XCRYPTO_PREFIX %+ _CRYPTO_set_locking_callback
%xdefine CRYPTO_set_thread_local XCRYPTO_PREFIX %+ _CRYPTO_set_thread_local
%xdefine CRYPTO_sysrand XCRYPTO_PREFIX %+ _CRYPTO_sysrand
%xdefine CRYPTO_sysrand_if_available XCRYPTO_PREFIX %+ _CRYPTO_sysrand_if_available
%xdefine CRYPTO_tls1_prf XCRYPTO_PREFIX %+ _CRYPTO_tls1_prf
%xdefine CTR_DRBG_clear XCRYPTO_PREFIX %+ _CTR_DRBG_clear
%xdefine CTR_DRBG_generate XCRYPTO_PREFIX %+ _CTR_DRBG_generate
%xdefine CTR_DRBG_init XCRYPTO_PREFIX %+ _CTR_DRBG_init
%xdefine CTR_DRBG_reseed XCRYPTO_PREFIX %+ _CTR_DRBG_reseed
%xdefine ChaCha20_ctr32 XCRYPTO_PREFIX %+ _ChaCha20_ctr32
%xdefine DES_decrypt3 XCRYPTO_PREFIX %+ _DES_decrypt3
%xdefine DES_ecb3_encrypt XCRYPTO_PREFIX %+ _DES_ecb3_encrypt
%xdefine DES_ecb_encrypt XCRYPTO_PREFIX %+ _DES_ecb_encrypt
%xdefine DES_ede2_cbc_encrypt XCRYPTO_PREFIX %+ _DES_ede2_cbc_encrypt
%xdefine DES_ede3_cbc_encrypt XCRYPTO_PREFIX %+ _DES_ede3_cbc_encrypt
%xdefine DES_encrypt3 XCRYPTO_PREFIX %+ _DES_encrypt3
%xdefine DES_ncbc_encrypt XCRYPTO_PREFIX %+ _DES_ncbc_encrypt
%xdefine DES_set_key XCRYPTO_PREFIX %+ _DES_set_key
%xdefine DES_set_key_unchecked XCRYPTO_PREFIX %+ _DES_set_key_unchecked
%xdefine DES_set_odd_parity XCRYPTO_PREFIX %+ _DES_set_odd_parity
%xdefine DH_check XCRYPTO_PREFIX %+ _DH_check
%xdefine DH_check_pub_key XCRYPTO_PREFIX %+ _DH_check_pub_key
%xdefine DH_compute_key XCRYPTO_PREFIX %+ _DH_compute_key
%xdefine DH_free XCRYPTO_PREFIX %+ _DH_free
%xdefine DH_generate_key XCRYPTO_PREFIX %+ _DH_generate_key
%xdefine DH_generate_parameters_ex XCRYPTO_PREFIX %+ _DH_generate_parameters_ex
%xdefine DH_get0_g XCRYPTO_PREFIX %+ _DH_get0_g
%xdefine DH_get0_key XCRYPTO_PREFIX %+ _DH_get0_key
%xdefine DH_get0_p XCRYPTO_PREFIX %+ _DH_get0_p
%xdefine DH_get0_pqg XCRYPTO_PREFIX %+ _DH_get0_pqg
%xdefine DH_get0_priv_key XCRYPTO_PREFIX %+ _DH_get0_priv_key
%xdefine DH_get0_pub_key XCRYPTO_PREFIX %+ _DH_get0_pub_key
%xdefine DH_get0_q XCRYPTO_PREFIX %+ _DH_get0_q
%xdefine DH_get_ex_data XCRYPTO_PREFIX %+ _DH_get_ex_data
%xdefine DH_get_ex_new_index XCRYPTO_PREFIX %+ _DH_get_ex_new_index
%xdefine DH_marshal_parameters XCRYPTO_PREFIX %+ _DH_marshal_parameters
%xdefine DH_new XCRYPTO_PREFIX %+ _DH_new
%xdefine DH_num_bits XCRYPTO_PREFIX %+ _DH_num_bits
%xdefine DH_parse_parameters XCRYPTO_PREFIX %+ _DH_parse_parameters
%xdefine DH_set0_key XCRYPTO_PREFIX %+ _DH_set0_key
%xdefine DH_set0_pqg XCRYPTO_PREFIX %+ _DH_set0_pqg
%xdefine DH_set_ex_data XCRYPTO_PREFIX %+ _DH_set_ex_data
%xdefine DH_set_length XCRYPTO_PREFIX %+ _DH_set_length
%xdefine DH_size XCRYPTO_PREFIX %+ _DH_size
%xdefine DH_up_ref XCRYPTO_PREFIX %+ _DH_up_ref
%xdefine DHparams_dup XCRYPTO_PREFIX %+ _DHparams_dup
%xdefine DIRECTORYSTRING_free XCRYPTO_PREFIX %+ _DIRECTORYSTRING_free
%xdefine DIRECTORYSTRING_it XCRYPTO_PREFIX %+ _DIRECTORYSTRING_it
%xdefine DIRECTORYSTRING_new XCRYPTO_PREFIX %+ _DIRECTORYSTRING_new
%xdefine DISPLAYTEXT_free XCRYPTO_PREFIX %+ _DISPLAYTEXT_free
%xdefine DISPLAYTEXT_it XCRYPTO_PREFIX %+ _DISPLAYTEXT_it
%xdefine DISPLAYTEXT_new XCRYPTO_PREFIX %+ _DISPLAYTEXT_new
%xdefine DIST_POINT_NAME_free XCRYPTO_PREFIX %+ _DIST_POINT_NAME_free
%xdefine DIST_POINT_NAME_it XCRYPTO_PREFIX %+ _DIST_POINT_NAME_it
%xdefine DIST_POINT_NAME_new XCRYPTO_PREFIX %+ _DIST_POINT_NAME_new
%xdefine DIST_POINT_free XCRYPTO_PREFIX %+ _DIST_POINT_free
%xdefine DIST_POINT_it XCRYPTO_PREFIX %+ _DIST_POINT_it
%xdefine DIST_POINT_new XCRYPTO_PREFIX %+ _DIST_POINT_new
%xdefine DIST_POINT_set_dpname XCRYPTO_PREFIX %+ _DIST_POINT_set_dpname
%xdefine DSA_SIG_free XCRYPTO_PREFIX %+ _DSA_SIG_free
%xdefine DSA_SIG_marshal XCRYPTO_PREFIX %+ _DSA_SIG_marshal
%xdefine DSA_SIG_new XCRYPTO_PREFIX %+ _DSA_SIG_new
%xdefine DSA_SIG_parse XCRYPTO_PREFIX %+ _DSA_SIG_parse
%xdefine DSA_check_signature XCRYPTO_PREFIX %+ _DSA_check_signature
%xdefine DSA_do_check_signature XCRYPTO_PREFIX %+ _DSA_do_check_signature
%xdefine DSA_do_sign XCRYPTO_PREFIX %+ _DSA_do_sign
%xdefine DSA_do_verify XCRYPTO_PREFIX %+ _DSA_do_verify
%xdefine DSA_dup_DH XCRYPTO_PREFIX %+ _DSA_dup_DH
%xdefine DSA_free XCRYPTO_PREFIX %+ _DSA_free
%xdefine DSA_generate_key XCRYPTO_PREFIX %+ _DSA_generate_key
%xdefine DSA_generate_parameters_ex XCRYPTO_PREFIX %+ _DSA_generate_parameters_ex
%xdefine DSA_get0_g XCRYPTO_PREFIX %+ _DSA_get0_g
%xdefine DSA_get0_key XCRYPTO_PREFIX %+ _DSA_get0_key
%xdefine DSA_get0_p XCRYPTO_PREFIX %+ _DSA_get0_p
%xdefine DSA_get0_pqg XCRYPTO_PREFIX %+ _DSA_get0_pqg
%xdefine DSA_get0_priv_key XCRYPTO_PREFIX %+ _DSA_get0_priv_key
%xdefine DSA_get0_pub_key XCRYPTO_PREFIX %+ _DSA_get0_pub_key
%xdefine DSA_get0_q XCRYPTO_PREFIX %+ _DSA_get0_q
%xdefine DSA_get_ex_data XCRYPTO_PREFIX %+ _DSA_get_ex_data
%xdefine DSA_get_ex_new_index XCRYPTO_PREFIX %+ _DSA_get_ex_new_index
%xdefine DSA_marshal_parameters XCRYPTO_PREFIX %+ _DSA_marshal_parameters
%xdefine DSA_marshal_private_key XCRYPTO_PREFIX %+ _DSA_marshal_private_key
%xdefine DSA_marshal_public_key XCRYPTO_PREFIX %+ _DSA_marshal_public_key
%xdefine DSA_new XCRYPTO_PREFIX %+ _DSA_new
%xdefine DSA_parse_parameters XCRYPTO_PREFIX %+ _DSA_parse_parameters
%xdefine DSA_parse_private_key XCRYPTO_PREFIX %+ _DSA_parse_private_key
%xdefine DSA_parse_public_key XCRYPTO_PREFIX %+ _DSA_parse_public_key
%xdefine DSA_set0_key XCRYPTO_PREFIX %+ _DSA_set0_key
%xdefine DSA_set0_pqg XCRYPTO_PREFIX %+ _DSA_set0_pqg
%xdefine DSA_set_ex_data XCRYPTO_PREFIX %+ _DSA_set_ex_data
%xdefine DSA_sign XCRYPTO_PREFIX %+ _DSA_sign
%xdefine DSA_size XCRYPTO_PREFIX %+ _DSA_size
%xdefine DSA_up_ref XCRYPTO_PREFIX %+ _DSA_up_ref
%xdefine DSA_verify XCRYPTO_PREFIX %+ _DSA_verify
%xdefine DSAparams_dup XCRYPTO_PREFIX %+ _DSAparams_dup
%xdefine DTLS_client_method XCRYPTO_PREFIX %+ _DTLS_client_method
%xdefine DTLS_method XCRYPTO_PREFIX %+ _DTLS_method
%xdefine DTLS_server_method XCRYPTO_PREFIX %+ _DTLS_server_method
%xdefine DTLS_with_buffers_method XCRYPTO_PREFIX %+ _DTLS_with_buffers_method
%xdefine DTLSv1_2_client_method XCRYPTO_PREFIX %+ _DTLSv1_2_client_method
%xdefine DTLSv1_2_method XCRYPTO_PREFIX %+ _DTLSv1_2_method
%xdefine DTLSv1_2_server_method XCRYPTO_PREFIX %+ _DTLSv1_2_server_method
%xdefine DTLSv1_client_method XCRYPTO_PREFIX %+ _DTLSv1_client_method
%xdefine DTLSv1_get_timeout XCRYPTO_PREFIX %+ _DTLSv1_get_timeout
%xdefine DTLSv1_handle_timeout XCRYPTO_PREFIX %+ _DTLSv1_handle_timeout
%xdefine DTLSv1_method XCRYPTO_PREFIX %+ _DTLSv1_method
%xdefine DTLSv1_server_method XCRYPTO_PREFIX %+ _DTLSv1_server_method
%xdefine DTLSv1_set_initial_timeout_duration XCRYPTO_PREFIX %+ _DTLSv1_set_initial_timeout_duration
%xdefine DW.ref.__gxx_personality_v0 XCRYPTO_PREFIX %+ _DW.ref.__gxx_personality_v0
%xdefine ECDH_compute_key XCRYPTO_PREFIX %+ _ECDH_compute_key
%xdefine ECDH_compute_key_fips XCRYPTO_PREFIX %+ _ECDH_compute_key_fips
%xdefine ECDSA_SIG_free XCRYPTO_PREFIX %+ _ECDSA_SIG_free
%xdefine ECDSA_SIG_from_bytes XCRYPTO_PREFIX %+ _ECDSA_SIG_from_bytes
%xdefine ECDSA_SIG_get0 XCRYPTO_PREFIX %+ _ECDSA_SIG_get0
%xdefine ECDSA_SIG_get0_r XCRYPTO_PREFIX %+ _ECDSA_SIG_get0_r
%xdefine ECDSA_SIG_get0_s XCRYPTO_PREFIX %+ _ECDSA_SIG_get0_s
%xdefine ECDSA_SIG_marshal XCRYPTO_PREFIX %+ _ECDSA_SIG_marshal
%xdefine ECDSA_SIG_max_len XCRYPTO_PREFIX %+ _ECDSA_SIG_max_len
%xdefine ECDSA_SIG_new XCRYPTO_PREFIX %+ _ECDSA_SIG_new
%xdefine ECDSA_SIG_parse XCRYPTO_PREFIX %+ _ECDSA_SIG_parse
%xdefine ECDSA_SIG_set0 XCRYPTO_PREFIX %+ _ECDSA_SIG_set0
%xdefine ECDSA_SIG_to_bytes XCRYPTO_PREFIX %+ _ECDSA_SIG_to_bytes
%xdefine ECDSA_do_sign XCRYPTO_PREFIX %+ _ECDSA_do_sign
%xdefine ECDSA_do_verify XCRYPTO_PREFIX %+ _ECDSA_do_verify
%xdefine ECDSA_sign XCRYPTO_PREFIX %+ _ECDSA_sign
%xdefine ECDSA_size XCRYPTO_PREFIX %+ _ECDSA_size
%xdefine ECDSA_verify XCRYPTO_PREFIX %+ _ECDSA_verify
%xdefine EC_GFp_mont_method XCRYPTO_PREFIX %+ _EC_GFp_mont_method
%xdefine EC_GFp_nistp224_method XCRYPTO_PREFIX %+ _EC_GFp_nistp224_method
%xdefine EC_GFp_nistp256_method XCRYPTO_PREFIX %+ _EC_GFp_nistp256_method
%xdefine EC_GFp_nistz256_method XCRYPTO_PREFIX %+ _EC_GFp_nistz256_method
%xdefine EC_GROUP_cmp XCRYPTO_PREFIX %+ _EC_GROUP_cmp
%xdefine EC_GROUP_dup XCRYPTO_PREFIX %+ _EC_GROUP_dup
%xdefine EC_GROUP_free XCRYPTO_PREFIX %+ _EC_GROUP_free
%xdefine EC_GROUP_get0_generator XCRYPTO_PREFIX %+ _EC_GROUP_get0_generator
%xdefine EC_GROUP_get0_order XCRYPTO_PREFIX %+ _EC_GROUP_get0_order
%xdefine EC_GROUP_get_cofactor XCRYPTO_PREFIX %+ _EC_GROUP_get_cofactor
%xdefine EC_GROUP_get_curve_GFp XCRYPTO_PREFIX %+ _EC_GROUP_get_curve_GFp
%xdefine EC_GROUP_get_curve_name XCRYPTO_PREFIX %+ _EC_GROUP_get_curve_name
%xdefine EC_GROUP_get_degree XCRYPTO_PREFIX %+ _EC_GROUP_get_degree
%xdefine EC_GROUP_get_order XCRYPTO_PREFIX %+ _EC_GROUP_get_order
%xdefine EC_GROUP_method_of XCRYPTO_PREFIX %+ _EC_GROUP_method_of
%xdefine EC_GROUP_new_by_curve_name XCRYPTO_PREFIX %+ _EC_GROUP_new_by_curve_name
%xdefine EC_GROUP_new_curve_GFp XCRYPTO_PREFIX %+ _EC_GROUP_new_curve_GFp
%xdefine EC_GROUP_order_bits XCRYPTO_PREFIX %+ _EC_GROUP_order_bits
%xdefine EC_GROUP_set_asn1_flag XCRYPTO_PREFIX %+ _EC_GROUP_set_asn1_flag
%xdefine EC_GROUP_set_generator XCRYPTO_PREFIX %+ _EC_GROUP_set_generator
%xdefine EC_GROUP_set_point_conversion_form XCRYPTO_PREFIX %+ _EC_GROUP_set_point_conversion_form
%xdefine EC_KEY_check_fips XCRYPTO_PREFIX %+ _EC_KEY_check_fips
%xdefine EC_KEY_check_key XCRYPTO_PREFIX %+ _EC_KEY_check_key
%xdefine EC_KEY_derive_from_secret XCRYPTO_PREFIX %+ _EC_KEY_derive_from_secret
%xdefine EC_KEY_dup XCRYPTO_PREFIX %+ _EC_KEY_dup
%xdefine EC_KEY_free XCRYPTO_PREFIX %+ _EC_KEY_free
%xdefine EC_KEY_generate_key XCRYPTO_PREFIX %+ _EC_KEY_generate_key
%xdefine EC_KEY_generate_key_fips XCRYPTO_PREFIX %+ _EC_KEY_generate_key_fips
%xdefine EC_KEY_get0_group XCRYPTO_PREFIX %+ _EC_KEY_get0_group
%xdefine EC_KEY_get0_private_key XCRYPTO_PREFIX %+ _EC_KEY_get0_private_key
%xdefine EC_KEY_get0_public_key XCRYPTO_PREFIX %+ _EC_KEY_get0_public_key
%xdefine EC_KEY_get_conv_form XCRYPTO_PREFIX %+ _EC_KEY_get_conv_form
%xdefine EC_KEY_get_enc_flags XCRYPTO_PREFIX %+ _EC_KEY_get_enc_flags
%xdefine EC_KEY_get_ex_data XCRYPTO_PREFIX %+ _EC_KEY_get_ex_data
%xdefine EC_KEY_get_ex_new_index XCRYPTO_PREFIX %+ _EC_KEY_get_ex_new_index
%xdefine EC_KEY_is_opaque XCRYPTO_PREFIX %+ _EC_KEY_is_opaque
%xdefine EC_KEY_key2buf XCRYPTO_PREFIX %+ _EC_KEY_key2buf
%xdefine EC_KEY_marshal_curve_name XCRYPTO_PREFIX %+ _EC_KEY_marshal_curve_name
%xdefine EC_KEY_marshal_private_key XCRYPTO_PREFIX %+ _EC_KEY_marshal_private_key
%xdefine EC_KEY_new XCRYPTO_PREFIX %+ _EC_KEY_new
%xdefine EC_KEY_new_by_curve_name XCRYPTO_PREFIX %+ _EC_KEY_new_by_curve_name
%xdefine EC_KEY_new_method XCRYPTO_PREFIX %+ _EC_KEY_new_method
%xdefine EC_KEY_parse_curve_name XCRYPTO_PREFIX %+ _EC_KEY_parse_curve_name
%xdefine EC_KEY_parse_parameters XCRYPTO_PREFIX %+ _EC_KEY_parse_parameters
%xdefine EC_KEY_parse_private_key XCRYPTO_PREFIX %+ _EC_KEY_parse_private_key
%xdefine EC_KEY_set_asn1_flag XCRYPTO_PREFIX %+ _EC_KEY_set_asn1_flag
%xdefine EC_KEY_set_conv_form XCRYPTO_PREFIX %+ _EC_KEY_set_conv_form
%xdefine EC_KEY_set_enc_flags XCRYPTO_PREFIX %+ _EC_KEY_set_enc_flags
%xdefine EC_KEY_set_ex_data XCRYPTO_PREFIX %+ _EC_KEY_set_ex_data
%xdefine EC_KEY_set_group XCRYPTO_PREFIX %+ _EC_KEY_set_group
%xdefine EC_KEY_set_private_key XCRYPTO_PREFIX %+ _EC_KEY_set_private_key
%xdefine EC_KEY_set_public_key XCRYPTO_PREFIX %+ _EC_KEY_set_public_key
%xdefine EC_KEY_set_public_key_affine_coordinates XCRYPTO_PREFIX %+ _EC_KEY_set_public_key_affine_coordinates
%xdefine EC_KEY_up_ref XCRYPTO_PREFIX %+ _EC_KEY_up_ref
%xdefine EC_METHOD_get_field_type XCRYPTO_PREFIX %+ _EC_METHOD_get_field_type
%xdefine EC_POINT_add XCRYPTO_PREFIX %+ _EC_POINT_add
%xdefine EC_POINT_clear_free XCRYPTO_PREFIX %+ _EC_POINT_clear_free
%xdefine EC_POINT_cmp XCRYPTO_PREFIX %+ _EC_POINT_cmp
%xdefine EC_POINT_copy XCRYPTO_PREFIX %+ _EC_POINT_copy
%xdefine EC_POINT_dbl XCRYPTO_PREFIX %+ _EC_POINT_dbl
%xdefine EC_POINT_dup XCRYPTO_PREFIX %+ _EC_POINT_dup
%xdefine EC_POINT_free XCRYPTO_PREFIX %+ _EC_POINT_free
%xdefine EC_POINT_get_affine_coordinates_GFp XCRYPTO_PREFIX %+ _EC_POINT_get_affine_coordinates_GFp
%xdefine EC_POINT_invert XCRYPTO_PREFIX %+ _EC_POINT_invert
%xdefine EC_POINT_is_at_infinity XCRYPTO_PREFIX %+ _EC_POINT_is_at_infinity
%xdefine EC_POINT_is_on_curve XCRYPTO_PREFIX %+ _EC_POINT_is_on_curve
%xdefine EC_POINT_mul XCRYPTO_PREFIX %+ _EC_POINT_mul
%xdefine EC_POINT_new XCRYPTO_PREFIX %+ _EC_POINT_new
%xdefine EC_POINT_oct2point XCRYPTO_PREFIX %+ _EC_POINT_oct2point
%xdefine EC_POINT_point2cbb XCRYPTO_PREFIX %+ _EC_POINT_point2cbb
%xdefine EC_POINT_point2oct XCRYPTO_PREFIX %+ _EC_POINT_point2oct
%xdefine EC_POINT_set_affine_coordinates_GFp XCRYPTO_PREFIX %+ _EC_POINT_set_affine_coordinates_GFp
%xdefine EC_POINT_set_compressed_coordinates_GFp XCRYPTO_PREFIX %+ _EC_POINT_set_compressed_coordinates_GFp
%xdefine EC_POINT_set_to_infinity XCRYPTO_PREFIX %+ _EC_POINT_set_to_infinity
%xdefine EC_curve_nid2nist XCRYPTO_PREFIX %+ _EC_curve_nid2nist
%xdefine EC_curve_nist2nid XCRYPTO_PREFIX %+ _EC_curve_nist2nid
%xdefine EC_get_builtin_curves XCRYPTO_PREFIX %+ _EC_get_builtin_curves
%xdefine ED25519_keypair XCRYPTO_PREFIX %+ _ED25519_keypair
%xdefine ED25519_keypair_from_seed XCRYPTO_PREFIX %+ _ED25519_keypair_from_seed
%xdefine ED25519_sign XCRYPTO_PREFIX %+ _ED25519_sign
%xdefine ED25519_verify XCRYPTO_PREFIX %+ _ED25519_verify
%xdefine EDIPARTYNAME_free XCRYPTO_PREFIX %+ _EDIPARTYNAME_free
%xdefine EDIPARTYNAME_it XCRYPTO_PREFIX %+ _EDIPARTYNAME_it
%xdefine EDIPARTYNAME_new XCRYPTO_PREFIX %+ _EDIPARTYNAME_new
%xdefine ENGINE_free XCRYPTO_PREFIX %+ _ENGINE_free
%xdefine ENGINE_get_ECDSA_method XCRYPTO_PREFIX %+ _ENGINE_get_ECDSA_method
%xdefine ENGINE_get_RSA_method XCRYPTO_PREFIX %+ _ENGINE_get_RSA_method
%xdefine ENGINE_load_builtin_engines XCRYPTO_PREFIX %+ _ENGINE_load_builtin_engines
%xdefine ENGINE_new XCRYPTO_PREFIX %+ _ENGINE_new
%xdefine ENGINE_register_all_complete XCRYPTO_PREFIX %+ _ENGINE_register_all_complete
%xdefine ENGINE_set_ECDSA_method XCRYPTO_PREFIX %+ _ENGINE_set_ECDSA_method
%xdefine ENGINE_set_RSA_method XCRYPTO_PREFIX %+ _ENGINE_set_RSA_method
%xdefine ERR_SAVE_STATE_free XCRYPTO_PREFIX %+ _ERR_SAVE_STATE_free
%xdefine ERR_add_error_data XCRYPTO_PREFIX %+ _ERR_add_error_data
%xdefine ERR_add_error_dataf XCRYPTO_PREFIX %+ _ERR_add_error_dataf
%xdefine ERR_clear_error XCRYPTO_PREFIX %+ _ERR_clear_error
%xdefine ERR_clear_system_error XCRYPTO_PREFIX %+ _ERR_clear_system_error
%xdefine ERR_error_string XCRYPTO_PREFIX %+ _ERR_error_string
%xdefine ERR_error_string_n XCRYPTO_PREFIX %+ _ERR_error_string_n
%xdefine ERR_free_strings XCRYPTO_PREFIX %+ _ERR_free_strings
%xdefine ERR_func_error_string XCRYPTO_PREFIX %+ _ERR_func_error_string
%xdefine ERR_get_error XCRYPTO_PREFIX %+ _ERR_get_error
%xdefine ERR_get_error_line XCRYPTO_PREFIX %+ _ERR_get_error_line
%xdefine ERR_get_error_line_data XCRYPTO_PREFIX %+ _ERR_get_error_line_data
%xdefine ERR_get_next_error_library XCRYPTO_PREFIX %+ _ERR_get_next_error_library
%xdefine ERR_lib_error_string XCRYPTO_PREFIX %+ _ERR_lib_error_string
%xdefine ERR_load_BIO_strings XCRYPTO_PREFIX %+ _ERR_load_BIO_strings
%xdefine ERR_load_ERR_strings XCRYPTO_PREFIX %+ _ERR_load_ERR_strings
%xdefine ERR_load_RAND_strings XCRYPTO_PREFIX %+ _ERR_load_RAND_strings
%xdefine ERR_load_SSL_strings XCRYPTO_PREFIX %+ _ERR_load_SSL_strings
%xdefine ERR_load_crypto_strings XCRYPTO_PREFIX %+ _ERR_load_crypto_strings
%xdefine ERR_peek_error XCRYPTO_PREFIX %+ _ERR_peek_error
%xdefine ERR_peek_error_line XCRYPTO_PREFIX %+ _ERR_peek_error_line
%xdefine ERR_peek_error_line_data XCRYPTO_PREFIX %+ _ERR_peek_error_line_data
%xdefine ERR_peek_last_error XCRYPTO_PREFIX %+ _ERR_peek_last_error
%xdefine ERR_peek_last_error_line XCRYPTO_PREFIX %+ _ERR_peek_last_error_line
%xdefine ERR_peek_last_error_line_data XCRYPTO_PREFIX %+ _ERR_peek_last_error_line_data
%xdefine ERR_pop_to_mark XCRYPTO_PREFIX %+ _ERR_pop_to_mark
%xdefine ERR_print_errors XCRYPTO_PREFIX %+ _ERR_print_errors
%xdefine ERR_print_errors_cb XCRYPTO_PREFIX %+ _ERR_print_errors_cb
%xdefine ERR_print_errors_fp XCRYPTO_PREFIX %+ _ERR_print_errors_fp
%xdefine ERR_put_error XCRYPTO_PREFIX %+ _ERR_put_error
%xdefine ERR_reason_error_string XCRYPTO_PREFIX %+ _ERR_reason_error_string
%xdefine ERR_remove_state XCRYPTO_PREFIX %+ _ERR_remove_state
%xdefine ERR_remove_thread_state XCRYPTO_PREFIX %+ _ERR_remove_thread_state
%xdefine ERR_restore_state XCRYPTO_PREFIX %+ _ERR_restore_state
%xdefine ERR_save_state XCRYPTO_PREFIX %+ _ERR_save_state
%xdefine ERR_set_mark XCRYPTO_PREFIX %+ _ERR_set_mark
%xdefine EVP_AEAD_CTX_aead XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_aead
%xdefine EVP_AEAD_CTX_cleanup XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_cleanup
%xdefine EVP_AEAD_CTX_free XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_free
%xdefine EVP_AEAD_CTX_get_iv XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_get_iv
%xdefine EVP_AEAD_CTX_init XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_init
%xdefine EVP_AEAD_CTX_init_with_direction XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_init_with_direction
%xdefine EVP_AEAD_CTX_new XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_new
%xdefine EVP_AEAD_CTX_open XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_open
%xdefine EVP_AEAD_CTX_open_gather XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_open_gather
%xdefine EVP_AEAD_CTX_seal XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_seal
%xdefine EVP_AEAD_CTX_seal_scatter XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_seal_scatter
%xdefine EVP_AEAD_CTX_tag_len XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_tag_len
%xdefine EVP_AEAD_CTX_zero XCRYPTO_PREFIX %+ _EVP_AEAD_CTX_zero
%xdefine EVP_AEAD_key_length XCRYPTO_PREFIX %+ _EVP_AEAD_key_length
%xdefine EVP_AEAD_max_overhead XCRYPTO_PREFIX %+ _EVP_AEAD_max_overhead
%xdefine EVP_AEAD_max_tag_len XCRYPTO_PREFIX %+ _EVP_AEAD_max_tag_len
%xdefine EVP_AEAD_nonce_length XCRYPTO_PREFIX %+ _EVP_AEAD_nonce_length
%xdefine EVP_BytesToKey XCRYPTO_PREFIX %+ _EVP_BytesToKey
%xdefine EVP_CIPHER_CTX_block_size XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_block_size
%xdefine EVP_CIPHER_CTX_cipher XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_cipher
%xdefine EVP_CIPHER_CTX_cleanup XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_cleanup
%xdefine EVP_CIPHER_CTX_copy XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_copy
%xdefine EVP_CIPHER_CTX_ctrl XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_ctrl
%xdefine EVP_CIPHER_CTX_encrypting XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_encrypting
%xdefine EVP_CIPHER_CTX_flags XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_flags
%xdefine EVP_CIPHER_CTX_free XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_free
%xdefine EVP_CIPHER_CTX_get_app_data XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_get_app_data
%xdefine EVP_CIPHER_CTX_init XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_init
%xdefine EVP_CIPHER_CTX_iv_length XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_iv_length
%xdefine EVP_CIPHER_CTX_key_length XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_key_length
%xdefine EVP_CIPHER_CTX_mode XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_mode
%xdefine EVP_CIPHER_CTX_new XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_new
%xdefine EVP_CIPHER_CTX_nid XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_nid
%xdefine EVP_CIPHER_CTX_reset XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_reset
%xdefine EVP_CIPHER_CTX_set_app_data XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_app_data
%xdefine EVP_CIPHER_CTX_set_flags XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_flags
%xdefine EVP_CIPHER_CTX_set_key_length XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_key_length
%xdefine EVP_CIPHER_CTX_set_padding XCRYPTO_PREFIX %+ _EVP_CIPHER_CTX_set_padding
%xdefine EVP_CIPHER_block_size XCRYPTO_PREFIX %+ _EVP_CIPHER_block_size
%xdefine EVP_CIPHER_flags XCRYPTO_PREFIX %+ _EVP_CIPHER_flags
%xdefine EVP_CIPHER_iv_length XCRYPTO_PREFIX %+ _EVP_CIPHER_iv_length
%xdefine EVP_CIPHER_key_length XCRYPTO_PREFIX %+ _EVP_CIPHER_key_length
%xdefine EVP_CIPHER_mode XCRYPTO_PREFIX %+ _EVP_CIPHER_mode
%xdefine EVP_CIPHER_nid XCRYPTO_PREFIX %+ _EVP_CIPHER_nid
%xdefine EVP_Cipher XCRYPTO_PREFIX %+ _EVP_Cipher
%xdefine EVP_CipherFinal_ex XCRYPTO_PREFIX %+ _EVP_CipherFinal_ex
%xdefine EVP_CipherInit XCRYPTO_PREFIX %+ _EVP_CipherInit
%xdefine EVP_CipherInit_ex XCRYPTO_PREFIX %+ _EVP_CipherInit_ex
%xdefine EVP_CipherUpdate XCRYPTO_PREFIX %+ _EVP_CipherUpdate
%xdefine EVP_DecodeBase64 XCRYPTO_PREFIX %+ _EVP_DecodeBase64
%xdefine EVP_DecodeBlock XCRYPTO_PREFIX %+ _EVP_DecodeBlock
%xdefine EVP_DecodeFinal XCRYPTO_PREFIX %+ _EVP_DecodeFinal
%xdefine EVP_DecodeInit XCRYPTO_PREFIX %+ _EVP_DecodeInit
%xdefine EVP_DecodeUpdate XCRYPTO_PREFIX %+ _EVP_DecodeUpdate
%xdefine EVP_DecodedLength XCRYPTO_PREFIX %+ _EVP_DecodedLength
%xdefine EVP_DecryptFinal_ex XCRYPTO_PREFIX %+ _EVP_DecryptFinal_ex
%xdefine EVP_DecryptInit XCRYPTO_PREFIX %+ _EVP_DecryptInit
%xdefine EVP_DecryptInit_ex XCRYPTO_PREFIX %+ _EVP_DecryptInit_ex
%xdefine EVP_DecryptUpdate XCRYPTO_PREFIX %+ _EVP_DecryptUpdate
%xdefine EVP_Digest XCRYPTO_PREFIX %+ _EVP_Digest
%xdefine EVP_DigestFinal XCRYPTO_PREFIX %+ _EVP_DigestFinal
%xdefine EVP_DigestFinalXOF XCRYPTO_PREFIX %+ _EVP_DigestFinalXOF
%xdefine EVP_DigestFinal_ex XCRYPTO_PREFIX %+ _EVP_DigestFinal_ex
%xdefine EVP_DigestInit XCRYPTO_PREFIX %+ _EVP_DigestInit
%xdefine EVP_DigestInit_ex XCRYPTO_PREFIX %+ _EVP_DigestInit_ex
%xdefine EVP_DigestSign XCRYPTO_PREFIX %+ _EVP_DigestSign
%xdefine EVP_DigestSignFinal XCRYPTO_PREFIX %+ _EVP_DigestSignFinal
%xdefine EVP_DigestSignInit XCRYPTO_PREFIX %+ _EVP_DigestSignInit
%xdefine EVP_DigestSignUpdate XCRYPTO_PREFIX %+ _EVP_DigestSignUpdate
%xdefine EVP_DigestUpdate XCRYPTO_PREFIX %+ _EVP_DigestUpdate
%xdefine EVP_DigestVerify XCRYPTO_PREFIX %+ _EVP_DigestVerify
%xdefine EVP_DigestVerifyFinal XCRYPTO_PREFIX %+ _EVP_DigestVerifyFinal
%xdefine EVP_DigestVerifyInit XCRYPTO_PREFIX %+ _EVP_DigestVerifyInit
%xdefine EVP_DigestVerifyUpdate XCRYPTO_PREFIX %+ _EVP_DigestVerifyUpdate
%xdefine EVP_EncodeBlock XCRYPTO_PREFIX %+ _EVP_EncodeBlock
%xdefine EVP_EncodeFinal XCRYPTO_PREFIX %+ _EVP_EncodeFinal
%xdefine EVP_EncodeInit XCRYPTO_PREFIX %+ _EVP_EncodeInit
%xdefine EVP_EncodeUpdate XCRYPTO_PREFIX %+ _EVP_EncodeUpdate
%xdefine EVP_EncodedLength XCRYPTO_PREFIX %+ _EVP_EncodedLength
%xdefine EVP_EncryptFinal_ex XCRYPTO_PREFIX %+ _EVP_EncryptFinal_ex
%xdefine EVP_EncryptInit XCRYPTO_PREFIX %+ _EVP_EncryptInit
%xdefine EVP_EncryptInit_ex XCRYPTO_PREFIX %+ _EVP_EncryptInit_ex
%xdefine EVP_EncryptUpdate XCRYPTO_PREFIX %+ _EVP_EncryptUpdate
%xdefine EVP_MD_CTX_block_size XCRYPTO_PREFIX %+ _EVP_MD_CTX_block_size
%xdefine EVP_MD_CTX_cleanup XCRYPTO_PREFIX %+ _EVP_MD_CTX_cleanup
%xdefine EVP_MD_CTX_copy XCRYPTO_PREFIX %+ _EVP_MD_CTX_copy
%xdefine EVP_MD_CTX_copy_ex XCRYPTO_PREFIX %+ _EVP_MD_CTX_copy_ex
%xdefine EVP_MD_CTX_create XCRYPTO_PREFIX %+ _EVP_MD_CTX_create
%xdefine EVP_MD_CTX_destroy XCRYPTO_PREFIX %+ _EVP_MD_CTX_destroy
%xdefine EVP_MD_CTX_free XCRYPTO_PREFIX %+ _EVP_MD_CTX_free
%xdefine EVP_MD_CTX_init XCRYPTO_PREFIX %+ _EVP_MD_CTX_init
%xdefine EVP_MD_CTX_md XCRYPTO_PREFIX %+ _EVP_MD_CTX_md
%xdefine EVP_MD_CTX_new XCRYPTO_PREFIX %+ _EVP_MD_CTX_new
%xdefine EVP_MD_CTX_reset XCRYPTO_PREFIX %+ _EVP_MD_CTX_reset
%xdefine EVP_MD_CTX_size XCRYPTO_PREFIX %+ _EVP_MD_CTX_size
%xdefine EVP_MD_CTX_type XCRYPTO_PREFIX %+ _EVP_MD_CTX_type
%xdefine EVP_MD_block_size XCRYPTO_PREFIX %+ _EVP_MD_block_size
%xdefine EVP_MD_flags XCRYPTO_PREFIX %+ _EVP_MD_flags
%xdefine EVP_MD_meth_get_flags XCRYPTO_PREFIX %+ _EVP_MD_meth_get_flags
%xdefine EVP_MD_size XCRYPTO_PREFIX %+ _EVP_MD_size
%xdefine EVP_MD_type XCRYPTO_PREFIX %+ _EVP_MD_type
%xdefine EVP_PBE_scrypt XCRYPTO_PREFIX %+ _EVP_PBE_scrypt
%xdefine EVP_PKCS82PKEY XCRYPTO_PREFIX %+ _EVP_PKCS82PKEY
%xdefine EVP_PKEY2PKCS8 XCRYPTO_PREFIX %+ _EVP_PKEY2PKCS8
%xdefine EVP_PKEY_CTX_ctrl XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_ctrl
%xdefine EVP_PKEY_CTX_dup XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_dup
%xdefine EVP_PKEY_CTX_free XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_free
%xdefine EVP_PKEY_CTX_get0_pkey XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get0_pkey
%xdefine EVP_PKEY_CTX_get0_rsa_oaep_label XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get0_rsa_oaep_label
%xdefine EVP_PKEY_CTX_get_rsa_mgf1_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_mgf1_md
%xdefine EVP_PKEY_CTX_get_rsa_oaep_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_oaep_md
%xdefine EVP_PKEY_CTX_get_rsa_padding XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_padding
%xdefine EVP_PKEY_CTX_get_rsa_pss_saltlen XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_rsa_pss_saltlen
%xdefine EVP_PKEY_CTX_get_signature_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_get_signature_md
%xdefine EVP_PKEY_CTX_new XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_new
%xdefine EVP_PKEY_CTX_new_id XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_new_id
%xdefine EVP_PKEY_CTX_set0_rsa_oaep_label XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set0_rsa_oaep_label
%xdefine EVP_PKEY_CTX_set_ec_param_enc XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_ec_param_enc
%xdefine EVP_PKEY_CTX_set_ec_paramgen_curve_nid XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_ec_paramgen_curve_nid
%xdefine EVP_PKEY_CTX_set_rsa_keygen_bits XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_keygen_bits
%xdefine EVP_PKEY_CTX_set_rsa_keygen_pubexp XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_keygen_pubexp
%xdefine EVP_PKEY_CTX_set_rsa_mgf1_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_mgf1_md
%xdefine EVP_PKEY_CTX_set_rsa_oaep_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_oaep_md
%xdefine EVP_PKEY_CTX_set_rsa_padding XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_padding
%xdefine EVP_PKEY_CTX_set_rsa_pss_keygen_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_keygen_md
%xdefine EVP_PKEY_CTX_set_rsa_pss_keygen_mgf1_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_keygen_mgf1_md
%xdefine EVP_PKEY_CTX_set_rsa_pss_keygen_saltlen XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_keygen_saltlen
%xdefine EVP_PKEY_CTX_set_rsa_pss_saltlen XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_rsa_pss_saltlen
%xdefine EVP_PKEY_CTX_set_signature_md XCRYPTO_PREFIX %+ _EVP_PKEY_CTX_set_signature_md
%xdefine EVP_PKEY_assign XCRYPTO_PREFIX %+ _EVP_PKEY_assign
%xdefine EVP_PKEY_assign_DSA XCRYPTO_PREFIX %+ _EVP_PKEY_assign_DSA
%xdefine EVP_PKEY_assign_EC_KEY XCRYPTO_PREFIX %+ _EVP_PKEY_assign_EC_KEY
%xdefine EVP_PKEY_assign_RSA XCRYPTO_PREFIX %+ _EVP_PKEY_assign_RSA
%xdefine EVP_PKEY_base_id XCRYPTO_PREFIX %+ _EVP_PKEY_base_id
%xdefine EVP_PKEY_bits XCRYPTO_PREFIX %+ _EVP_PKEY_bits
%xdefine EVP_PKEY_cmp XCRYPTO_PREFIX %+ _EVP_PKEY_cmp
%xdefine EVP_PKEY_cmp_parameters XCRYPTO_PREFIX %+ _EVP_PKEY_cmp_parameters
%xdefine EVP_PKEY_copy_parameters XCRYPTO_PREFIX %+ _EVP_PKEY_copy_parameters
%xdefine EVP_PKEY_decrypt XCRYPTO_PREFIX %+ _EVP_PKEY_decrypt
%xdefine EVP_PKEY_decrypt_init XCRYPTO_PREFIX %+ _EVP_PKEY_decrypt_init
%xdefine EVP_PKEY_derive XCRYPTO_PREFIX %+ _EVP_PKEY_derive
%xdefine EVP_PKEY_derive_init XCRYPTO_PREFIX %+ _EVP_PKEY_derive_init
%xdefine EVP_PKEY_derive_set_peer XCRYPTO_PREFIX %+ _EVP_PKEY_derive_set_peer
%xdefine EVP_PKEY_encrypt XCRYPTO_PREFIX %+ _EVP_PKEY_encrypt
%xdefine EVP_PKEY_encrypt_init XCRYPTO_PREFIX %+ _EVP_PKEY_encrypt_init
%xdefine EVP_PKEY_free XCRYPTO_PREFIX %+ _EVP_PKEY_free
%xdefine EVP_PKEY_get0_DH XCRYPTO_PREFIX %+ _EVP_PKEY_get0_DH
%xdefine EVP_PKEY_get0_DSA XCRYPTO_PREFIX %+ _EVP_PKEY_get0_DSA
%xdefine EVP_PKEY_get0_EC_KEY XCRYPTO_PREFIX %+ _EVP_PKEY_get0_EC_KEY
%xdefine EVP_PKEY_get0_RSA XCRYPTO_PREFIX %+ _EVP_PKEY_get0_RSA
%xdefine EVP_PKEY_get1_DH XCRYPTO_PREFIX %+ _EVP_PKEY_get1_DH
%xdefine EVP_PKEY_get1_DSA XCRYPTO_PREFIX %+ _EVP_PKEY_get1_DSA
%xdefine EVP_PKEY_get1_EC_KEY XCRYPTO_PREFIX %+ _EVP_PKEY_get1_EC_KEY
%xdefine EVP_PKEY_get1_RSA XCRYPTO_PREFIX %+ _EVP_PKEY_get1_RSA
%xdefine EVP_PKEY_get1_tls_encodedpoint XCRYPTO_PREFIX %+ _EVP_PKEY_get1_tls_encodedpoint
%xdefine EVP_PKEY_get_raw_private_key XCRYPTO_PREFIX %+ _EVP_PKEY_get_raw_private_key
%xdefine EVP_PKEY_get_raw_public_key XCRYPTO_PREFIX %+ _EVP_PKEY_get_raw_public_key
%xdefine EVP_PKEY_id XCRYPTO_PREFIX %+ _EVP_PKEY_id
%xdefine EVP_PKEY_is_opaque XCRYPTO_PREFIX %+ _EVP_PKEY_is_opaque
%xdefine EVP_PKEY_keygen XCRYPTO_PREFIX %+ _EVP_PKEY_keygen
%xdefine EVP_PKEY_keygen_init XCRYPTO_PREFIX %+ _EVP_PKEY_keygen_init
%xdefine EVP_PKEY_missing_parameters XCRYPTO_PREFIX %+ _EVP_PKEY_missing_parameters
%xdefine EVP_PKEY_new XCRYPTO_PREFIX %+ _EVP_PKEY_new
%xdefine EVP_PKEY_new_raw_private_key XCRYPTO_PREFIX %+ _EVP_PKEY_new_raw_private_key
%xdefine EVP_PKEY_new_raw_public_key XCRYPTO_PREFIX %+ _EVP_PKEY_new_raw_public_key
%xdefine EVP_PKEY_paramgen XCRYPTO_PREFIX %+ _EVP_PKEY_paramgen
%xdefine EVP_PKEY_paramgen_init XCRYPTO_PREFIX %+ _EVP_PKEY_paramgen_init
%xdefine EVP_PKEY_print_params XCRYPTO_PREFIX %+ _EVP_PKEY_print_params
%xdefine EVP_PKEY_print_private XCRYPTO_PREFIX %+ _EVP_PKEY_print_private
%xdefine EVP_PKEY_print_public XCRYPTO_PREFIX %+ _EVP_PKEY_print_public
%xdefine EVP_PKEY_set1_DSA XCRYPTO_PREFIX %+ _EVP_PKEY_set1_DSA
%xdefine EVP_PKEY_set1_EC_KEY XCRYPTO_PREFIX %+ _EVP_PKEY_set1_EC_KEY
%xdefine EVP_PKEY_set1_RSA XCRYPTO_PREFIX %+ _EVP_PKEY_set1_RSA
%xdefine EVP_PKEY_set1_tls_encodedpoint XCRYPTO_PREFIX %+ _EVP_PKEY_set1_tls_encodedpoint
%xdefine EVP_PKEY_set_type XCRYPTO_PREFIX %+ _EVP_PKEY_set_type
%xdefine EVP_PKEY_sign XCRYPTO_PREFIX %+ _EVP_PKEY_sign
%xdefine EVP_PKEY_sign_init XCRYPTO_PREFIX %+ _EVP_PKEY_sign_init
%xdefine EVP_PKEY_size XCRYPTO_PREFIX %+ _EVP_PKEY_size
%xdefine EVP_PKEY_type XCRYPTO_PREFIX %+ _EVP_PKEY_type
%xdefine EVP_PKEY_up_ref XCRYPTO_PREFIX %+ _EVP_PKEY_up_ref
%xdefine EVP_PKEY_verify XCRYPTO_PREFIX %+ _EVP_PKEY_verify
%xdefine EVP_PKEY_verify_init XCRYPTO_PREFIX %+ _EVP_PKEY_verify_init
%xdefine EVP_PKEY_verify_recover XCRYPTO_PREFIX %+ _EVP_PKEY_verify_recover
%xdefine EVP_PKEY_verify_recover_init XCRYPTO_PREFIX %+ _EVP_PKEY_verify_recover_init
%xdefine EVP_SignFinal XCRYPTO_PREFIX %+ _EVP_SignFinal
%xdefine EVP_SignInit XCRYPTO_PREFIX %+ _EVP_SignInit
%xdefine EVP_SignInit_ex XCRYPTO_PREFIX %+ _EVP_SignInit_ex
%xdefine EVP_SignUpdate XCRYPTO_PREFIX %+ _EVP_SignUpdate
%xdefine EVP_VerifyFinal XCRYPTO_PREFIX %+ _EVP_VerifyFinal
%xdefine EVP_VerifyInit XCRYPTO_PREFIX %+ _EVP_VerifyInit
%xdefine EVP_VerifyInit_ex XCRYPTO_PREFIX %+ _EVP_VerifyInit_ex
%xdefine EVP_VerifyUpdate XCRYPTO_PREFIX %+ _EVP_VerifyUpdate
%xdefine EVP_add_cipher_alias XCRYPTO_PREFIX %+ _EVP_add_cipher_alias
%xdefine EVP_add_digest XCRYPTO_PREFIX %+ _EVP_add_digest
%xdefine EVP_aead_aes_128_cbc_sha1_tls XCRYPTO_PREFIX %+ _EVP_aead_aes_128_cbc_sha1_tls
%xdefine EVP_aead_aes_128_cbc_sha1_tls_implicit_iv XCRYPTO_PREFIX %+ _EVP_aead_aes_128_cbc_sha1_tls_implicit_iv
%xdefine EVP_aead_aes_128_cbc_sha256_tls XCRYPTO_PREFIX %+ _EVP_aead_aes_128_cbc_sha256_tls
%xdefine EVP_aead_aes_128_ccm_bluetooth XCRYPTO_PREFIX %+ _EVP_aead_aes_128_ccm_bluetooth
%xdefine EVP_aead_aes_128_ccm_bluetooth_8 XCRYPTO_PREFIX %+ _EVP_aead_aes_128_ccm_bluetooth_8
%xdefine EVP_aead_aes_128_ctr_hmac_sha256 XCRYPTO_PREFIX %+ _EVP_aead_aes_128_ctr_hmac_sha256
%xdefine EVP_aead_aes_128_gcm XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm
%xdefine EVP_aead_aes_128_gcm_siv XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm_siv
%xdefine EVP_aead_aes_128_gcm_tls12 XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm_tls12
%xdefine EVP_aead_aes_128_gcm_tls13 XCRYPTO_PREFIX %+ _EVP_aead_aes_128_gcm_tls13
%xdefine EVP_aead_aes_192_gcm XCRYPTO_PREFIX %+ _EVP_aead_aes_192_gcm
%xdefine EVP_aead_aes_256_cbc_sha1_tls XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha1_tls
%xdefine EVP_aead_aes_256_cbc_sha1_tls_implicit_iv XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha1_tls_implicit_iv
%xdefine EVP_aead_aes_256_cbc_sha256_tls XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha256_tls
%xdefine EVP_aead_aes_256_cbc_sha384_tls XCRYPTO_PREFIX %+ _EVP_aead_aes_256_cbc_sha384_tls
%xdefine EVP_aead_aes_256_ctr_hmac_sha256 XCRYPTO_PREFIX %+ _EVP_aead_aes_256_ctr_hmac_sha256
%xdefine EVP_aead_aes_256_gcm XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm
%xdefine EVP_aead_aes_256_gcm_siv XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm_siv
%xdefine EVP_aead_aes_256_gcm_tls12 XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm_tls12
%xdefine EVP_aead_aes_256_gcm_tls13 XCRYPTO_PREFIX %+ _EVP_aead_aes_256_gcm_tls13
%xdefine EVP_aead_chacha20_poly1305 XCRYPTO_PREFIX %+ _EVP_aead_chacha20_poly1305
%xdefine EVP_aead_des_ede3_cbc_sha1_tls XCRYPTO_PREFIX %+ _EVP_aead_des_ede3_cbc_sha1_tls
%xdefine EVP_aead_des_ede3_cbc_sha1_tls_implicit_iv XCRYPTO_PREFIX %+ _EVP_aead_des_ede3_cbc_sha1_tls_implicit_iv
%xdefine EVP_aead_null_sha1_tls XCRYPTO_PREFIX %+ _EVP_aead_null_sha1_tls
%xdefine EVP_aead_xchacha20_poly1305 XCRYPTO_PREFIX %+ _EVP_aead_xchacha20_poly1305
%xdefine EVP_aes_128_cbc XCRYPTO_PREFIX %+ _EVP_aes_128_cbc
%xdefine EVP_aes_128_ctr XCRYPTO_PREFIX %+ _EVP_aes_128_ctr
%xdefine EVP_aes_128_ecb XCRYPTO_PREFIX %+ _EVP_aes_128_ecb
%xdefine EVP_aes_128_gcm XCRYPTO_PREFIX %+ _EVP_aes_128_gcm
%xdefine EVP_aes_128_ofb XCRYPTO_PREFIX %+ _EVP_aes_128_ofb
%xdefine EVP_aes_192_cbc XCRYPTO_PREFIX %+ _EVP_aes_192_cbc
%xdefine EVP_aes_192_ctr XCRYPTO_PREFIX %+ _EVP_aes_192_ctr
%xdefine EVP_aes_192_ecb XCRYPTO_PREFIX %+ _EVP_aes_192_ecb
%xdefine EVP_aes_192_gcm XCRYPTO_PREFIX %+ _EVP_aes_192_gcm
%xdefine EVP_aes_192_ofb XCRYPTO_PREFIX %+ _EVP_aes_192_ofb
%xdefine EVP_aes_256_cbc XCRYPTO_PREFIX %+ _EVP_aes_256_cbc
%xdefine EVP_aes_256_ctr XCRYPTO_PREFIX %+ _EVP_aes_256_ctr
%xdefine EVP_aes_256_ecb XCRYPTO_PREFIX %+ _EVP_aes_256_ecb
%xdefine EVP_aes_256_gcm XCRYPTO_PREFIX %+ _EVP_aes_256_gcm
%xdefine EVP_aes_256_ofb XCRYPTO_PREFIX %+ _EVP_aes_256_ofb
%xdefine EVP_cleanup XCRYPTO_PREFIX %+ _EVP_cleanup
%xdefine EVP_des_cbc XCRYPTO_PREFIX %+ _EVP_des_cbc
%xdefine EVP_des_ecb XCRYPTO_PREFIX %+ _EVP_des_ecb
%xdefine EVP_des_ede XCRYPTO_PREFIX %+ _EVP_des_ede
%xdefine EVP_des_ede3 XCRYPTO_PREFIX %+ _EVP_des_ede3
%xdefine EVP_des_ede3_cbc XCRYPTO_PREFIX %+ _EVP_des_ede3_cbc
%xdefine EVP_des_ede3_ecb XCRYPTO_PREFIX %+ _EVP_des_ede3_ecb
%xdefine EVP_des_ede_cbc XCRYPTO_PREFIX %+ _EVP_des_ede_cbc
%xdefine EVP_enc_null XCRYPTO_PREFIX %+ _EVP_enc_null
%xdefine EVP_get_cipherbyname XCRYPTO_PREFIX %+ _EVP_get_cipherbyname
%xdefine EVP_get_cipherbynid XCRYPTO_PREFIX %+ _EVP_get_cipherbynid
%xdefine EVP_get_digestbyname XCRYPTO_PREFIX %+ _EVP_get_digestbyname
%xdefine EVP_get_digestbynid XCRYPTO_PREFIX %+ _EVP_get_digestbynid
%xdefine EVP_get_digestbyobj XCRYPTO_PREFIX %+ _EVP_get_digestbyobj
%xdefine EVP_has_aes_hardware XCRYPTO_PREFIX %+ _EVP_has_aes_hardware
%xdefine EVP_marshal_digest_algorithm XCRYPTO_PREFIX %+ _EVP_marshal_digest_algorithm
%xdefine EVP_marshal_private_key XCRYPTO_PREFIX %+ _EVP_marshal_private_key
%xdefine EVP_marshal_public_key XCRYPTO_PREFIX %+ _EVP_marshal_public_key
%xdefine EVP_md4 XCRYPTO_PREFIX %+ _EVP_md4
%xdefine EVP_md5 XCRYPTO_PREFIX %+ _EVP_md5
%xdefine EVP_md5_sha1 XCRYPTO_PREFIX %+ _EVP_md5_sha1
%xdefine EVP_parse_digest_algorithm XCRYPTO_PREFIX %+ _EVP_parse_digest_algorithm
%xdefine EVP_parse_private_key XCRYPTO_PREFIX %+ _EVP_parse_private_key
%xdefine EVP_parse_public_key XCRYPTO_PREFIX %+ _EVP_parse_public_key
%xdefine EVP_rc2_40_cbc XCRYPTO_PREFIX %+ _EVP_rc2_40_cbc
%xdefine EVP_rc2_cbc XCRYPTO_PREFIX %+ _EVP_rc2_cbc
%xdefine EVP_rc4 XCRYPTO_PREFIX %+ _EVP_rc4
%xdefine EVP_sha1 XCRYPTO_PREFIX %+ _EVP_sha1
%xdefine EVP_sha224 XCRYPTO_PREFIX %+ _EVP_sha224
%xdefine EVP_sha256 XCRYPTO_PREFIX %+ _EVP_sha256
%xdefine EVP_sha384 XCRYPTO_PREFIX %+ _EVP_sha384
%xdefine EVP_sha512 XCRYPTO_PREFIX %+ _EVP_sha512
%xdefine EVP_sha512_256 XCRYPTO_PREFIX %+ _EVP_sha512_256
%xdefine EVP_tls_cbc_copy_mac XCRYPTO_PREFIX %+ _EVP_tls_cbc_copy_mac
%xdefine EVP_tls_cbc_digest_record XCRYPTO_PREFIX %+ _EVP_tls_cbc_digest_record
%xdefine EVP_tls_cbc_record_digest_supported XCRYPTO_PREFIX %+ _EVP_tls_cbc_record_digest_supported
%xdefine EVP_tls_cbc_remove_padding XCRYPTO_PREFIX %+ _EVP_tls_cbc_remove_padding
%xdefine EXTENDED_KEY_USAGE_free XCRYPTO_PREFIX %+ _EXTENDED_KEY_USAGE_free
%xdefine EXTENDED_KEY_USAGE_it XCRYPTO_PREFIX %+ _EXTENDED_KEY_USAGE_it
%xdefine EXTENDED_KEY_USAGE_new XCRYPTO_PREFIX %+ _EXTENDED_KEY_USAGE_new
%xdefine FIPS_mode XCRYPTO_PREFIX %+ _FIPS_mode
%xdefine FIPS_mode_set XCRYPTO_PREFIX %+ _FIPS_mode_set
%xdefine GENERAL_NAMES_free XCRYPTO_PREFIX %+ _GENERAL_NAMES_free
%xdefine GENERAL_NAMES_it XCRYPTO_PREFIX %+ _GENERAL_NAMES_it
%xdefine GENERAL_NAMES_new XCRYPTO_PREFIX %+ _GENERAL_NAMES_new
%xdefine GENERAL_NAME_cmp XCRYPTO_PREFIX %+ _GENERAL_NAME_cmp
%xdefine GENERAL_NAME_dup XCRYPTO_PREFIX %+ _GENERAL_NAME_dup
%xdefine GENERAL_NAME_free XCRYPTO_PREFIX %+ _GENERAL_NAME_free
%xdefine GENERAL_NAME_get0_otherName XCRYPTO_PREFIX %+ _GENERAL_NAME_get0_otherName
%xdefine GENERAL_NAME_get0_value XCRYPTO_PREFIX %+ _GENERAL_NAME_get0_value
%xdefine GENERAL_NAME_it XCRYPTO_PREFIX %+ _GENERAL_NAME_it
%xdefine GENERAL_NAME_new XCRYPTO_PREFIX %+ _GENERAL_NAME_new
%xdefine GENERAL_NAME_print XCRYPTO_PREFIX %+ _GENERAL_NAME_print
%xdefine GENERAL_NAME_set0_othername XCRYPTO_PREFIX %+ _GENERAL_NAME_set0_othername
%xdefine GENERAL_NAME_set0_value XCRYPTO_PREFIX %+ _GENERAL_NAME_set0_value
%xdefine GENERAL_SUBTREE_free XCRYPTO_PREFIX %+ _GENERAL_SUBTREE_free
%xdefine GENERAL_SUBTREE_it XCRYPTO_PREFIX %+ _GENERAL_SUBTREE_it
%xdefine GENERAL_SUBTREE_new XCRYPTO_PREFIX %+ _GENERAL_SUBTREE_new
%xdefine HKDF XCRYPTO_PREFIX %+ _HKDF
%xdefine HKDF_expand XCRYPTO_PREFIX %+ _HKDF_expand
%xdefine HKDF_extract XCRYPTO_PREFIX %+ _HKDF_extract
%xdefine HMAC XCRYPTO_PREFIX %+ _HMAC
%xdefine HMAC_CTX_cleanup XCRYPTO_PREFIX %+ _HMAC_CTX_cleanup
%xdefine HMAC_CTX_copy XCRYPTO_PREFIX %+ _HMAC_CTX_copy
%xdefine HMAC_CTX_copy_ex XCRYPTO_PREFIX %+ _HMAC_CTX_copy_ex
%xdefine HMAC_CTX_free XCRYPTO_PREFIX %+ _HMAC_CTX_free
%xdefine HMAC_CTX_init XCRYPTO_PREFIX %+ _HMAC_CTX_init
%xdefine HMAC_CTX_new XCRYPTO_PREFIX %+ _HMAC_CTX_new
%xdefine HMAC_CTX_reset XCRYPTO_PREFIX %+ _HMAC_CTX_reset
%xdefine HMAC_Final XCRYPTO_PREFIX %+ _HMAC_Final
%xdefine HMAC_Init XCRYPTO_PREFIX %+ _HMAC_Init
%xdefine HMAC_Init_ex XCRYPTO_PREFIX %+ _HMAC_Init_ex
%xdefine HMAC_Update XCRYPTO_PREFIX %+ _HMAC_Update
%xdefine HMAC_size XCRYPTO_PREFIX %+ _HMAC_size
%xdefine HRSS_decap XCRYPTO_PREFIX %+ _HRSS_decap
%xdefine HRSS_encap XCRYPTO_PREFIX %+ _HRSS_encap
%xdefine HRSS_generate_key XCRYPTO_PREFIX %+ _HRSS_generate_key
%xdefine HRSS_marshal_public_key XCRYPTO_PREFIX %+ _HRSS_marshal_public_key
%xdefine HRSS_parse_public_key XCRYPTO_PREFIX %+ _HRSS_parse_public_key
%xdefine HRSS_poly3_invert XCRYPTO_PREFIX %+ _HRSS_poly3_invert
%xdefine HRSS_poly3_mul XCRYPTO_PREFIX %+ _HRSS_poly3_mul
%xdefine ISSUING_DIST_POINT_free XCRYPTO_PREFIX %+ _ISSUING_DIST_POINT_free
%xdefine ISSUING_DIST_POINT_it XCRYPTO_PREFIX %+ _ISSUING_DIST_POINT_it
%xdefine ISSUING_DIST_POINT_new XCRYPTO_PREFIX %+ _ISSUING_DIST_POINT_new
%xdefine MD4 XCRYPTO_PREFIX %+ _MD4
%xdefine MD4_Final XCRYPTO_PREFIX %+ _MD4_Final
%xdefine MD4_Init XCRYPTO_PREFIX %+ _MD4_Init
%xdefine MD4_Transform XCRYPTO_PREFIX %+ _MD4_Transform
%xdefine MD4_Update XCRYPTO_PREFIX %+ _MD4_Update
%xdefine MD5 XCRYPTO_PREFIX %+ _MD5
%xdefine MD5_Final XCRYPTO_PREFIX %+ _MD5_Final
%xdefine MD5_Init XCRYPTO_PREFIX %+ _MD5_Init
%xdefine MD5_Transform XCRYPTO_PREFIX %+ _MD5_Transform
%xdefine MD5_Update XCRYPTO_PREFIX %+ _MD5_Update
%xdefine METHOD_ref XCRYPTO_PREFIX %+ _METHOD_ref
%xdefine METHOD_unref XCRYPTO_PREFIX %+ _METHOD_unref
%xdefine NAME_CONSTRAINTS_check XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_check
%xdefine NAME_CONSTRAINTS_free XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_free
%xdefine NAME_CONSTRAINTS_it XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_it
%xdefine NAME_CONSTRAINTS_new XCRYPTO_PREFIX %+ _NAME_CONSTRAINTS_new
%xdefine NCONF_free XCRYPTO_PREFIX %+ _NCONF_free
%xdefine NCONF_get_section XCRYPTO_PREFIX %+ _NCONF_get_section
%xdefine NCONF_get_string XCRYPTO_PREFIX %+ _NCONF_get_string
%xdefine NCONF_load XCRYPTO_PREFIX %+ _NCONF_load
%xdefine NCONF_load_bio XCRYPTO_PREFIX %+ _NCONF_load_bio
%xdefine NCONF_new XCRYPTO_PREFIX %+ _NCONF_new
%xdefine NETSCAPE_SPKAC_free XCRYPTO_PREFIX %+ _NETSCAPE_SPKAC_free
%xdefine NETSCAPE_SPKAC_it XCRYPTO_PREFIX %+ _NETSCAPE_SPKAC_it
%xdefine NETSCAPE_SPKAC_new XCRYPTO_PREFIX %+ _NETSCAPE_SPKAC_new
%xdefine NETSCAPE_SPKI_b64_decode XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_b64_decode
%xdefine NETSCAPE_SPKI_b64_encode XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_b64_encode
%xdefine NETSCAPE_SPKI_free XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_free
%xdefine NETSCAPE_SPKI_get_pubkey XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_get_pubkey
%xdefine NETSCAPE_SPKI_it XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_it
%xdefine NETSCAPE_SPKI_new XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_new
%xdefine NETSCAPE_SPKI_set_pubkey XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_set_pubkey
%xdefine NETSCAPE_SPKI_sign XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_sign
%xdefine NETSCAPE_SPKI_verify XCRYPTO_PREFIX %+ _NETSCAPE_SPKI_verify
%xdefine NOTICEREF_free XCRYPTO_PREFIX %+ _NOTICEREF_free
%xdefine NOTICEREF_it XCRYPTO_PREFIX %+ _NOTICEREF_it
%xdefine NOTICEREF_new XCRYPTO_PREFIX %+ _NOTICEREF_new
%xdefine OBJ_cbs2nid XCRYPTO_PREFIX %+ _OBJ_cbs2nid
%xdefine OBJ_cleanup XCRYPTO_PREFIX %+ _OBJ_cleanup
%xdefine OBJ_cmp XCRYPTO_PREFIX %+ _OBJ_cmp
%xdefine OBJ_create XCRYPTO_PREFIX %+ _OBJ_create
%xdefine OBJ_dup XCRYPTO_PREFIX %+ _OBJ_dup
%xdefine OBJ_find_sigid_algs XCRYPTO_PREFIX %+ _OBJ_find_sigid_algs
%xdefine OBJ_find_sigid_by_algs XCRYPTO_PREFIX %+ _OBJ_find_sigid_by_algs
%xdefine OBJ_get0_data XCRYPTO_PREFIX %+ _OBJ_get0_data
%xdefine OBJ_length XCRYPTO_PREFIX %+ _OBJ_length
%xdefine OBJ_ln2nid XCRYPTO_PREFIX %+ _OBJ_ln2nid
%xdefine OBJ_nid2cbb XCRYPTO_PREFIX %+ _OBJ_nid2cbb
%xdefine OBJ_nid2ln XCRYPTO_PREFIX %+ _OBJ_nid2ln
%xdefine OBJ_nid2obj XCRYPTO_PREFIX %+ _OBJ_nid2obj
%xdefine OBJ_nid2sn XCRYPTO_PREFIX %+ _OBJ_nid2sn
%xdefine OBJ_obj2nid XCRYPTO_PREFIX %+ _OBJ_obj2nid
%xdefine OBJ_obj2txt XCRYPTO_PREFIX %+ _OBJ_obj2txt
%xdefine OBJ_sn2nid XCRYPTO_PREFIX %+ _OBJ_sn2nid
%xdefine OBJ_txt2nid XCRYPTO_PREFIX %+ _OBJ_txt2nid
%xdefine OBJ_txt2obj XCRYPTO_PREFIX %+ _OBJ_txt2obj
%xdefine OPENSSL_add_all_algorithms_conf XCRYPTO_PREFIX %+ _OPENSSL_add_all_algorithms_conf
%xdefine XCRYPTO_ARMcap_P XCRYPTO_PREFIX %+ _XCRYPTO_ARMcap_P
%xdefine OPENSSL_built_in_curves XCRYPTO_PREFIX %+ _OPENSSL_built_in_curves
%xdefine OPENSSL_cleanse XCRYPTO_PREFIX %+ _OPENSSL_cleanse
%xdefine OPENSSL_cleanup XCRYPTO_PREFIX %+ _OPENSSL_cleanup
%xdefine OPENSSL_clear_free XCRYPTO_PREFIX %+ _OPENSSL_clear_free
%xdefine OPENSSL_config XCRYPTO_PREFIX %+ _OPENSSL_config
%xdefine OPENSSL_cpuid_setup XCRYPTO_PREFIX %+ _OPENSSL_cpuid_setup
%xdefine OPENSSL_free XCRYPTO_PREFIX %+ _OPENSSL_free
%xdefine OPENSSL_get_armcap_pointer_for_test XCRYPTO_PREFIX %+ _OPENSSL_get_armcap_pointer_for_test
%xdefine OPENSSL_gmtime XCRYPTO_PREFIX %+ _OPENSSL_gmtime
%xdefine OPENSSL_gmtime_adj XCRYPTO_PREFIX %+ _OPENSSL_gmtime_adj
%xdefine OPENSSL_gmtime_diff XCRYPTO_PREFIX %+ _OPENSSL_gmtime_diff
%xdefine OPENSSL_hash32 XCRYPTO_PREFIX %+ _OPENSSL_hash32
%xdefine OPENSSL_ia32cap_P XCRYPTO_PREFIX %+ _OPENSSL_ia32cap_P
%xdefine OPENSSL_init_crypto XCRYPTO_PREFIX %+ _OPENSSL_init_crypto
%xdefine OPENSSL_init_ssl XCRYPTO_PREFIX %+ _OPENSSL_init_ssl
%xdefine OPENSSL_load_builtin_modules XCRYPTO_PREFIX %+ _OPENSSL_load_builtin_modules
%xdefine OPENSSL_malloc XCRYPTO_PREFIX %+ _OPENSSL_malloc
%xdefine OPENSSL_malloc_init XCRYPTO_PREFIX %+ _OPENSSL_malloc_init
%xdefine OPENSSL_memdup XCRYPTO_PREFIX %+ _OPENSSL_memdup
%xdefine OPENSSL_no_config XCRYPTO_PREFIX %+ _OPENSSL_no_config
%xdefine OPENSSL_realloc XCRYPTO_PREFIX %+ _OPENSSL_realloc
%xdefine OPENSSL_strcasecmp XCRYPTO_PREFIX %+ _OPENSSL_strcasecmp
%xdefine OPENSSL_strdup XCRYPTO_PREFIX %+ _OPENSSL_strdup
%xdefine OPENSSL_strlcat XCRYPTO_PREFIX %+ _OPENSSL_strlcat
%xdefine OPENSSL_strlcpy XCRYPTO_PREFIX %+ _OPENSSL_strlcpy
%xdefine OPENSSL_strncasecmp XCRYPTO_PREFIX %+ _OPENSSL_strncasecmp
%xdefine OPENSSL_strndup XCRYPTO_PREFIX %+ _OPENSSL_strndup
%xdefine OPENSSL_strnlen XCRYPTO_PREFIX %+ _OPENSSL_strnlen
%xdefine OPENSSL_tolower XCRYPTO_PREFIX %+ _OPENSSL_tolower
%xdefine OTHERNAME_cmp XCRYPTO_PREFIX %+ _OTHERNAME_cmp
%xdefine OTHERNAME_free XCRYPTO_PREFIX %+ _OTHERNAME_free
%xdefine OTHERNAME_it XCRYPTO_PREFIX %+ _OTHERNAME_it
%xdefine OTHERNAME_new XCRYPTO_PREFIX %+ _OTHERNAME_new
%xdefine OpenSSL_add_all_algorithms XCRYPTO_PREFIX %+ _OpenSSL_add_all_algorithms
%xdefine OpenSSL_add_all_ciphers XCRYPTO_PREFIX %+ _OpenSSL_add_all_ciphers
%xdefine OpenSSL_add_all_digests XCRYPTO_PREFIX %+ _OpenSSL_add_all_digests
%xdefine OpenSSL_version XCRYPTO_PREFIX %+ _OpenSSL_version
%xdefine OpenSSL_version_num XCRYPTO_PREFIX %+ _OpenSSL_version_num
%xdefine PEM_ASN1_read XCRYPTO_PREFIX %+ _PEM_ASN1_read
%xdefine PEM_ASN1_read_bio XCRYPTO_PREFIX %+ _PEM_ASN1_read_bio
%xdefine PEM_ASN1_write XCRYPTO_PREFIX %+ _PEM_ASN1_write
%xdefine PEM_ASN1_write_bio XCRYPTO_PREFIX %+ _PEM_ASN1_write_bio
%xdefine PEM_X509_INFO_read XCRYPTO_PREFIX %+ _PEM_X509_INFO_read
%xdefine PEM_X509_INFO_read_bio XCRYPTO_PREFIX %+ _PEM_X509_INFO_read_bio
%xdefine PEM_X509_INFO_write_bio XCRYPTO_PREFIX %+ _PEM_X509_INFO_write_bio
%xdefine PEM_bytes_read_bio XCRYPTO_PREFIX %+ _PEM_bytes_read_bio
%xdefine PEM_def_callback XCRYPTO_PREFIX %+ _PEM_def_callback
%xdefine PEM_dek_info XCRYPTO_PREFIX %+ _PEM_dek_info
%xdefine PEM_do_header XCRYPTO_PREFIX %+ _PEM_do_header
%xdefine PEM_get_EVP_CIPHER_INFO XCRYPTO_PREFIX %+ _PEM_get_EVP_CIPHER_INFO
%xdefine PEM_proc_type XCRYPTO_PREFIX %+ _PEM_proc_type
%xdefine PEM_read XCRYPTO_PREFIX %+ _PEM_read
%xdefine PEM_read_DHparams XCRYPTO_PREFIX %+ _PEM_read_DHparams
%xdefine PEM_read_DSAPrivateKey XCRYPTO_PREFIX %+ _PEM_read_DSAPrivateKey
%xdefine PEM_read_DSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_DSA_PUBKEY
%xdefine PEM_read_DSAparams XCRYPTO_PREFIX %+ _PEM_read_DSAparams
%xdefine PEM_read_ECPrivateKey XCRYPTO_PREFIX %+ _PEM_read_ECPrivateKey
%xdefine PEM_read_EC_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_EC_PUBKEY
%xdefine PEM_read_PKCS7 XCRYPTO_PREFIX %+ _PEM_read_PKCS7
%xdefine PEM_read_PKCS8 XCRYPTO_PREFIX %+ _PEM_read_PKCS8
%xdefine PEM_read_PKCS8_PRIV_KEY_INFO XCRYPTO_PREFIX %+ _PEM_read_PKCS8_PRIV_KEY_INFO
%xdefine PEM_read_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_PUBKEY
%xdefine PEM_read_PrivateKey XCRYPTO_PREFIX %+ _PEM_read_PrivateKey
%xdefine PEM_read_RSAPrivateKey XCRYPTO_PREFIX %+ _PEM_read_RSAPrivateKey
%xdefine PEM_read_RSAPublicKey XCRYPTO_PREFIX %+ _PEM_read_RSAPublicKey
%xdefine PEM_read_RSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_RSA_PUBKEY
%xdefine PEM_read_SSL_SESSION XCRYPTO_PREFIX %+ _PEM_read_SSL_SESSION
%xdefine PEM_read_X509 XCRYPTO_PREFIX %+ _PEM_read_X509
%xdefine PEM_read_X509_AUX XCRYPTO_PREFIX %+ _PEM_read_X509_AUX
%xdefine PEM_read_X509_CRL XCRYPTO_PREFIX %+ _PEM_read_X509_CRL
%xdefine PEM_read_X509_REQ XCRYPTO_PREFIX %+ _PEM_read_X509_REQ
%xdefine PEM_read_bio XCRYPTO_PREFIX %+ _PEM_read_bio
%xdefine PEM_read_bio_DHparams XCRYPTO_PREFIX %+ _PEM_read_bio_DHparams
%xdefine PEM_read_bio_DSAPrivateKey XCRYPTO_PREFIX %+ _PEM_read_bio_DSAPrivateKey
%xdefine PEM_read_bio_DSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_bio_DSA_PUBKEY
%xdefine PEM_read_bio_DSAparams XCRYPTO_PREFIX %+ _PEM_read_bio_DSAparams
%xdefine PEM_read_bio_ECPrivateKey XCRYPTO_PREFIX %+ _PEM_read_bio_ECPrivateKey
%xdefine PEM_read_bio_EC_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_bio_EC_PUBKEY
%xdefine PEM_read_bio_PKCS7 XCRYPTO_PREFIX %+ _PEM_read_bio_PKCS7
%xdefine PEM_read_bio_PKCS8 XCRYPTO_PREFIX %+ _PEM_read_bio_PKCS8
%xdefine PEM_read_bio_PKCS8_PRIV_KEY_INFO XCRYPTO_PREFIX %+ _PEM_read_bio_PKCS8_PRIV_KEY_INFO
%xdefine PEM_read_bio_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_bio_PUBKEY
%xdefine PEM_read_bio_PrivateKey XCRYPTO_PREFIX %+ _PEM_read_bio_PrivateKey
%xdefine PEM_read_bio_RSAPrivateKey XCRYPTO_PREFIX %+ _PEM_read_bio_RSAPrivateKey
%xdefine PEM_read_bio_RSAPublicKey XCRYPTO_PREFIX %+ _PEM_read_bio_RSAPublicKey
%xdefine PEM_read_bio_RSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_read_bio_RSA_PUBKEY
%xdefine PEM_read_bio_SSL_SESSION XCRYPTO_PREFIX %+ _PEM_read_bio_SSL_SESSION
%xdefine PEM_read_bio_X509 XCRYPTO_PREFIX %+ _PEM_read_bio_X509
%xdefine PEM_read_bio_X509_AUX XCRYPTO_PREFIX %+ _PEM_read_bio_X509_AUX
%xdefine PEM_read_bio_X509_CRL XCRYPTO_PREFIX %+ _PEM_read_bio_X509_CRL
%xdefine PEM_read_bio_X509_REQ XCRYPTO_PREFIX %+ _PEM_read_bio_X509_REQ
%xdefine PEM_write XCRYPTO_PREFIX %+ _PEM_write
%xdefine PEM_write_DHparams XCRYPTO_PREFIX %+ _PEM_write_DHparams
%xdefine PEM_write_DSAPrivateKey XCRYPTO_PREFIX %+ _PEM_write_DSAPrivateKey
%xdefine PEM_write_DSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_DSA_PUBKEY
%xdefine PEM_write_DSAparams XCRYPTO_PREFIX %+ _PEM_write_DSAparams
%xdefine PEM_write_ECPrivateKey XCRYPTO_PREFIX %+ _PEM_write_ECPrivateKey
%xdefine PEM_write_EC_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_EC_PUBKEY
%xdefine PEM_write_PKCS7 XCRYPTO_PREFIX %+ _PEM_write_PKCS7
%xdefine PEM_write_PKCS8 XCRYPTO_PREFIX %+ _PEM_write_PKCS8
%xdefine PEM_write_PKCS8PrivateKey XCRYPTO_PREFIX %+ _PEM_write_PKCS8PrivateKey
%xdefine PEM_write_PKCS8PrivateKey_nid XCRYPTO_PREFIX %+ _PEM_write_PKCS8PrivateKey_nid
%xdefine PEM_write_PKCS8_PRIV_KEY_INFO XCRYPTO_PREFIX %+ _PEM_write_PKCS8_PRIV_KEY_INFO
%xdefine PEM_write_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_PUBKEY
%xdefine PEM_write_PrivateKey XCRYPTO_PREFIX %+ _PEM_write_PrivateKey
%xdefine PEM_write_RSAPrivateKey XCRYPTO_PREFIX %+ _PEM_write_RSAPrivateKey
%xdefine PEM_write_RSAPublicKey XCRYPTO_PREFIX %+ _PEM_write_RSAPublicKey
%xdefine PEM_write_RSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_RSA_PUBKEY
%xdefine PEM_write_SSL_SESSION XCRYPTO_PREFIX %+ _PEM_write_SSL_SESSION
%xdefine PEM_write_X509 XCRYPTO_PREFIX %+ _PEM_write_X509
%xdefine PEM_write_X509_AUX XCRYPTO_PREFIX %+ _PEM_write_X509_AUX
%xdefine PEM_write_X509_CRL XCRYPTO_PREFIX %+ _PEM_write_X509_CRL
%xdefine PEM_write_X509_REQ XCRYPTO_PREFIX %+ _PEM_write_X509_REQ
%xdefine PEM_write_X509_REQ_NEW XCRYPTO_PREFIX %+ _PEM_write_X509_REQ_NEW
%xdefine PEM_write_bio XCRYPTO_PREFIX %+ _PEM_write_bio
%xdefine PEM_write_bio_DHparams XCRYPTO_PREFIX %+ _PEM_write_bio_DHparams
%xdefine PEM_write_bio_DSAPrivateKey XCRYPTO_PREFIX %+ _PEM_write_bio_DSAPrivateKey
%xdefine PEM_write_bio_DSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_bio_DSA_PUBKEY
%xdefine PEM_write_bio_DSAparams XCRYPTO_PREFIX %+ _PEM_write_bio_DSAparams
%xdefine PEM_write_bio_ECPrivateKey XCRYPTO_PREFIX %+ _PEM_write_bio_ECPrivateKey
%xdefine PEM_write_bio_EC_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_bio_EC_PUBKEY
%xdefine PEM_write_bio_PKCS7 XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS7
%xdefine PEM_write_bio_PKCS8 XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8
%xdefine PEM_write_bio_PKCS8PrivateKey XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8PrivateKey
%xdefine PEM_write_bio_PKCS8PrivateKey_nid XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8PrivateKey_nid
%xdefine PEM_write_bio_PKCS8_PRIV_KEY_INFO XCRYPTO_PREFIX %+ _PEM_write_bio_PKCS8_PRIV_KEY_INFO
%xdefine PEM_write_bio_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_bio_PUBKEY
%xdefine PEM_write_bio_PrivateKey XCRYPTO_PREFIX %+ _PEM_write_bio_PrivateKey
%xdefine PEM_write_bio_RSAPrivateKey XCRYPTO_PREFIX %+ _PEM_write_bio_RSAPrivateKey
%xdefine PEM_write_bio_RSAPublicKey XCRYPTO_PREFIX %+ _PEM_write_bio_RSAPublicKey
%xdefine PEM_write_bio_RSA_PUBKEY XCRYPTO_PREFIX %+ _PEM_write_bio_RSA_PUBKEY
%xdefine PEM_write_bio_SSL_SESSION XCRYPTO_PREFIX %+ _PEM_write_bio_SSL_SESSION
%xdefine PEM_write_bio_X509 XCRYPTO_PREFIX %+ _PEM_write_bio_X509
%xdefine PEM_write_bio_X509_AUX XCRYPTO_PREFIX %+ _PEM_write_bio_X509_AUX
%xdefine PEM_write_bio_X509_CRL XCRYPTO_PREFIX %+ _PEM_write_bio_X509_CRL
%xdefine PEM_write_bio_X509_REQ XCRYPTO_PREFIX %+ _PEM_write_bio_X509_REQ
%xdefine PEM_write_bio_X509_REQ_NEW XCRYPTO_PREFIX %+ _PEM_write_bio_X509_REQ_NEW
%xdefine PKCS12_PBE_add XCRYPTO_PREFIX %+ _PKCS12_PBE_add
%xdefine PKCS12_create XCRYPTO_PREFIX %+ _PKCS12_create
%xdefine PKCS12_free XCRYPTO_PREFIX %+ _PKCS12_free
%xdefine PKCS12_get_key_and_certs XCRYPTO_PREFIX %+ _PKCS12_get_key_and_certs
%xdefine PKCS12_parse XCRYPTO_PREFIX %+ _PKCS12_parse
%xdefine PKCS12_verify_mac XCRYPTO_PREFIX %+ _PKCS12_verify_mac
%xdefine PKCS5_PBKDF2_HMAC XCRYPTO_PREFIX %+ _PKCS5_PBKDF2_HMAC
%xdefine PKCS5_PBKDF2_HMAC_SHA1 XCRYPTO_PREFIX %+ _PKCS5_PBKDF2_HMAC_SHA1
%xdefine PKCS5_pbe2_decrypt_init XCRYPTO_PREFIX %+ _PKCS5_pbe2_decrypt_init
%xdefine PKCS5_pbe2_encrypt_init XCRYPTO_PREFIX %+ _PKCS5_pbe2_encrypt_init
%xdefine PKCS7_bundle_CRLs XCRYPTO_PREFIX %+ _PKCS7_bundle_CRLs
%xdefine PKCS7_bundle_certificates XCRYPTO_PREFIX %+ _PKCS7_bundle_certificates
%xdefine PKCS7_free XCRYPTO_PREFIX %+ _PKCS7_free
%xdefine PKCS7_get_CRLs XCRYPTO_PREFIX %+ _PKCS7_get_CRLs
%xdefine PKCS7_get_PEM_CRLs XCRYPTO_PREFIX %+ _PKCS7_get_PEM_CRLs
%xdefine PKCS7_get_PEM_certificates XCRYPTO_PREFIX %+ _PKCS7_get_PEM_certificates
%xdefine PKCS7_get_certificates XCRYPTO_PREFIX %+ _PKCS7_get_certificates
%xdefine PKCS7_get_raw_certificates XCRYPTO_PREFIX %+ _PKCS7_get_raw_certificates
%xdefine PKCS7_sign XCRYPTO_PREFIX %+ _PKCS7_sign
%xdefine PKCS7_type_is_data XCRYPTO_PREFIX %+ _PKCS7_type_is_data
%xdefine PKCS7_type_is_digest XCRYPTO_PREFIX %+ _PKCS7_type_is_digest
%xdefine PKCS7_type_is_encrypted XCRYPTO_PREFIX %+ _PKCS7_type_is_encrypted
%xdefine PKCS7_type_is_enveloped XCRYPTO_PREFIX %+ _PKCS7_type_is_enveloped
%xdefine PKCS7_type_is_signed XCRYPTO_PREFIX %+ _PKCS7_type_is_signed
%xdefine PKCS7_type_is_signedAndEnveloped XCRYPTO_PREFIX %+ _PKCS7_type_is_signedAndEnveloped
%xdefine PKCS8_PRIV_KEY_INFO_free XCRYPTO_PREFIX %+ _PKCS8_PRIV_KEY_INFO_free
%xdefine PKCS8_PRIV_KEY_INFO_it XCRYPTO_PREFIX %+ _PKCS8_PRIV_KEY_INFO_it
%xdefine PKCS8_PRIV_KEY_INFO_new XCRYPTO_PREFIX %+ _PKCS8_PRIV_KEY_INFO_new
%xdefine PKCS8_decrypt XCRYPTO_PREFIX %+ _PKCS8_decrypt
%xdefine PKCS8_encrypt XCRYPTO_PREFIX %+ _PKCS8_encrypt
%xdefine PKCS8_marshal_encrypted_private_key XCRYPTO_PREFIX %+ _PKCS8_marshal_encrypted_private_key
%xdefine PKCS8_parse_encrypted_private_key XCRYPTO_PREFIX %+ _PKCS8_parse_encrypted_private_key
%xdefine PKCS8_pkey_get0 XCRYPTO_PREFIX %+ _PKCS8_pkey_get0
%xdefine PKCS8_pkey_set0 XCRYPTO_PREFIX %+ _PKCS8_pkey_set0
%xdefine PKEY_USAGE_PERIOD_free XCRYPTO_PREFIX %+ _PKEY_USAGE_PERIOD_free
%xdefine PKEY_USAGE_PERIOD_it XCRYPTO_PREFIX %+ _PKEY_USAGE_PERIOD_it
%xdefine PKEY_USAGE_PERIOD_new XCRYPTO_PREFIX %+ _PKEY_USAGE_PERIOD_new
%xdefine PMBTOKEN_PRETOKEN_free XCRYPTO_PREFIX %+ _PMBTOKEN_PRETOKEN_free
%xdefine POLICYINFO_free XCRYPTO_PREFIX %+ _POLICYINFO_free
%xdefine POLICYINFO_it XCRYPTO_PREFIX %+ _POLICYINFO_it
%xdefine POLICYINFO_new XCRYPTO_PREFIX %+ _POLICYINFO_new
%xdefine POLICYQUALINFO_free XCRYPTO_PREFIX %+ _POLICYQUALINFO_free
%xdefine POLICYQUALINFO_it XCRYPTO_PREFIX %+ _POLICYQUALINFO_it
%xdefine POLICYQUALINFO_new XCRYPTO_PREFIX %+ _POLICYQUALINFO_new
%xdefine POLICY_CONSTRAINTS_free XCRYPTO_PREFIX %+ _POLICY_CONSTRAINTS_free
%xdefine POLICY_CONSTRAINTS_it XCRYPTO_PREFIX %+ _POLICY_CONSTRAINTS_it
%xdefine POLICY_CONSTRAINTS_new XCRYPTO_PREFIX %+ _POLICY_CONSTRAINTS_new
%xdefine POLICY_MAPPINGS_it XCRYPTO_PREFIX %+ _POLICY_MAPPINGS_it
%xdefine POLICY_MAPPING_free XCRYPTO_PREFIX %+ _POLICY_MAPPING_free
%xdefine POLICY_MAPPING_it XCRYPTO_PREFIX %+ _POLICY_MAPPING_it
%xdefine POLICY_MAPPING_new XCRYPTO_PREFIX %+ _POLICY_MAPPING_new
%xdefine PROXY_CERT_INFO_EXTENSION_free XCRYPTO_PREFIX %+ _PROXY_CERT_INFO_EXTENSION_free
%xdefine PROXY_CERT_INFO_EXTENSION_it XCRYPTO_PREFIX %+ _PROXY_CERT_INFO_EXTENSION_it
%xdefine PROXY_CERT_INFO_EXTENSION_new XCRYPTO_PREFIX %+ _PROXY_CERT_INFO_EXTENSION_new
%xdefine PROXY_POLICY_free XCRYPTO_PREFIX %+ _PROXY_POLICY_free
%xdefine PROXY_POLICY_it XCRYPTO_PREFIX %+ _PROXY_POLICY_it
%xdefine PROXY_POLICY_new XCRYPTO_PREFIX %+ _PROXY_POLICY_new
%xdefine RAND_SSLeay XCRYPTO_PREFIX %+ _RAND_SSLeay
%xdefine RAND_add XCRYPTO_PREFIX %+ _RAND_add
%xdefine RAND_bytes XCRYPTO_PREFIX %+ _RAND_bytes
%xdefine RAND_bytes_with_additional_data XCRYPTO_PREFIX %+ _RAND_bytes_with_additional_data
%xdefine RAND_cleanup XCRYPTO_PREFIX %+ _RAND_cleanup
%xdefine RAND_egd XCRYPTO_PREFIX %+ _RAND_egd
%xdefine RAND_enable_fork_unsafe_buffering XCRYPTO_PREFIX %+ _RAND_enable_fork_unsafe_buffering
%xdefine RAND_file_name XCRYPTO_PREFIX %+ _RAND_file_name
%xdefine RAND_get_rand_method XCRYPTO_PREFIX %+ _RAND_get_rand_method
%xdefine RAND_load_file XCRYPTO_PREFIX %+ _RAND_load_file
%xdefine RAND_poll XCRYPTO_PREFIX %+ _RAND_poll
%xdefine RAND_pseudo_bytes XCRYPTO_PREFIX %+ _RAND_pseudo_bytes
%xdefine RAND_seed XCRYPTO_PREFIX %+ _RAND_seed
%xdefine RAND_set_rand_method XCRYPTO_PREFIX %+ _RAND_set_rand_method
%xdefine RAND_set_urandom_fd XCRYPTO_PREFIX %+ _RAND_set_urandom_fd
%xdefine RAND_status XCRYPTO_PREFIX %+ _RAND_status
%xdefine RC4 XCRYPTO_PREFIX %+ _RC4
%xdefine RC4_set_key XCRYPTO_PREFIX %+ _RC4_set_key
%xdefine RSAPrivateKey_dup XCRYPTO_PREFIX %+ _RSAPrivateKey_dup
%xdefine RSAPublicKey_dup XCRYPTO_PREFIX %+ _RSAPublicKey_dup
%xdefine RSAZ_1024_mod_exp_avx2 XCRYPTO_PREFIX %+ _RSAZ_1024_mod_exp_avx2
%xdefine RSA_PSS_PARAMS_free XCRYPTO_PREFIX %+ _RSA_PSS_PARAMS_free
%xdefine RSA_PSS_PARAMS_it XCRYPTO_PREFIX %+ _RSA_PSS_PARAMS_it
%xdefine RSA_PSS_PARAMS_new XCRYPTO_PREFIX %+ _RSA_PSS_PARAMS_new
%xdefine RSA_add_pkcs1_prefix XCRYPTO_PREFIX %+ _RSA_add_pkcs1_prefix
%xdefine RSA_bits XCRYPTO_PREFIX %+ _RSA_bits
%xdefine RSA_blinding_on XCRYPTO_PREFIX %+ _RSA_blinding_on
%xdefine RSA_check_fips XCRYPTO_PREFIX %+ _RSA_check_fips
%xdefine RSA_check_key XCRYPTO_PREFIX %+ _RSA_check_key
%xdefine RSA_decrypt XCRYPTO_PREFIX %+ _RSA_decrypt
%xdefine RSA_default_method XCRYPTO_PREFIX %+ _RSA_default_method
%xdefine RSA_encrypt XCRYPTO_PREFIX %+ _RSA_encrypt
%xdefine RSA_flags XCRYPTO_PREFIX %+ _RSA_flags
%xdefine RSA_free XCRYPTO_PREFIX %+ _RSA_free
%xdefine RSA_generate_key_ex XCRYPTO_PREFIX %+ _RSA_generate_key_ex
%xdefine RSA_generate_key_fips XCRYPTO_PREFIX %+ _RSA_generate_key_fips
%xdefine RSA_get0_crt_params XCRYPTO_PREFIX %+ _RSA_get0_crt_params
%xdefine RSA_get0_d XCRYPTO_PREFIX %+ _RSA_get0_d
%xdefine RSA_get0_dmp1 XCRYPTO_PREFIX %+ _RSA_get0_dmp1
%xdefine RSA_get0_dmq1 XCRYPTO_PREFIX %+ _RSA_get0_dmq1
%xdefine RSA_get0_e XCRYPTO_PREFIX %+ _RSA_get0_e
%xdefine RSA_get0_factors XCRYPTO_PREFIX %+ _RSA_get0_factors
%xdefine RSA_get0_iqmp XCRYPTO_PREFIX %+ _RSA_get0_iqmp
%xdefine RSA_get0_key XCRYPTO_PREFIX %+ _RSA_get0_key
%xdefine RSA_get0_n XCRYPTO_PREFIX %+ _RSA_get0_n
%xdefine RSA_get0_p XCRYPTO_PREFIX %+ _RSA_get0_p
%xdefine RSA_get0_q XCRYPTO_PREFIX %+ _RSA_get0_q
%xdefine RSA_get_ex_data XCRYPTO_PREFIX %+ _RSA_get_ex_data
%xdefine RSA_get_ex_new_index XCRYPTO_PREFIX %+ _RSA_get_ex_new_index
%xdefine RSA_is_opaque XCRYPTO_PREFIX %+ _RSA_is_opaque
%xdefine RSA_marshal_private_key XCRYPTO_PREFIX %+ _RSA_marshal_private_key
%xdefine RSA_marshal_public_key XCRYPTO_PREFIX %+ _RSA_marshal_public_key
%xdefine RSA_new XCRYPTO_PREFIX %+ _RSA_new
%xdefine RSA_new_method XCRYPTO_PREFIX %+ _RSA_new_method
%xdefine RSA_padding_add_PKCS1_OAEP_mgf1 XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_OAEP_mgf1
%xdefine RSA_padding_add_PKCS1_PSS_mgf1 XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_PSS_mgf1
%xdefine RSA_padding_add_PKCS1_type_1 XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_type_1
%xdefine RSA_padding_add_PKCS1_type_2 XCRYPTO_PREFIX %+ _RSA_padding_add_PKCS1_type_2
%xdefine RSA_padding_add_none XCRYPTO_PREFIX %+ _RSA_padding_add_none
%xdefine RSA_padding_check_PKCS1_OAEP_mgf1 XCRYPTO_PREFIX %+ _RSA_padding_check_PKCS1_OAEP_mgf1
%xdefine RSA_padding_check_PKCS1_type_1 XCRYPTO_PREFIX %+ _RSA_padding_check_PKCS1_type_1
%xdefine RSA_padding_check_PKCS1_type_2 XCRYPTO_PREFIX %+ _RSA_padding_check_PKCS1_type_2
%xdefine RSA_parse_private_key XCRYPTO_PREFIX %+ _RSA_parse_private_key
%xdefine RSA_parse_public_key XCRYPTO_PREFIX %+ _RSA_parse_public_key
%xdefine RSA_print XCRYPTO_PREFIX %+ _RSA_print
%xdefine RSA_private_decrypt XCRYPTO_PREFIX %+ _RSA_private_decrypt
%xdefine RSA_private_encrypt XCRYPTO_PREFIX %+ _RSA_private_encrypt
%xdefine RSA_private_key_from_bytes XCRYPTO_PREFIX %+ _RSA_private_key_from_bytes
%xdefine RSA_private_key_to_bytes XCRYPTO_PREFIX %+ _RSA_private_key_to_bytes
%xdefine RSA_private_transform XCRYPTO_PREFIX %+ _RSA_private_transform
%xdefine RSA_public_decrypt XCRYPTO_PREFIX %+ _RSA_public_decrypt
%xdefine RSA_public_encrypt XCRYPTO_PREFIX %+ _RSA_public_encrypt
%xdefine RSA_public_key_from_bytes XCRYPTO_PREFIX %+ _RSA_public_key_from_bytes
%xdefine RSA_public_key_to_bytes XCRYPTO_PREFIX %+ _RSA_public_key_to_bytes
%xdefine RSA_set0_crt_params XCRYPTO_PREFIX %+ _RSA_set0_crt_params
%xdefine RSA_set0_factors XCRYPTO_PREFIX %+ _RSA_set0_factors
%xdefine RSA_set0_key XCRYPTO_PREFIX %+ _RSA_set0_key
%xdefine RSA_set_ex_data XCRYPTO_PREFIX %+ _RSA_set_ex_data
%xdefine RSA_sign XCRYPTO_PREFIX %+ _RSA_sign
%xdefine RSA_sign_pss_mgf1 XCRYPTO_PREFIX %+ _RSA_sign_pss_mgf1
%xdefine RSA_sign_raw XCRYPTO_PREFIX %+ _RSA_sign_raw
%xdefine RSA_size XCRYPTO_PREFIX %+ _RSA_size
%xdefine RSA_up_ref XCRYPTO_PREFIX %+ _RSA_up_ref
%xdefine RSA_verify XCRYPTO_PREFIX %+ _RSA_verify
%xdefine RSA_verify_PKCS1_PSS_mgf1 XCRYPTO_PREFIX %+ _RSA_verify_PKCS1_PSS_mgf1
%xdefine RSA_verify_pss_mgf1 XCRYPTO_PREFIX %+ _RSA_verify_pss_mgf1
%xdefine RSA_verify_raw XCRYPTO_PREFIX %+ _RSA_verify_raw
%xdefine SHA1 XCRYPTO_PREFIX %+ _SHA1
%xdefine SHA1_Final XCRYPTO_PREFIX %+ _SHA1_Final
%xdefine SHA1_Init XCRYPTO_PREFIX %+ _SHA1_Init
%xdefine SHA1_Transform XCRYPTO_PREFIX %+ _SHA1_Transform
%xdefine SHA1_Update XCRYPTO_PREFIX %+ _SHA1_Update
%xdefine SHA224 XCRYPTO_PREFIX %+ _SHA224
%xdefine SHA224_Final XCRYPTO_PREFIX %+ _SHA224_Final
%xdefine SHA224_Init XCRYPTO_PREFIX %+ _SHA224_Init
%xdefine SHA224_Update XCRYPTO_PREFIX %+ _SHA224_Update
%xdefine SHA256 XCRYPTO_PREFIX %+ _SHA256
%xdefine SHA256_Final XCRYPTO_PREFIX %+ _SHA256_Final
%xdefine SHA256_Init XCRYPTO_PREFIX %+ _SHA256_Init
%xdefine SHA256_Transform XCRYPTO_PREFIX %+ _SHA256_Transform
%xdefine SHA256_TransformBlocks XCRYPTO_PREFIX %+ _SHA256_TransformBlocks
%xdefine SHA256_Update XCRYPTO_PREFIX %+ _SHA256_Update
%xdefine SHA384 XCRYPTO_PREFIX %+ _SHA384
%xdefine SHA384_Final XCRYPTO_PREFIX %+ _SHA384_Final
%xdefine SHA384_Init XCRYPTO_PREFIX %+ _SHA384_Init
%xdefine SHA384_Update XCRYPTO_PREFIX %+ _SHA384_Update
%xdefine SHA512 XCRYPTO_PREFIX %+ _SHA512
%xdefine SHA512_256 XCRYPTO_PREFIX %+ _SHA512_256
%xdefine SHA512_256_Final XCRYPTO_PREFIX %+ _SHA512_256_Final
%xdefine SHA512_256_Init XCRYPTO_PREFIX %+ _SHA512_256_Init
%xdefine SHA512_256_Update XCRYPTO_PREFIX %+ _SHA512_256_Update
%xdefine SHA512_Final XCRYPTO_PREFIX %+ _SHA512_Final
%xdefine SHA512_Init XCRYPTO_PREFIX %+ _SHA512_Init
%xdefine SHA512_Transform XCRYPTO_PREFIX %+ _SHA512_Transform
%xdefine SHA512_Update XCRYPTO_PREFIX %+ _SHA512_Update
%xdefine SIPHASH_24 XCRYPTO_PREFIX %+ _SIPHASH_24
%xdefine SPAKE2_CTX_free XCRYPTO_PREFIX %+ _SPAKE2_CTX_free
%xdefine SPAKE2_CTX_new XCRYPTO_PREFIX %+ _SPAKE2_CTX_new
%xdefine SPAKE2_generate_msg XCRYPTO_PREFIX %+ _SPAKE2_generate_msg
%xdefine SPAKE2_process_msg XCRYPTO_PREFIX %+ _SPAKE2_process_msg
%xdefine SSL_CIPHER_description XCRYPTO_PREFIX %+ _SSL_CIPHER_description
%xdefine SSL_CIPHER_get_auth_nid XCRYPTO_PREFIX %+ _SSL_CIPHER_get_auth_nid
%xdefine SSL_CIPHER_get_bits XCRYPTO_PREFIX %+ _SSL_CIPHER_get_bits
%xdefine SSL_CIPHER_get_cipher_nid XCRYPTO_PREFIX %+ _SSL_CIPHER_get_cipher_nid
%xdefine SSL_CIPHER_get_digest_nid XCRYPTO_PREFIX %+ _SSL_CIPHER_get_digest_nid
%xdefine SSL_CIPHER_get_id XCRYPTO_PREFIX %+ _SSL_CIPHER_get_id
%xdefine SSL_CIPHER_get_kx_name XCRYPTO_PREFIX %+ _SSL_CIPHER_get_kx_name
%xdefine SSL_CIPHER_get_kx_nid XCRYPTO_PREFIX %+ _SSL_CIPHER_get_kx_nid
%xdefine SSL_CIPHER_get_max_version XCRYPTO_PREFIX %+ _SSL_CIPHER_get_max_version
%xdefine SSL_CIPHER_get_min_version XCRYPTO_PREFIX %+ _SSL_CIPHER_get_min_version
%xdefine SSL_CIPHER_get_name XCRYPTO_PREFIX %+ _SSL_CIPHER_get_name
%xdefine SSL_CIPHER_get_prf_nid XCRYPTO_PREFIX %+ _SSL_CIPHER_get_prf_nid
%xdefine SSL_CIPHER_get_rfc_name XCRYPTO_PREFIX %+ _SSL_CIPHER_get_rfc_name
%xdefine SSL_CIPHER_get_value XCRYPTO_PREFIX %+ _SSL_CIPHER_get_value
%xdefine SSL_CIPHER_get_version XCRYPTO_PREFIX %+ _SSL_CIPHER_get_version
%xdefine SSL_CIPHER_is_aead XCRYPTO_PREFIX %+ _SSL_CIPHER_is_aead
%xdefine SSL_CIPHER_is_block_cipher XCRYPTO_PREFIX %+ _SSL_CIPHER_is_block_cipher
%xdefine SSL_CIPHER_standard_name XCRYPTO_PREFIX %+ _SSL_CIPHER_standard_name
%xdefine SSL_COMP_add_compression_method XCRYPTO_PREFIX %+ _SSL_COMP_add_compression_method
%xdefine SSL_COMP_free_compression_methods XCRYPTO_PREFIX %+ _SSL_COMP_free_compression_methods
%xdefine SSL_COMP_get0_name XCRYPTO_PREFIX %+ _SSL_COMP_get0_name
%xdefine SSL_COMP_get_compression_methods XCRYPTO_PREFIX %+ _SSL_COMP_get_compression_methods
%xdefine SSL_COMP_get_id XCRYPTO_PREFIX %+ _SSL_COMP_get_id
%xdefine SSL_COMP_get_name XCRYPTO_PREFIX %+ _SSL_COMP_get_name
%xdefine SSL_CTX_add0_chain_cert XCRYPTO_PREFIX %+ _SSL_CTX_add0_chain_cert
%xdefine SSL_CTX_add1_chain_cert XCRYPTO_PREFIX %+ _SSL_CTX_add1_chain_cert
%xdefine SSL_CTX_add_cert_compression_alg XCRYPTO_PREFIX %+ _SSL_CTX_add_cert_compression_alg
%xdefine SSL_CTX_add_client_CA XCRYPTO_PREFIX %+ _SSL_CTX_add_client_CA
%xdefine SSL_CTX_add_extra_chain_cert XCRYPTO_PREFIX %+ _SSL_CTX_add_extra_chain_cert
%xdefine SSL_CTX_add_session XCRYPTO_PREFIX %+ _SSL_CTX_add_session
%xdefine SSL_CTX_check_private_key XCRYPTO_PREFIX %+ _SSL_CTX_check_private_key
%xdefine SSL_CTX_cipher_in_group XCRYPTO_PREFIX %+ _SSL_CTX_cipher_in_group
%xdefine SSL_CTX_clear_chain_certs XCRYPTO_PREFIX %+ _SSL_CTX_clear_chain_certs
%xdefine SSL_CTX_clear_extra_chain_certs XCRYPTO_PREFIX %+ _SSL_CTX_clear_extra_chain_certs
%xdefine SSL_CTX_clear_mode XCRYPTO_PREFIX %+ _SSL_CTX_clear_mode
%xdefine SSL_CTX_clear_options XCRYPTO_PREFIX %+ _SSL_CTX_clear_options
%xdefine SSL_CTX_enable_ocsp_stapling XCRYPTO_PREFIX %+ _SSL_CTX_enable_ocsp_stapling
%xdefine SSL_CTX_enable_signed_cert_timestamps XCRYPTO_PREFIX %+ _SSL_CTX_enable_signed_cert_timestamps
%xdefine SSL_CTX_enable_tls_channel_id XCRYPTO_PREFIX %+ _SSL_CTX_enable_tls_channel_id
%xdefine SSL_CTX_flush_sessions XCRYPTO_PREFIX %+ _SSL_CTX_flush_sessions
%xdefine SSL_CTX_free XCRYPTO_PREFIX %+ _SSL_CTX_free
%xdefine SSL_CTX_get0_certificate XCRYPTO_PREFIX %+ _SSL_CTX_get0_certificate
%xdefine SSL_CTX_get0_chain XCRYPTO_PREFIX %+ _SSL_CTX_get0_chain
%xdefine SSL_CTX_get0_chain_certs XCRYPTO_PREFIX %+ _SSL_CTX_get0_chain_certs
%xdefine SSL_CTX_get0_param XCRYPTO_PREFIX %+ _SSL_CTX_get0_param
%xdefine SSL_CTX_get0_privatekey XCRYPTO_PREFIX %+ _SSL_CTX_get0_privatekey
%xdefine SSL_CTX_get_cert_store XCRYPTO_PREFIX %+ _SSL_CTX_get_cert_store
%xdefine SSL_CTX_get_channel_id_cb XCRYPTO_PREFIX %+ _SSL_CTX_get_channel_id_cb
%xdefine SSL_CTX_get_ciphers XCRYPTO_PREFIX %+ _SSL_CTX_get_ciphers
%xdefine SSL_CTX_get_client_CA_list XCRYPTO_PREFIX %+ _SSL_CTX_get_client_CA_list
%xdefine SSL_CTX_get_default_passwd_cb XCRYPTO_PREFIX %+ _SSL_CTX_get_default_passwd_cb
%xdefine SSL_CTX_get_default_passwd_cb_userdata XCRYPTO_PREFIX %+ _SSL_CTX_get_default_passwd_cb_userdata
%xdefine SSL_CTX_get_ex_data XCRYPTO_PREFIX %+ _SSL_CTX_get_ex_data
%xdefine SSL_CTX_get_ex_new_index XCRYPTO_PREFIX %+ _SSL_CTX_get_ex_new_index
%xdefine SSL_CTX_get_extra_chain_certs XCRYPTO_PREFIX %+ _SSL_CTX_get_extra_chain_certs
%xdefine SSL_CTX_get_info_callback XCRYPTO_PREFIX %+ _SSL_CTX_get_info_callback
%xdefine SSL_CTX_get_keylog_callback XCRYPTO_PREFIX %+ _SSL_CTX_get_keylog_callback
%xdefine SSL_CTX_get_max_cert_list XCRYPTO_PREFIX %+ _SSL_CTX_get_max_cert_list
%xdefine SSL_CTX_get_max_proto_version XCRYPTO_PREFIX %+ _SSL_CTX_get_max_proto_version
%xdefine SSL_CTX_get_min_proto_version XCRYPTO_PREFIX %+ _SSL_CTX_get_min_proto_version
%xdefine SSL_CTX_get_mode XCRYPTO_PREFIX %+ _SSL_CTX_get_mode
%xdefine SSL_CTX_get_options XCRYPTO_PREFIX %+ _SSL_CTX_get_options
%xdefine SSL_CTX_get_quiet_shutdown XCRYPTO_PREFIX %+ _SSL_CTX_get_quiet_shutdown
%xdefine SSL_CTX_get_read_ahead XCRYPTO_PREFIX %+ _SSL_CTX_get_read_ahead
%xdefine SSL_CTX_get_session_cache_mode XCRYPTO_PREFIX %+ _SSL_CTX_get_session_cache_mode
%xdefine SSL_CTX_get_timeout XCRYPTO_PREFIX %+ _SSL_CTX_get_timeout
%xdefine SSL_CTX_get_tlsext_ticket_keys XCRYPTO_PREFIX %+ _SSL_CTX_get_tlsext_ticket_keys
%xdefine SSL_CTX_get_verify_callback XCRYPTO_PREFIX %+ _SSL_CTX_get_verify_callback
%xdefine SSL_CTX_get_verify_depth XCRYPTO_PREFIX %+ _SSL_CTX_get_verify_depth
%xdefine SSL_CTX_get_verify_mode XCRYPTO_PREFIX %+ _SSL_CTX_get_verify_mode
%xdefine SSL_CTX_load_verify_locations XCRYPTO_PREFIX %+ _SSL_CTX_load_verify_locations
%xdefine SSL_CTX_need_tmp_RSA XCRYPTO_PREFIX %+ _SSL_CTX_need_tmp_RSA
%xdefine SSL_CTX_new XCRYPTO_PREFIX %+ _SSL_CTX_new
%xdefine SSL_CTX_remove_session XCRYPTO_PREFIX %+ _SSL_CTX_remove_session
%xdefine SSL_CTX_sess_accept XCRYPTO_PREFIX %+ _SSL_CTX_sess_accept
%xdefine SSL_CTX_sess_accept_good XCRYPTO_PREFIX %+ _SSL_CTX_sess_accept_good
%xdefine SSL_CTX_sess_accept_renegotiate XCRYPTO_PREFIX %+ _SSL_CTX_sess_accept_renegotiate
%xdefine SSL_CTX_sess_cache_full XCRYPTO_PREFIX %+ _SSL_CTX_sess_cache_full
%xdefine SSL_CTX_sess_cb_hits XCRYPTO_PREFIX %+ _SSL_CTX_sess_cb_hits
%xdefine SSL_CTX_sess_connect XCRYPTO_PREFIX %+ _SSL_CTX_sess_connect
%xdefine SSL_CTX_sess_connect_good XCRYPTO_PREFIX %+ _SSL_CTX_sess_connect_good
%xdefine SSL_CTX_sess_connect_renegotiate XCRYPTO_PREFIX %+ _SSL_CTX_sess_connect_renegotiate
%xdefine SSL_CTX_sess_get_cache_size XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_cache_size
%xdefine SSL_CTX_sess_get_get_cb XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_get_cb
%xdefine SSL_CTX_sess_get_new_cb XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_new_cb
%xdefine SSL_CTX_sess_get_remove_cb XCRYPTO_PREFIX %+ _SSL_CTX_sess_get_remove_cb
%xdefine SSL_CTX_sess_hits XCRYPTO_PREFIX %+ _SSL_CTX_sess_hits
%xdefine SSL_CTX_sess_misses XCRYPTO_PREFIX %+ _SSL_CTX_sess_misses
%xdefine SSL_CTX_sess_number XCRYPTO_PREFIX %+ _SSL_CTX_sess_number
%xdefine SSL_CTX_sess_set_cache_size XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_cache_size
%xdefine SSL_CTX_sess_set_get_cb XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_get_cb
%xdefine SSL_CTX_sess_set_new_cb XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_new_cb
%xdefine SSL_CTX_sess_set_remove_cb XCRYPTO_PREFIX %+ _SSL_CTX_sess_set_remove_cb
%xdefine SSL_CTX_sess_timeouts XCRYPTO_PREFIX %+ _SSL_CTX_sess_timeouts
%xdefine SSL_CTX_set0_buffer_pool XCRYPTO_PREFIX %+ _SSL_CTX_set0_buffer_pool
%xdefine SSL_CTX_set0_chain XCRYPTO_PREFIX %+ _SSL_CTX_set0_chain
%xdefine SSL_CTX_set0_client_CAs XCRYPTO_PREFIX %+ _SSL_CTX_set0_client_CAs
%xdefine SSL_CTX_set0_verify_cert_store XCRYPTO_PREFIX %+ _SSL_CTX_set0_verify_cert_store
%xdefine SSL_CTX_set1_chain XCRYPTO_PREFIX %+ _SSL_CTX_set1_chain
%xdefine SSL_CTX_set1_curves XCRYPTO_PREFIX %+ _SSL_CTX_set1_curves
%xdefine SSL_CTX_set1_curves_list XCRYPTO_PREFIX %+ _SSL_CTX_set1_curves_list
%xdefine SSL_CTX_set1_param XCRYPTO_PREFIX %+ _SSL_CTX_set1_param
%xdefine SSL_CTX_set1_sigalgs XCRYPTO_PREFIX %+ _SSL_CTX_set1_sigalgs
%xdefine SSL_CTX_set1_sigalgs_list XCRYPTO_PREFIX %+ _SSL_CTX_set1_sigalgs_list
%xdefine SSL_CTX_set1_tls_channel_id XCRYPTO_PREFIX %+ _SSL_CTX_set1_tls_channel_id
%xdefine SSL_CTX_set1_verify_cert_store XCRYPTO_PREFIX %+ _SSL_CTX_set1_verify_cert_store
%xdefine SSL_CTX_set_allow_unknown_alpn_protos XCRYPTO_PREFIX %+ _SSL_CTX_set_allow_unknown_alpn_protos
%xdefine SSL_CTX_set_alpn_protos XCRYPTO_PREFIX %+ _SSL_CTX_set_alpn_protos
%xdefine SSL_CTX_set_alpn_select_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_alpn_select_cb
%xdefine SSL_CTX_set_cert_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_cert_cb
%xdefine SSL_CTX_set_cert_store XCRYPTO_PREFIX %+ _SSL_CTX_set_cert_store
%xdefine SSL_CTX_set_cert_verify_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_cert_verify_callback
%xdefine SSL_CTX_set_chain_and_key XCRYPTO_PREFIX %+ _SSL_CTX_set_chain_and_key
%xdefine SSL_CTX_set_channel_id_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_channel_id_cb
%xdefine SSL_CTX_set_cipher_list XCRYPTO_PREFIX %+ _SSL_CTX_set_cipher_list
%xdefine SSL_CTX_set_client_CA_list XCRYPTO_PREFIX %+ _SSL_CTX_set_client_CA_list
%xdefine SSL_CTX_set_client_cert_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_client_cert_cb
%xdefine SSL_CTX_set_current_time_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_current_time_cb
%xdefine SSL_CTX_set_custom_verify XCRYPTO_PREFIX %+ _SSL_CTX_set_custom_verify
%xdefine SSL_CTX_set_default_passwd_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_default_passwd_cb
%xdefine SSL_CTX_set_default_passwd_cb_userdata XCRYPTO_PREFIX %+ _SSL_CTX_set_default_passwd_cb_userdata
%xdefine SSL_CTX_set_default_verify_paths XCRYPTO_PREFIX %+ _SSL_CTX_set_default_verify_paths
%xdefine SSL_CTX_set_dos_protection_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_dos_protection_cb
%xdefine SSL_CTX_set_early_data_enabled XCRYPTO_PREFIX %+ _SSL_CTX_set_early_data_enabled
%xdefine SSL_CTX_set_ex_data XCRYPTO_PREFIX %+ _SSL_CTX_set_ex_data
%xdefine SSL_CTX_set_false_start_allowed_without_alpn XCRYPTO_PREFIX %+ _SSL_CTX_set_false_start_allowed_without_alpn
%xdefine SSL_CTX_set_grease_enabled XCRYPTO_PREFIX %+ _SSL_CTX_set_grease_enabled
%xdefine SSL_CTX_set_ignore_tls13_downgrade XCRYPTO_PREFIX %+ _SSL_CTX_set_ignore_tls13_downgrade
%xdefine SSL_CTX_set_info_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_info_callback
%xdefine SSL_CTX_set_keylog_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_keylog_callback
%xdefine SSL_CTX_set_max_cert_list XCRYPTO_PREFIX %+ _SSL_CTX_set_max_cert_list
%xdefine SSL_CTX_set_max_proto_version XCRYPTO_PREFIX %+ _SSL_CTX_set_max_proto_version
%xdefine SSL_CTX_set_max_send_fragment XCRYPTO_PREFIX %+ _SSL_CTX_set_max_send_fragment
%xdefine SSL_CTX_set_min_proto_version XCRYPTO_PREFIX %+ _SSL_CTX_set_min_proto_version
%xdefine SSL_CTX_set_mode XCRYPTO_PREFIX %+ _SSL_CTX_set_mode
%xdefine SSL_CTX_set_msg_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_msg_callback
%xdefine SSL_CTX_set_msg_callback_arg XCRYPTO_PREFIX %+ _SSL_CTX_set_msg_callback_arg
%xdefine SSL_CTX_set_next_proto_select_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_next_proto_select_cb
%xdefine SSL_CTX_set_next_protos_advertised_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_next_protos_advertised_cb
%xdefine SSL_CTX_set_ocsp_response XCRYPTO_PREFIX %+ _SSL_CTX_set_ocsp_response
%xdefine SSL_CTX_set_options XCRYPTO_PREFIX %+ _SSL_CTX_set_options
%xdefine SSL_CTX_set_private_key_method XCRYPTO_PREFIX %+ _SSL_CTX_set_private_key_method
%xdefine SSL_CTX_set_psk_client_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_psk_client_callback
%xdefine SSL_CTX_set_psk_server_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_psk_server_callback
%xdefine SSL_CTX_set_purpose XCRYPTO_PREFIX %+ _SSL_CTX_set_purpose
%xdefine SSL_CTX_set_quic_method XCRYPTO_PREFIX %+ _SSL_CTX_set_quic_method
%xdefine SSL_CTX_set_quiet_shutdown XCRYPTO_PREFIX %+ _SSL_CTX_set_quiet_shutdown
%xdefine SSL_CTX_set_read_ahead XCRYPTO_PREFIX %+ _SSL_CTX_set_read_ahead
%xdefine SSL_CTX_set_retain_only_sha256_of_client_certs XCRYPTO_PREFIX %+ _SSL_CTX_set_retain_only_sha256_of_client_certs
%xdefine SSL_CTX_set_reverify_on_resume XCRYPTO_PREFIX %+ _SSL_CTX_set_reverify_on_resume
%xdefine SSL_CTX_set_select_certificate_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_select_certificate_cb
%xdefine SSL_CTX_set_session_cache_mode XCRYPTO_PREFIX %+ _SSL_CTX_set_session_cache_mode
%xdefine SSL_CTX_set_session_id_context XCRYPTO_PREFIX %+ _SSL_CTX_set_session_id_context
%xdefine SSL_CTX_set_session_psk_dhe_timeout XCRYPTO_PREFIX %+ _SSL_CTX_set_session_psk_dhe_timeout
%xdefine SSL_CTX_set_signed_cert_timestamp_list XCRYPTO_PREFIX %+ _SSL_CTX_set_signed_cert_timestamp_list
%xdefine SSL_CTX_set_signing_algorithm_prefs XCRYPTO_PREFIX %+ _SSL_CTX_set_signing_algorithm_prefs
%xdefine SSL_CTX_set_srtp_profiles XCRYPTO_PREFIX %+ _SSL_CTX_set_srtp_profiles
%xdefine SSL_CTX_set_strict_cipher_list XCRYPTO_PREFIX %+ _SSL_CTX_set_strict_cipher_list
%xdefine SSL_CTX_set_ticket_aead_method XCRYPTO_PREFIX %+ _SSL_CTX_set_ticket_aead_method
%xdefine SSL_CTX_set_timeout XCRYPTO_PREFIX %+ _SSL_CTX_set_timeout
%xdefine SSL_CTX_set_tls_channel_id_enabled XCRYPTO_PREFIX %+ _SSL_CTX_set_tls_channel_id_enabled
%xdefine SSL_CTX_set_tlsext_servername_arg XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_servername_arg
%xdefine SSL_CTX_set_tlsext_servername_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_servername_callback
%xdefine SSL_CTX_set_tlsext_status_arg XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_status_arg
%xdefine SSL_CTX_set_tlsext_status_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_status_cb
%xdefine SSL_CTX_set_tlsext_ticket_key_cb XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_ticket_key_cb
%xdefine SSL_CTX_set_tlsext_ticket_keys XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_ticket_keys
%xdefine SSL_CTX_set_tlsext_use_srtp XCRYPTO_PREFIX %+ _SSL_CTX_set_tlsext_use_srtp
%xdefine SSL_CTX_set_tmp_dh XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_dh
%xdefine SSL_CTX_set_tmp_dh_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_dh_callback
%xdefine SSL_CTX_set_tmp_ecdh XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_ecdh
%xdefine SSL_CTX_set_tmp_rsa XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_rsa
%xdefine SSL_CTX_set_tmp_rsa_callback XCRYPTO_PREFIX %+ _SSL_CTX_set_tmp_rsa_callback
%xdefine SSL_CTX_set_trust XCRYPTO_PREFIX %+ _SSL_CTX_set_trust
%xdefine SSL_CTX_set_verify XCRYPTO_PREFIX %+ _SSL_CTX_set_verify
%xdefine SSL_CTX_set_verify_algorithm_prefs XCRYPTO_PREFIX %+ _SSL_CTX_set_verify_algorithm_prefs
%xdefine SSL_CTX_set_verify_depth XCRYPTO_PREFIX %+ _SSL_CTX_set_verify_depth
%xdefine SSL_CTX_up_ref XCRYPTO_PREFIX %+ _SSL_CTX_up_ref
%xdefine SSL_CTX_use_PrivateKey XCRYPTO_PREFIX %+ _SSL_CTX_use_PrivateKey
%xdefine SSL_CTX_use_PrivateKey_ASN1 XCRYPTO_PREFIX %+ _SSL_CTX_use_PrivateKey_ASN1
%xdefine SSL_CTX_use_PrivateKey_file XCRYPTO_PREFIX %+ _SSL_CTX_use_PrivateKey_file
%xdefine SSL_CTX_use_RSAPrivateKey XCRYPTO_PREFIX %+ _SSL_CTX_use_RSAPrivateKey
%xdefine SSL_CTX_use_RSAPrivateKey_ASN1 XCRYPTO_PREFIX %+ _SSL_CTX_use_RSAPrivateKey_ASN1
%xdefine SSL_CTX_use_RSAPrivateKey_file XCRYPTO_PREFIX %+ _SSL_CTX_use_RSAPrivateKey_file
%xdefine SSL_CTX_use_certificate XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate
%xdefine SSL_CTX_use_certificate_ASN1 XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate_ASN1
%xdefine SSL_CTX_use_certificate_chain_file XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate_chain_file
%xdefine SSL_CTX_use_certificate_file XCRYPTO_PREFIX %+ _SSL_CTX_use_certificate_file
%xdefine SSL_CTX_use_psk_identity_hint XCRYPTO_PREFIX %+ _SSL_CTX_use_psk_identity_hint
%xdefine SSL_SESSION_copy_without_early_data XCRYPTO_PREFIX %+ _SSL_SESSION_copy_without_early_data
%xdefine SSL_SESSION_early_data_capable XCRYPTO_PREFIX %+ _SSL_SESSION_early_data_capable
%xdefine SSL_SESSION_free XCRYPTO_PREFIX %+ _SSL_SESSION_free
%xdefine SSL_SESSION_from_bytes XCRYPTO_PREFIX %+ _SSL_SESSION_from_bytes
%xdefine SSL_SESSION_get0_cipher XCRYPTO_PREFIX %+ _SSL_SESSION_get0_cipher
%xdefine SSL_SESSION_get0_id_context XCRYPTO_PREFIX %+ _SSL_SESSION_get0_id_context
%xdefine SSL_SESSION_get0_ocsp_response XCRYPTO_PREFIX %+ _SSL_SESSION_get0_ocsp_response
%xdefine SSL_SESSION_get0_peer XCRYPTO_PREFIX %+ _SSL_SESSION_get0_peer
%xdefine SSL_SESSION_get0_peer_certificates XCRYPTO_PREFIX %+ _SSL_SESSION_get0_peer_certificates
%xdefine SSL_SESSION_get0_peer_sha256 XCRYPTO_PREFIX %+ _SSL_SESSION_get0_peer_sha256
%xdefine SSL_SESSION_get0_signed_cert_timestamp_list XCRYPTO_PREFIX %+ _SSL_SESSION_get0_signed_cert_timestamp_list
%xdefine SSL_SESSION_get0_ticket XCRYPTO_PREFIX %+ _SSL_SESSION_get0_ticket
%xdefine SSL_SESSION_get_ex_data XCRYPTO_PREFIX %+ _SSL_SESSION_get_ex_data
%xdefine SSL_SESSION_get_ex_new_index XCRYPTO_PREFIX %+ _SSL_SESSION_get_ex_new_index
%xdefine SSL_SESSION_get_id XCRYPTO_PREFIX %+ _SSL_SESSION_get_id
%xdefine SSL_SESSION_get_master_key XCRYPTO_PREFIX %+ _SSL_SESSION_get_master_key
%xdefine SSL_SESSION_get_protocol_version XCRYPTO_PREFIX %+ _SSL_SESSION_get_protocol_version
%xdefine SSL_SESSION_get_ticket_lifetime_hint XCRYPTO_PREFIX %+ _SSL_SESSION_get_ticket_lifetime_hint
%xdefine SSL_SESSION_get_time XCRYPTO_PREFIX %+ _SSL_SESSION_get_time
%xdefine SSL_SESSION_get_timeout XCRYPTO_PREFIX %+ _SSL_SESSION_get_timeout
%xdefine SSL_SESSION_get_version XCRYPTO_PREFIX %+ _SSL_SESSION_get_version
%xdefine SSL_SESSION_has_peer_sha256 XCRYPTO_PREFIX %+ _SSL_SESSION_has_peer_sha256
%xdefine SSL_SESSION_has_ticket XCRYPTO_PREFIX %+ _SSL_SESSION_has_ticket
%xdefine SSL_SESSION_is_resumable XCRYPTO_PREFIX %+ _SSL_SESSION_is_resumable
%xdefine SSL_SESSION_new XCRYPTO_PREFIX %+ _SSL_SESSION_new
%xdefine SSL_SESSION_set1_id XCRYPTO_PREFIX %+ _SSL_SESSION_set1_id
%xdefine SSL_SESSION_set1_id_context XCRYPTO_PREFIX %+ _SSL_SESSION_set1_id_context
%xdefine SSL_SESSION_set_ex_data XCRYPTO_PREFIX %+ _SSL_SESSION_set_ex_data
%xdefine SSL_SESSION_set_protocol_version XCRYPTO_PREFIX %+ _SSL_SESSION_set_protocol_version
%xdefine SSL_SESSION_set_ticket XCRYPTO_PREFIX %+ _SSL_SESSION_set_ticket
%xdefine SSL_SESSION_set_time XCRYPTO_PREFIX %+ _SSL_SESSION_set_time
%xdefine SSL_SESSION_set_timeout XCRYPTO_PREFIX %+ _SSL_SESSION_set_timeout
%xdefine SSL_SESSION_should_be_single_use XCRYPTO_PREFIX %+ _SSL_SESSION_should_be_single_use
%xdefine SSL_SESSION_to_bytes XCRYPTO_PREFIX %+ _SSL_SESSION_to_bytes
%xdefine SSL_SESSION_to_bytes_for_ticket XCRYPTO_PREFIX %+ _SSL_SESSION_to_bytes_for_ticket
%xdefine SSL_SESSION_up_ref XCRYPTO_PREFIX %+ _SSL_SESSION_up_ref
%xdefine SSL_accept XCRYPTO_PREFIX %+ _SSL_accept
%xdefine SSL_add0_chain_cert XCRYPTO_PREFIX %+ _SSL_add0_chain_cert
%xdefine SSL_add1_chain_cert XCRYPTO_PREFIX %+ _SSL_add1_chain_cert
%xdefine SSL_add_client_CA XCRYPTO_PREFIX %+ _SSL_add_client_CA
%xdefine SSL_add_file_cert_subjects_to_stack XCRYPTO_PREFIX %+ _SSL_add_file_cert_subjects_to_stack
%xdefine SSL_alert_desc_string XCRYPTO_PREFIX %+ _SSL_alert_desc_string
%xdefine SSL_alert_desc_string_long XCRYPTO_PREFIX %+ _SSL_alert_desc_string_long
%xdefine SSL_alert_from_verify_result XCRYPTO_PREFIX %+ _SSL_alert_from_verify_result
%xdefine SSL_alert_type_string XCRYPTO_PREFIX %+ _SSL_alert_type_string
%xdefine SSL_alert_type_string_long XCRYPTO_PREFIX %+ _SSL_alert_type_string_long
%xdefine SSL_cache_hit XCRYPTO_PREFIX %+ _SSL_cache_hit
%xdefine SSL_certs_clear XCRYPTO_PREFIX %+ _SSL_certs_clear
%xdefine SSL_check_private_key XCRYPTO_PREFIX %+ _SSL_check_private_key
%xdefine SSL_clear XCRYPTO_PREFIX %+ _SSL_clear
%xdefine SSL_clear_chain_certs XCRYPTO_PREFIX %+ _SSL_clear_chain_certs
%xdefine SSL_clear_mode XCRYPTO_PREFIX %+ _SSL_clear_mode
%xdefine SSL_clear_options XCRYPTO_PREFIX %+ _SSL_clear_options
%xdefine SSL_connect XCRYPTO_PREFIX %+ _SSL_connect
%xdefine SSL_cutthrough_complete XCRYPTO_PREFIX %+ _SSL_cutthrough_complete
%xdefine SSL_delegated_credential_used XCRYPTO_PREFIX %+ _SSL_delegated_credential_used
%xdefine SSL_do_handshake XCRYPTO_PREFIX %+ _SSL_do_handshake
%xdefine SSL_dup_CA_list XCRYPTO_PREFIX %+ _SSL_dup_CA_list
%xdefine SSL_early_callback_ctx_extension_get XCRYPTO_PREFIX %+ _SSL_early_callback_ctx_extension_get
%xdefine SSL_early_data_accepted XCRYPTO_PREFIX %+ _SSL_early_data_accepted
%xdefine SSL_enable_ocsp_stapling XCRYPTO_PREFIX %+ _SSL_enable_ocsp_stapling
%xdefine SSL_enable_signed_cert_timestamps XCRYPTO_PREFIX %+ _SSL_enable_signed_cert_timestamps
%xdefine SSL_enable_tls_channel_id XCRYPTO_PREFIX %+ _SSL_enable_tls_channel_id
%xdefine SSL_error_description XCRYPTO_PREFIX %+ _SSL_error_description
%xdefine SSL_export_keying_material XCRYPTO_PREFIX %+ _SSL_export_keying_material
%xdefine SSL_free XCRYPTO_PREFIX %+ _SSL_free
%xdefine SSL_generate_key_block XCRYPTO_PREFIX %+ _SSL_generate_key_block
%xdefine SSL_get0_alpn_selected XCRYPTO_PREFIX %+ _SSL_get0_alpn_selected
%xdefine SSL_get0_certificate_types XCRYPTO_PREFIX %+ _SSL_get0_certificate_types
%xdefine SSL_get0_chain_certs XCRYPTO_PREFIX %+ _SSL_get0_chain_certs
%xdefine SSL_get0_next_proto_negotiated XCRYPTO_PREFIX %+ _SSL_get0_next_proto_negotiated
%xdefine SSL_get0_ocsp_response XCRYPTO_PREFIX %+ _SSL_get0_ocsp_response
%xdefine SSL_get0_param XCRYPTO_PREFIX %+ _SSL_get0_param
%xdefine SSL_get0_peer_certificates XCRYPTO_PREFIX %+ _SSL_get0_peer_certificates
%xdefine SSL_get0_peer_verify_algorithms XCRYPTO_PREFIX %+ _SSL_get0_peer_verify_algorithms
%xdefine SSL_get0_server_requested_CAs XCRYPTO_PREFIX %+ _SSL_get0_server_requested_CAs
%xdefine SSL_get0_session_id_context XCRYPTO_PREFIX %+ _SSL_get0_session_id_context
%xdefine SSL_get0_signed_cert_timestamp_list XCRYPTO_PREFIX %+ _SSL_get0_signed_cert_timestamp_list
%xdefine SSL_get1_session XCRYPTO_PREFIX %+ _SSL_get1_session
%xdefine SSL_get_SSL_CTX XCRYPTO_PREFIX %+ _SSL_get_SSL_CTX
%xdefine SSL_get_certificate XCRYPTO_PREFIX %+ _SSL_get_certificate
%xdefine SSL_get_cipher_by_value XCRYPTO_PREFIX %+ _SSL_get_cipher_by_value
%xdefine SSL_get_cipher_list XCRYPTO_PREFIX %+ _SSL_get_cipher_list
%xdefine SSL_get_ciphers XCRYPTO_PREFIX %+ _SSL_get_ciphers
%xdefine SSL_get_client_CA_list XCRYPTO_PREFIX %+ _SSL_get_client_CA_list
%xdefine SSL_get_client_random XCRYPTO_PREFIX %+ _SSL_get_client_random
%xdefine SSL_get_current_cipher XCRYPTO_PREFIX %+ _SSL_get_current_cipher
%xdefine SSL_get_current_compression XCRYPTO_PREFIX %+ _SSL_get_current_compression
%xdefine SSL_get_current_expansion XCRYPTO_PREFIX %+ _SSL_get_current_expansion
%xdefine SSL_get_curve_id XCRYPTO_PREFIX %+ _SSL_get_curve_id
%xdefine SSL_get_curve_name XCRYPTO_PREFIX %+ _SSL_get_curve_name
%xdefine SSL_get_default_timeout XCRYPTO_PREFIX %+ _SSL_get_default_timeout
%xdefine SSL_get_early_data_reason XCRYPTO_PREFIX %+ _SSL_get_early_data_reason
%xdefine SSL_get_error XCRYPTO_PREFIX %+ _SSL_get_error
%xdefine SSL_get_ex_data XCRYPTO_PREFIX %+ _SSL_get_ex_data
%xdefine SSL_get_ex_data_X509_STORE_CTX_idx XCRYPTO_PREFIX %+ _SSL_get_ex_data_X509_STORE_CTX_idx
%xdefine SSL_get_ex_new_index XCRYPTO_PREFIX %+ _SSL_get_ex_new_index
%xdefine SSL_get_extms_support XCRYPTO_PREFIX %+ _SSL_get_extms_support
%xdefine SSL_get_fd XCRYPTO_PREFIX %+ _SSL_get_fd
%xdefine SSL_get_finished XCRYPTO_PREFIX %+ _SSL_get_finished
%xdefine SSL_get_info_callback XCRYPTO_PREFIX %+ _SSL_get_info_callback
%xdefine SSL_get_ivs XCRYPTO_PREFIX %+ _SSL_get_ivs
%xdefine SSL_get_key_block_len XCRYPTO_PREFIX %+ _SSL_get_key_block_len
%xdefine SSL_get_max_cert_list XCRYPTO_PREFIX %+ _SSL_get_max_cert_list
%xdefine SSL_get_max_proto_version XCRYPTO_PREFIX %+ _SSL_get_max_proto_version
%xdefine SSL_get_min_proto_version XCRYPTO_PREFIX %+ _SSL_get_min_proto_version
%xdefine SSL_get_mode XCRYPTO_PREFIX %+ _SSL_get_mode
%xdefine SSL_get_negotiated_token_binding_param XCRYPTO_PREFIX %+ _SSL_get_negotiated_token_binding_param
%xdefine SSL_get_options XCRYPTO_PREFIX %+ _SSL_get_options
%xdefine SSL_get_peer_cert_chain XCRYPTO_PREFIX %+ _SSL_get_peer_cert_chain
%xdefine SSL_get_peer_certificate XCRYPTO_PREFIX %+ _SSL_get_peer_certificate
%xdefine SSL_get_peer_finished XCRYPTO_PREFIX %+ _SSL_get_peer_finished
%xdefine SSL_get_peer_full_cert_chain XCRYPTO_PREFIX %+ _SSL_get_peer_full_cert_chain
%xdefine SSL_get_peer_quic_transport_params XCRYPTO_PREFIX %+ _SSL_get_peer_quic_transport_params
%xdefine SSL_get_peer_signature_algorithm XCRYPTO_PREFIX %+ _SSL_get_peer_signature_algorithm
%xdefine SSL_get_pending_cipher XCRYPTO_PREFIX %+ _SSL_get_pending_cipher
%xdefine SSL_get_privatekey XCRYPTO_PREFIX %+ _SSL_get_privatekey
%xdefine SSL_get_psk_identity XCRYPTO_PREFIX %+ _SSL_get_psk_identity
%xdefine SSL_get_psk_identity_hint XCRYPTO_PREFIX %+ _SSL_get_psk_identity_hint
%xdefine SSL_get_quiet_shutdown XCRYPTO_PREFIX %+ _SSL_get_quiet_shutdown
%xdefine SSL_get_rbio XCRYPTO_PREFIX %+ _SSL_get_rbio
%xdefine SSL_get_read_ahead XCRYPTO_PREFIX %+ _SSL_get_read_ahead
%xdefine SSL_get_read_sequence XCRYPTO_PREFIX %+ _SSL_get_read_sequence
%xdefine SSL_get_rfd XCRYPTO_PREFIX %+ _SSL_get_rfd
%xdefine SSL_get_secure_renegotiation_support XCRYPTO_PREFIX %+ _SSL_get_secure_renegotiation_support
%xdefine SSL_get_selected_srtp_profile XCRYPTO_PREFIX %+ _SSL_get_selected_srtp_profile
%xdefine SSL_get_server_random XCRYPTO_PREFIX %+ _SSL_get_server_random
%xdefine SSL_get_server_tmp_key XCRYPTO_PREFIX %+ _SSL_get_server_tmp_key
%xdefine SSL_get_servername XCRYPTO_PREFIX %+ _SSL_get_servername
%xdefine SSL_get_servername_type XCRYPTO_PREFIX %+ _SSL_get_servername_type
%xdefine SSL_get_session XCRYPTO_PREFIX %+ _SSL_get_session
%xdefine SSL_get_shared_ciphers XCRYPTO_PREFIX %+ _SSL_get_shared_ciphers
%xdefine SSL_get_shared_sigalgs XCRYPTO_PREFIX %+ _SSL_get_shared_sigalgs
%xdefine SSL_get_shutdown XCRYPTO_PREFIX %+ _SSL_get_shutdown
%xdefine SSL_get_signature_algorithm_digest XCRYPTO_PREFIX %+ _SSL_get_signature_algorithm_digest
%xdefine SSL_get_signature_algorithm_key_type XCRYPTO_PREFIX %+ _SSL_get_signature_algorithm_key_type
%xdefine SSL_get_signature_algorithm_name XCRYPTO_PREFIX %+ _SSL_get_signature_algorithm_name
%xdefine SSL_get_srtp_profiles XCRYPTO_PREFIX %+ _SSL_get_srtp_profiles
%xdefine SSL_get_ticket_age_skew XCRYPTO_PREFIX %+ _SSL_get_ticket_age_skew
%xdefine SSL_get_tls_channel_id XCRYPTO_PREFIX %+ _SSL_get_tls_channel_id
%xdefine SSL_get_tls_unique XCRYPTO_PREFIX %+ _SSL_get_tls_unique
%xdefine SSL_get_tlsext_status_ocsp_resp XCRYPTO_PREFIX %+ _SSL_get_tlsext_status_ocsp_resp
%xdefine SSL_get_tlsext_status_type XCRYPTO_PREFIX %+ _SSL_get_tlsext_status_type
%xdefine SSL_get_verify_callback XCRYPTO_PREFIX %+ _SSL_get_verify_callback
%xdefine SSL_get_verify_depth XCRYPTO_PREFIX %+ _SSL_get_verify_depth
%xdefine SSL_get_verify_mode XCRYPTO_PREFIX %+ _SSL_get_verify_mode
%xdefine SSL_get_verify_result XCRYPTO_PREFIX %+ _SSL_get_verify_result
%xdefine SSL_get_version XCRYPTO_PREFIX %+ _SSL_get_version
%xdefine SSL_get_wbio XCRYPTO_PREFIX %+ _SSL_get_wbio
%xdefine SSL_get_wfd XCRYPTO_PREFIX %+ _SSL_get_wfd
%xdefine SSL_get_write_sequence XCRYPTO_PREFIX %+ _SSL_get_write_sequence
%xdefine SSL_in_early_data XCRYPTO_PREFIX %+ _SSL_in_early_data
%xdefine SSL_in_false_start XCRYPTO_PREFIX %+ _SSL_in_false_start
%xdefine SSL_in_init XCRYPTO_PREFIX %+ _SSL_in_init
%xdefine SSL_is_dtls XCRYPTO_PREFIX %+ _SSL_is_dtls
%xdefine SSL_is_init_finished XCRYPTO_PREFIX %+ _SSL_is_init_finished
%xdefine SSL_is_server XCRYPTO_PREFIX %+ _SSL_is_server
%xdefine SSL_is_signature_algorithm_rsa_pss XCRYPTO_PREFIX %+ _SSL_is_signature_algorithm_rsa_pss
%xdefine SSL_is_tls13_downgrade XCRYPTO_PREFIX %+ _SSL_is_tls13_downgrade
%xdefine SSL_is_token_binding_negotiated XCRYPTO_PREFIX %+ _SSL_is_token_binding_negotiated
%xdefine SSL_key_update XCRYPTO_PREFIX %+ _SSL_key_update
%xdefine SSL_library_init XCRYPTO_PREFIX %+ _SSL_library_init
%xdefine SSL_load_client_CA_file XCRYPTO_PREFIX %+ _SSL_load_client_CA_file
%xdefine SSL_load_error_strings XCRYPTO_PREFIX %+ _SSL_load_error_strings
%xdefine SSL_magic_pending_session_ptr XCRYPTO_PREFIX %+ _SSL_magic_pending_session_ptr
%xdefine SSL_max_seal_overhead XCRYPTO_PREFIX %+ _SSL_max_seal_overhead
%xdefine SSL_need_tmp_RSA XCRYPTO_PREFIX %+ _SSL_need_tmp_RSA
%xdefine SSL_new XCRYPTO_PREFIX %+ _SSL_new
%xdefine SSL_num_renegotiations XCRYPTO_PREFIX %+ _SSL_num_renegotiations
%xdefine SSL_peek XCRYPTO_PREFIX %+ _SSL_peek
%xdefine SSL_pending XCRYPTO_PREFIX %+ _SSL_pending
%xdefine SSL_process_quic_post_handshake XCRYPTO_PREFIX %+ _SSL_process_quic_post_handshake
%xdefine SSL_provide_quic_data XCRYPTO_PREFIX %+ _SSL_provide_quic_data
%xdefine SSL_quic_max_handshake_flight_len XCRYPTO_PREFIX %+ _SSL_quic_max_handshake_flight_len
%xdefine SSL_quic_read_level XCRYPTO_PREFIX %+ _SSL_quic_read_level
%xdefine SSL_quic_write_level XCRYPTO_PREFIX %+ _SSL_quic_write_level
%xdefine SSL_read XCRYPTO_PREFIX %+ _SSL_read
%xdefine SSL_renegotiate XCRYPTO_PREFIX %+ _SSL_renegotiate
%xdefine SSL_renegotiate_pending XCRYPTO_PREFIX %+ _SSL_renegotiate_pending
%xdefine SSL_reset_early_data_reject XCRYPTO_PREFIX %+ _SSL_reset_early_data_reject
%xdefine SSL_select_next_proto XCRYPTO_PREFIX %+ _SSL_select_next_proto
%xdefine SSL_send_fatal_alert XCRYPTO_PREFIX %+ _SSL_send_fatal_alert
%xdefine SSL_session_reused XCRYPTO_PREFIX %+ _SSL_session_reused
%xdefine SSL_set0_chain XCRYPTO_PREFIX %+ _SSL_set0_chain
%xdefine SSL_set0_client_CAs XCRYPTO_PREFIX %+ _SSL_set0_client_CAs
%xdefine SSL_set0_rbio XCRYPTO_PREFIX %+ _SSL_set0_rbio
%xdefine SSL_set0_verify_cert_store XCRYPTO_PREFIX %+ _SSL_set0_verify_cert_store
%xdefine SSL_set0_wbio XCRYPTO_PREFIX %+ _SSL_set0_wbio
%xdefine SSL_set1_chain XCRYPTO_PREFIX %+ _SSL_set1_chain
%xdefine SSL_set1_curves XCRYPTO_PREFIX %+ _SSL_set1_curves
%xdefine SSL_set1_curves_list XCRYPTO_PREFIX %+ _SSL_set1_curves_list
%xdefine SSL_set1_delegated_credential XCRYPTO_PREFIX %+ _SSL_set1_delegated_credential
%xdefine SSL_set1_param XCRYPTO_PREFIX %+ _SSL_set1_param
%xdefine SSL_set1_sigalgs XCRYPTO_PREFIX %+ _SSL_set1_sigalgs
%xdefine SSL_set1_sigalgs_list XCRYPTO_PREFIX %+ _SSL_set1_sigalgs_list
%xdefine SSL_set1_tls_channel_id XCRYPTO_PREFIX %+ _SSL_set1_tls_channel_id
%xdefine SSL_set1_verify_cert_store XCRYPTO_PREFIX %+ _SSL_set1_verify_cert_store
%xdefine SSL_set_SSL_CTX XCRYPTO_PREFIX %+ _SSL_set_SSL_CTX
%xdefine SSL_set_accept_state XCRYPTO_PREFIX %+ _SSL_set_accept_state
%xdefine SSL_set_alpn_protos XCRYPTO_PREFIX %+ _SSL_set_alpn_protos
%xdefine SSL_set_bio XCRYPTO_PREFIX %+ _SSL_set_bio
%xdefine SSL_set_cert_cb XCRYPTO_PREFIX %+ _SSL_set_cert_cb
%xdefine SSL_set_chain_and_key XCRYPTO_PREFIX %+ _SSL_set_chain_and_key
%xdefine SSL_set_cipher_list XCRYPTO_PREFIX %+ _SSL_set_cipher_list
%xdefine SSL_set_client_CA_list XCRYPTO_PREFIX %+ _SSL_set_client_CA_list
%xdefine SSL_set_connect_state XCRYPTO_PREFIX %+ _SSL_set_connect_state
%xdefine SSL_set_custom_verify XCRYPTO_PREFIX %+ _SSL_set_custom_verify
%xdefine SSL_set_early_data_enabled XCRYPTO_PREFIX %+ _SSL_set_early_data_enabled
%xdefine SSL_set_enforce_rsa_key_usage XCRYPTO_PREFIX %+ _SSL_set_enforce_rsa_key_usage
%xdefine SSL_set_ex_data XCRYPTO_PREFIX %+ _SSL_set_ex_data
%xdefine SSL_set_fd XCRYPTO_PREFIX %+ _SSL_set_fd
%xdefine SSL_set_ignore_tls13_downgrade XCRYPTO_PREFIX %+ _SSL_set_ignore_tls13_downgrade
%xdefine SSL_set_info_callback XCRYPTO_PREFIX %+ _SSL_set_info_callback
%xdefine SSL_set_jdk11_workaround XCRYPTO_PREFIX %+ _SSL_set_jdk11_workaround
%xdefine SSL_set_max_cert_list XCRYPTO_PREFIX %+ _SSL_set_max_cert_list
%xdefine SSL_set_max_proto_version XCRYPTO_PREFIX %+ _SSL_set_max_proto_version
%xdefine SSL_set_max_send_fragment XCRYPTO_PREFIX %+ _SSL_set_max_send_fragment
%xdefine SSL_set_min_proto_version XCRYPTO_PREFIX %+ _SSL_set_min_proto_version
%xdefine SSL_set_mode XCRYPTO_PREFIX %+ _SSL_set_mode
%xdefine SSL_set_msg_callback XCRYPTO_PREFIX %+ _SSL_set_msg_callback
%xdefine SSL_set_msg_callback_arg XCRYPTO_PREFIX %+ _SSL_set_msg_callback_arg
%xdefine SSL_set_mtu XCRYPTO_PREFIX %+ _SSL_set_mtu
%xdefine SSL_set_ocsp_response XCRYPTO_PREFIX %+ _SSL_set_ocsp_response
%xdefine SSL_set_options XCRYPTO_PREFIX %+ _SSL_set_options
%xdefine SSL_set_private_key_method XCRYPTO_PREFIX %+ _SSL_set_private_key_method
%xdefine SSL_set_psk_client_callback XCRYPTO_PREFIX %+ _SSL_set_psk_client_callback
%xdefine SSL_set_psk_server_callback XCRYPTO_PREFIX %+ _SSL_set_psk_server_callback
%xdefine SSL_set_purpose XCRYPTO_PREFIX %+ _SSL_set_purpose
%xdefine SSL_set_quic_early_data_context XCRYPTO_PREFIX %+ _SSL_set_quic_early_data_context
%xdefine SSL_set_quic_method XCRYPTO_PREFIX %+ _SSL_set_quic_method
%xdefine SSL_set_quic_transport_params XCRYPTO_PREFIX %+ _SSL_set_quic_transport_params
%xdefine SSL_set_quiet_shutdown XCRYPTO_PREFIX %+ _SSL_set_quiet_shutdown
%xdefine SSL_set_read_ahead XCRYPTO_PREFIX %+ _SSL_set_read_ahead
%xdefine SSL_set_renegotiate_mode XCRYPTO_PREFIX %+ _SSL_set_renegotiate_mode
%xdefine SSL_set_retain_only_sha256_of_client_certs XCRYPTO_PREFIX %+ _SSL_set_retain_only_sha256_of_client_certs
%xdefine SSL_set_rfd XCRYPTO_PREFIX %+ _SSL_set_rfd
%xdefine SSL_set_session XCRYPTO_PREFIX %+ _SSL_set_session
%xdefine SSL_set_session_id_context XCRYPTO_PREFIX %+ _SSL_set_session_id_context
%xdefine SSL_set_shed_handshake_config XCRYPTO_PREFIX %+ _SSL_set_shed_handshake_config
%xdefine SSL_set_shutdown XCRYPTO_PREFIX %+ _SSL_set_shutdown
%xdefine SSL_set_signed_cert_timestamp_list XCRYPTO_PREFIX %+ _SSL_set_signed_cert_timestamp_list
%xdefine SSL_set_signing_algorithm_prefs XCRYPTO_PREFIX %+ _SSL_set_signing_algorithm_prefs
%xdefine SSL_set_srtp_profiles XCRYPTO_PREFIX %+ _SSL_set_srtp_profiles
%xdefine SSL_set_state XCRYPTO_PREFIX %+ _SSL_set_state
%xdefine SSL_set_strict_cipher_list XCRYPTO_PREFIX %+ _SSL_set_strict_cipher_list
%xdefine SSL_set_tls_channel_id_enabled XCRYPTO_PREFIX %+ _SSL_set_tls_channel_id_enabled
%xdefine SSL_set_tlsext_host_name XCRYPTO_PREFIX %+ _SSL_set_tlsext_host_name
%xdefine SSL_set_tlsext_status_ocsp_resp XCRYPTO_PREFIX %+ _SSL_set_tlsext_status_ocsp_resp
%xdefine SSL_set_tlsext_status_type XCRYPTO_PREFIX %+ _SSL_set_tlsext_status_type
%xdefine SSL_set_tlsext_use_srtp XCRYPTO_PREFIX %+ _SSL_set_tlsext_use_srtp
%xdefine SSL_set_tmp_dh XCRYPTO_PREFIX %+ _SSL_set_tmp_dh
%xdefine SSL_set_tmp_dh_callback XCRYPTO_PREFIX %+ _SSL_set_tmp_dh_callback
%xdefine SSL_set_tmp_ecdh XCRYPTO_PREFIX %+ _SSL_set_tmp_ecdh
%xdefine SSL_set_tmp_rsa XCRYPTO_PREFIX %+ _SSL_set_tmp_rsa
%xdefine SSL_set_tmp_rsa_callback XCRYPTO_PREFIX %+ _SSL_set_tmp_rsa_callback
%xdefine SSL_set_token_binding_params XCRYPTO_PREFIX %+ _SSL_set_token_binding_params
%xdefine SSL_set_trust XCRYPTO_PREFIX %+ _SSL_set_trust
%xdefine SSL_set_verify XCRYPTO_PREFIX %+ _SSL_set_verify
%xdefine SSL_set_verify_algorithm_prefs XCRYPTO_PREFIX %+ _SSL_set_verify_algorithm_prefs
%xdefine SSL_set_verify_depth XCRYPTO_PREFIX %+ _SSL_set_verify_depth
%xdefine SSL_set_verify_result XCRYPTO_PREFIX %+ _SSL_set_verify_result
%xdefine SSL_set_wfd XCRYPTO_PREFIX %+ _SSL_set_wfd
%xdefine SSL_shutdown XCRYPTO_PREFIX %+ _SSL_shutdown
%xdefine SSL_state XCRYPTO_PREFIX %+ _SSL_state
%xdefine SSL_state_string XCRYPTO_PREFIX %+ _SSL_state_string
%xdefine SSL_state_string_long XCRYPTO_PREFIX %+ _SSL_state_string_long
%xdefine SSL_total_renegotiations XCRYPTO_PREFIX %+ _SSL_total_renegotiations
%xdefine SSL_use_PrivateKey XCRYPTO_PREFIX %+ _SSL_use_PrivateKey
%xdefine SSL_use_PrivateKey_ASN1 XCRYPTO_PREFIX %+ _SSL_use_PrivateKey_ASN1
%xdefine SSL_use_PrivateKey_file XCRYPTO_PREFIX %+ _SSL_use_PrivateKey_file
%xdefine SSL_use_RSAPrivateKey XCRYPTO_PREFIX %+ _SSL_use_RSAPrivateKey
%xdefine SSL_use_RSAPrivateKey_ASN1 XCRYPTO_PREFIX %+ _SSL_use_RSAPrivateKey_ASN1
%xdefine SSL_use_RSAPrivateKey_file XCRYPTO_PREFIX %+ _SSL_use_RSAPrivateKey_file
%xdefine SSL_use_certificate XCRYPTO_PREFIX %+ _SSL_use_certificate
%xdefine SSL_use_certificate_ASN1 XCRYPTO_PREFIX %+ _SSL_use_certificate_ASN1
%xdefine SSL_use_certificate_file XCRYPTO_PREFIX %+ _SSL_use_certificate_file
%xdefine SSL_use_psk_identity_hint XCRYPTO_PREFIX %+ _SSL_use_psk_identity_hint
%xdefine SSL_used_hello_retry_request XCRYPTO_PREFIX %+ _SSL_used_hello_retry_request
%xdefine SSL_version XCRYPTO_PREFIX %+ _SSL_version
%xdefine SSL_want XCRYPTO_PREFIX %+ _SSL_want
%xdefine SSL_write XCRYPTO_PREFIX %+ _SSL_write
%xdefine SSLeay XCRYPTO_PREFIX %+ _SSLeay
%xdefine SSLeay_version XCRYPTO_PREFIX %+ _SSLeay_version
%xdefine SSLv23_client_method XCRYPTO_PREFIX %+ _SSLv23_client_method
%xdefine SSLv23_method XCRYPTO_PREFIX %+ _SSLv23_method
%xdefine SSLv23_server_method XCRYPTO_PREFIX %+ _SSLv23_server_method
%xdefine SXNETID_free XCRYPTO_PREFIX %+ _SXNETID_free
%xdefine SXNETID_it XCRYPTO_PREFIX %+ _SXNETID_it
%xdefine SXNETID_new XCRYPTO_PREFIX %+ _SXNETID_new
%xdefine SXNET_add_id_INTEGER XCRYPTO_PREFIX %+ _SXNET_add_id_INTEGER
%xdefine SXNET_add_id_asc XCRYPTO_PREFIX %+ _SXNET_add_id_asc
%xdefine SXNET_add_id_ulong XCRYPTO_PREFIX %+ _SXNET_add_id_ulong
%xdefine SXNET_free XCRYPTO_PREFIX %+ _SXNET_free
%xdefine SXNET_get_id_INTEGER XCRYPTO_PREFIX %+ _SXNET_get_id_INTEGER
%xdefine SXNET_get_id_asc XCRYPTO_PREFIX %+ _SXNET_get_id_asc
%xdefine SXNET_get_id_ulong XCRYPTO_PREFIX %+ _SXNET_get_id_ulong
%xdefine SXNET_it XCRYPTO_PREFIX %+ _SXNET_it
%xdefine SXNET_new XCRYPTO_PREFIX %+ _SXNET_new
%xdefine TLS_client_method XCRYPTO_PREFIX %+ _TLS_client_method
%xdefine TLS_method XCRYPTO_PREFIX %+ _TLS_method
%xdefine TLS_server_method XCRYPTO_PREFIX %+ _TLS_server_method
%xdefine TLS_with_buffers_method XCRYPTO_PREFIX %+ _TLS_with_buffers_method
%xdefine TLSv1_1_client_method XCRYPTO_PREFIX %+ _TLSv1_1_client_method
%xdefine TLSv1_1_method XCRYPTO_PREFIX %+ _TLSv1_1_method
%xdefine TLSv1_1_server_method XCRYPTO_PREFIX %+ _TLSv1_1_server_method
%xdefine TLSv1_2_client_method XCRYPTO_PREFIX %+ _TLSv1_2_client_method
%xdefine TLSv1_2_method XCRYPTO_PREFIX %+ _TLSv1_2_method
%xdefine TLSv1_2_server_method XCRYPTO_PREFIX %+ _TLSv1_2_server_method
%xdefine TLSv1_client_method XCRYPTO_PREFIX %+ _TLSv1_client_method
%xdefine TLSv1_method XCRYPTO_PREFIX %+ _TLSv1_method
%xdefine TLSv1_server_method XCRYPTO_PREFIX %+ _TLSv1_server_method
%xdefine TRUST_TOKEN_CLIENT_add_key XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_add_key
%xdefine TRUST_TOKEN_CLIENT_begin_issuance XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_begin_issuance
%xdefine TRUST_TOKEN_CLIENT_begin_redemption XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_begin_redemption
%xdefine TRUST_TOKEN_CLIENT_finish_issuance XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_finish_issuance
%xdefine TRUST_TOKEN_CLIENT_finish_redemption XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_finish_redemption
%xdefine TRUST_TOKEN_CLIENT_free XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_free
%xdefine TRUST_TOKEN_CLIENT_new XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_new
%xdefine TRUST_TOKEN_CLIENT_set_srr_key XCRYPTO_PREFIX %+ _TRUST_TOKEN_CLIENT_set_srr_key
%xdefine TRUST_TOKEN_ISSUER_add_key XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_add_key
%xdefine TRUST_TOKEN_ISSUER_free XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_free
%xdefine TRUST_TOKEN_ISSUER_issue XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_issue
%xdefine TRUST_TOKEN_ISSUER_new XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_new
%xdefine TRUST_TOKEN_ISSUER_redeem XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_redeem
%xdefine TRUST_TOKEN_ISSUER_set_metadata_key XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_set_metadata_key
%xdefine TRUST_TOKEN_ISSUER_set_srr_key XCRYPTO_PREFIX %+ _TRUST_TOKEN_ISSUER_set_srr_key
%xdefine TRUST_TOKEN_decode_private_metadata XCRYPTO_PREFIX %+ _TRUST_TOKEN_decode_private_metadata
%xdefine TRUST_TOKEN_experiment_v0 XCRYPTO_PREFIX %+ _TRUST_TOKEN_experiment_v0
%xdefine TRUST_TOKEN_experiment_v1 XCRYPTO_PREFIX %+ _TRUST_TOKEN_experiment_v1
%xdefine TRUST_TOKEN_free XCRYPTO_PREFIX %+ _TRUST_TOKEN_free
%xdefine TRUST_TOKEN_generate_key XCRYPTO_PREFIX %+ _TRUST_TOKEN_generate_key
%xdefine TRUST_TOKEN_new XCRYPTO_PREFIX %+ _TRUST_TOKEN_new
%xdefine USERNOTICE_free XCRYPTO_PREFIX %+ _USERNOTICE_free
%xdefine USERNOTICE_it XCRYPTO_PREFIX %+ _USERNOTICE_it
%xdefine USERNOTICE_new XCRYPTO_PREFIX %+ _USERNOTICE_new
%xdefine UTF8_getc XCRYPTO_PREFIX %+ _UTF8_getc
%xdefine UTF8_putc XCRYPTO_PREFIX %+ _UTF8_putc
%xdefine X25519 XCRYPTO_PREFIX %+ _X25519
%xdefine X25519_keypair XCRYPTO_PREFIX %+ _X25519_keypair
%xdefine X25519_public_from_private XCRYPTO_PREFIX %+ _X25519_public_from_private
%xdefine X509V3_EXT_CRL_add_nconf XCRYPTO_PREFIX %+ _X509V3_EXT_CRL_add_nconf
%xdefine X509V3_EXT_REQ_add_nconf XCRYPTO_PREFIX %+ _X509V3_EXT_REQ_add_nconf
%xdefine X509V3_EXT_add XCRYPTO_PREFIX %+ _X509V3_EXT_add
%xdefine X509V3_EXT_add_alias XCRYPTO_PREFIX %+ _X509V3_EXT_add_alias
%xdefine X509V3_EXT_add_list XCRYPTO_PREFIX %+ _X509V3_EXT_add_list
%xdefine X509V3_EXT_add_nconf XCRYPTO_PREFIX %+ _X509V3_EXT_add_nconf
%xdefine X509V3_EXT_add_nconf_sk XCRYPTO_PREFIX %+ _X509V3_EXT_add_nconf_sk
%xdefine X509V3_EXT_cleanup XCRYPTO_PREFIX %+ _X509V3_EXT_cleanup
%xdefine X509V3_EXT_d2i XCRYPTO_PREFIX %+ _X509V3_EXT_d2i
%xdefine X509V3_EXT_free XCRYPTO_PREFIX %+ _X509V3_EXT_free
%xdefine X509V3_EXT_get XCRYPTO_PREFIX %+ _X509V3_EXT_get
%xdefine X509V3_EXT_get_nid XCRYPTO_PREFIX %+ _X509V3_EXT_get_nid
%xdefine X509V3_EXT_i2d XCRYPTO_PREFIX %+ _X509V3_EXT_i2d
%xdefine X509V3_EXT_nconf XCRYPTO_PREFIX %+ _X509V3_EXT_nconf
%xdefine X509V3_EXT_nconf_nid XCRYPTO_PREFIX %+ _X509V3_EXT_nconf_nid
%xdefine X509V3_EXT_print XCRYPTO_PREFIX %+ _X509V3_EXT_print
%xdefine X509V3_EXT_print_fp XCRYPTO_PREFIX %+ _X509V3_EXT_print_fp
%xdefine X509V3_EXT_val_prn XCRYPTO_PREFIX %+ _X509V3_EXT_val_prn
%xdefine X509V3_NAME_from_section XCRYPTO_PREFIX %+ _X509V3_NAME_from_section
%xdefine X509V3_add1_i2d XCRYPTO_PREFIX %+ _X509V3_add1_i2d
%xdefine X509V3_add_standard_extensions XCRYPTO_PREFIX %+ _X509V3_add_standard_extensions
%xdefine X509V3_add_value XCRYPTO_PREFIX %+ _X509V3_add_value
%xdefine X509V3_add_value_bool XCRYPTO_PREFIX %+ _X509V3_add_value_bool
%xdefine X509V3_add_value_bool_nf XCRYPTO_PREFIX %+ _X509V3_add_value_bool_nf
%xdefine X509V3_add_value_int XCRYPTO_PREFIX %+ _X509V3_add_value_int
%xdefine X509V3_add_value_uchar XCRYPTO_PREFIX %+ _X509V3_add_value_uchar
%xdefine X509V3_conf_free XCRYPTO_PREFIX %+ _X509V3_conf_free
%xdefine X509V3_extensions_print XCRYPTO_PREFIX %+ _X509V3_extensions_print
%xdefine X509V3_get_d2i XCRYPTO_PREFIX %+ _X509V3_get_d2i
%xdefine X509V3_get_section XCRYPTO_PREFIX %+ _X509V3_get_section
%xdefine X509V3_get_string XCRYPTO_PREFIX %+ _X509V3_get_string
%xdefine X509V3_get_value_bool XCRYPTO_PREFIX %+ _X509V3_get_value_bool
%xdefine X509V3_get_value_int XCRYPTO_PREFIX %+ _X509V3_get_value_int
%xdefine X509V3_parse_list XCRYPTO_PREFIX %+ _X509V3_parse_list
%xdefine X509V3_section_free XCRYPTO_PREFIX %+ _X509V3_section_free
%xdefine X509V3_set_ctx XCRYPTO_PREFIX %+ _X509V3_set_ctx
%xdefine X509V3_set_nconf XCRYPTO_PREFIX %+ _X509V3_set_nconf
%xdefine X509V3_string_free XCRYPTO_PREFIX %+ _X509V3_string_free
%xdefine X509_ALGORS_it XCRYPTO_PREFIX %+ _X509_ALGORS_it
%xdefine X509_ALGOR_cmp XCRYPTO_PREFIX %+ _X509_ALGOR_cmp
%xdefine X509_ALGOR_dup XCRYPTO_PREFIX %+ _X509_ALGOR_dup
%xdefine X509_ALGOR_free XCRYPTO_PREFIX %+ _X509_ALGOR_free
%xdefine X509_ALGOR_get0 XCRYPTO_PREFIX %+ _X509_ALGOR_get0
%xdefine X509_ALGOR_it XCRYPTO_PREFIX %+ _X509_ALGOR_it
%xdefine X509_ALGOR_new XCRYPTO_PREFIX %+ _X509_ALGOR_new
%xdefine X509_ALGOR_set0 XCRYPTO_PREFIX %+ _X509_ALGOR_set0
%xdefine X509_ALGOR_set_md XCRYPTO_PREFIX %+ _X509_ALGOR_set_md
%xdefine X509_ATTRIBUTE_SET_it XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_SET_it
%xdefine X509_ATTRIBUTE_count XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_count
%xdefine X509_ATTRIBUTE_create XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create
%xdefine X509_ATTRIBUTE_create_by_NID XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create_by_NID
%xdefine X509_ATTRIBUTE_create_by_OBJ XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create_by_OBJ
%xdefine X509_ATTRIBUTE_create_by_txt XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_create_by_txt
%xdefine X509_ATTRIBUTE_dup XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_dup
%xdefine X509_ATTRIBUTE_free XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_free
%xdefine X509_ATTRIBUTE_get0_data XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_get0_data
%xdefine X509_ATTRIBUTE_get0_object XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_get0_object
%xdefine X509_ATTRIBUTE_get0_type XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_get0_type
%xdefine X509_ATTRIBUTE_it XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_it
%xdefine X509_ATTRIBUTE_new XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_new
%xdefine X509_ATTRIBUTE_set1_data XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_set1_data
%xdefine X509_ATTRIBUTE_set1_object XCRYPTO_PREFIX %+ _X509_ATTRIBUTE_set1_object
%xdefine X509_CERT_AUX_free XCRYPTO_PREFIX %+ _X509_CERT_AUX_free
%xdefine X509_CERT_AUX_it XCRYPTO_PREFIX %+ _X509_CERT_AUX_it
%xdefine X509_CERT_AUX_new XCRYPTO_PREFIX %+ _X509_CERT_AUX_new
%xdefine X509_CERT_AUX_print XCRYPTO_PREFIX %+ _X509_CERT_AUX_print
%xdefine X509_CINF_free XCRYPTO_PREFIX %+ _X509_CINF_free
%xdefine X509_CINF_it XCRYPTO_PREFIX %+ _X509_CINF_it
%xdefine X509_CINF_new XCRYPTO_PREFIX %+ _X509_CINF_new
%xdefine X509_CRL_INFO_free XCRYPTO_PREFIX %+ _X509_CRL_INFO_free
%xdefine X509_CRL_INFO_it XCRYPTO_PREFIX %+ _X509_CRL_INFO_it
%xdefine X509_CRL_INFO_new XCRYPTO_PREFIX %+ _X509_CRL_INFO_new
%xdefine X509_CRL_METHOD_free XCRYPTO_PREFIX %+ _X509_CRL_METHOD_free
%xdefine X509_CRL_METHOD_new XCRYPTO_PREFIX %+ _X509_CRL_METHOD_new
%xdefine X509_CRL_add0_revoked XCRYPTO_PREFIX %+ _X509_CRL_add0_revoked
%xdefine X509_CRL_add1_ext_i2d XCRYPTO_PREFIX %+ _X509_CRL_add1_ext_i2d
%xdefine X509_CRL_add_ext XCRYPTO_PREFIX %+ _X509_CRL_add_ext
%xdefine X509_CRL_check_suiteb XCRYPTO_PREFIX %+ _X509_CRL_check_suiteb
%xdefine X509_CRL_cmp XCRYPTO_PREFIX %+ _X509_CRL_cmp
%xdefine X509_CRL_delete_ext XCRYPTO_PREFIX %+ _X509_CRL_delete_ext
%xdefine X509_CRL_diff XCRYPTO_PREFIX %+ _X509_CRL_diff
%xdefine X509_CRL_digest XCRYPTO_PREFIX %+ _X509_CRL_digest
%xdefine X509_CRL_dup XCRYPTO_PREFIX %+ _X509_CRL_dup
%xdefine X509_CRL_free XCRYPTO_PREFIX %+ _X509_CRL_free
%xdefine X509_CRL_get0_by_cert XCRYPTO_PREFIX %+ _X509_CRL_get0_by_cert
%xdefine X509_CRL_get0_by_serial XCRYPTO_PREFIX %+ _X509_CRL_get0_by_serial
%xdefine X509_CRL_get0_lastUpdate XCRYPTO_PREFIX %+ _X509_CRL_get0_lastUpdate
%xdefine X509_CRL_get0_nextUpdate XCRYPTO_PREFIX %+ _X509_CRL_get0_nextUpdate
%xdefine X509_CRL_get0_signature XCRYPTO_PREFIX %+ _X509_CRL_get0_signature
%xdefine X509_CRL_get_ext XCRYPTO_PREFIX %+ _X509_CRL_get_ext
%xdefine X509_CRL_get_ext_by_NID XCRYPTO_PREFIX %+ _X509_CRL_get_ext_by_NID
%xdefine X509_CRL_get_ext_by_OBJ XCRYPTO_PREFIX %+ _X509_CRL_get_ext_by_OBJ
%xdefine X509_CRL_get_ext_by_critical XCRYPTO_PREFIX %+ _X509_CRL_get_ext_by_critical
%xdefine X509_CRL_get_ext_count XCRYPTO_PREFIX %+ _X509_CRL_get_ext_count
%xdefine X509_CRL_get_ext_d2i XCRYPTO_PREFIX %+ _X509_CRL_get_ext_d2i
%xdefine X509_CRL_get_meth_data XCRYPTO_PREFIX %+ _X509_CRL_get_meth_data
%xdefine X509_CRL_get_signature_nid XCRYPTO_PREFIX %+ _X509_CRL_get_signature_nid
%xdefine X509_CRL_it XCRYPTO_PREFIX %+ _X509_CRL_it
%xdefine X509_CRL_match XCRYPTO_PREFIX %+ _X509_CRL_match
%xdefine X509_CRL_new XCRYPTO_PREFIX %+ _X509_CRL_new
%xdefine X509_CRL_print XCRYPTO_PREFIX %+ _X509_CRL_print
%xdefine X509_CRL_print_fp XCRYPTO_PREFIX %+ _X509_CRL_print_fp
%xdefine X509_CRL_set_default_method XCRYPTO_PREFIX %+ _X509_CRL_set_default_method
%xdefine X509_CRL_set_issuer_name XCRYPTO_PREFIX %+ _X509_CRL_set_issuer_name
%xdefine X509_CRL_set_lastUpdate XCRYPTO_PREFIX %+ _X509_CRL_set_lastUpdate
%xdefine X509_CRL_set_meth_data XCRYPTO_PREFIX %+ _X509_CRL_set_meth_data
%xdefine X509_CRL_set_nextUpdate XCRYPTO_PREFIX %+ _X509_CRL_set_nextUpdate
%xdefine X509_CRL_set_version XCRYPTO_PREFIX %+ _X509_CRL_set_version
%xdefine X509_CRL_sign XCRYPTO_PREFIX %+ _X509_CRL_sign
%xdefine X509_CRL_sign_ctx XCRYPTO_PREFIX %+ _X509_CRL_sign_ctx
%xdefine X509_CRL_sort XCRYPTO_PREFIX %+ _X509_CRL_sort
%xdefine X509_CRL_up_ref XCRYPTO_PREFIX %+ _X509_CRL_up_ref
%xdefine X509_CRL_verify XCRYPTO_PREFIX %+ _X509_CRL_verify
%xdefine X509_EXTENSIONS_it XCRYPTO_PREFIX %+ _X509_EXTENSIONS_it
%xdefine X509_EXTENSION_create_by_NID XCRYPTO_PREFIX %+ _X509_EXTENSION_create_by_NID
%xdefine X509_EXTENSION_create_by_OBJ XCRYPTO_PREFIX %+ _X509_EXTENSION_create_by_OBJ
%xdefine X509_EXTENSION_dup XCRYPTO_PREFIX %+ _X509_EXTENSION_dup
%xdefine X509_EXTENSION_free XCRYPTO_PREFIX %+ _X509_EXTENSION_free
%xdefine X509_EXTENSION_get_critical XCRYPTO_PREFIX %+ _X509_EXTENSION_get_critical
%xdefine X509_EXTENSION_get_data XCRYPTO_PREFIX %+ _X509_EXTENSION_get_data
%xdefine X509_EXTENSION_get_object XCRYPTO_PREFIX %+ _X509_EXTENSION_get_object
%xdefine X509_EXTENSION_it XCRYPTO_PREFIX %+ _X509_EXTENSION_it
%xdefine X509_EXTENSION_new XCRYPTO_PREFIX %+ _X509_EXTENSION_new
%xdefine X509_EXTENSION_set_critical XCRYPTO_PREFIX %+ _X509_EXTENSION_set_critical
%xdefine X509_EXTENSION_set_data XCRYPTO_PREFIX %+ _X509_EXTENSION_set_data
%xdefine X509_EXTENSION_set_object XCRYPTO_PREFIX %+ _X509_EXTENSION_set_object
%xdefine X509_INFO_free XCRYPTO_PREFIX %+ _X509_INFO_free
%xdefine X509_INFO_new XCRYPTO_PREFIX %+ _X509_INFO_new
%xdefine X509_LOOKUP_by_alias XCRYPTO_PREFIX %+ _X509_LOOKUP_by_alias
%xdefine X509_LOOKUP_by_fingerprint XCRYPTO_PREFIX %+ _X509_LOOKUP_by_fingerprint
%xdefine X509_LOOKUP_by_issuer_serial XCRYPTO_PREFIX %+ _X509_LOOKUP_by_issuer_serial
%xdefine X509_LOOKUP_by_subject XCRYPTO_PREFIX %+ _X509_LOOKUP_by_subject
%xdefine X509_LOOKUP_ctrl XCRYPTO_PREFIX %+ _X509_LOOKUP_ctrl
%xdefine X509_LOOKUP_file XCRYPTO_PREFIX %+ _X509_LOOKUP_file
%xdefine X509_LOOKUP_free XCRYPTO_PREFIX %+ _X509_LOOKUP_free
%xdefine X509_LOOKUP_hash_dir XCRYPTO_PREFIX %+ _X509_LOOKUP_hash_dir
%xdefine X509_LOOKUP_init XCRYPTO_PREFIX %+ _X509_LOOKUP_init
%xdefine X509_LOOKUP_new XCRYPTO_PREFIX %+ _X509_LOOKUP_new
%xdefine X509_LOOKUP_shutdown XCRYPTO_PREFIX %+ _X509_LOOKUP_shutdown
%xdefine X509_NAME_ENTRIES_it XCRYPTO_PREFIX %+ _X509_NAME_ENTRIES_it
%xdefine X509_NAME_ENTRY_create_by_NID XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_create_by_NID
%xdefine X509_NAME_ENTRY_create_by_OBJ XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_create_by_OBJ
%xdefine X509_NAME_ENTRY_create_by_txt XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_create_by_txt
%xdefine X509_NAME_ENTRY_dup XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_dup
%xdefine X509_NAME_ENTRY_free XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_free
%xdefine X509_NAME_ENTRY_get_data XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_get_data
%xdefine X509_NAME_ENTRY_get_object XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_get_object
%xdefine X509_NAME_ENTRY_it XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_it
%xdefine X509_NAME_ENTRY_new XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_new
%xdefine X509_NAME_ENTRY_set XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_set
%xdefine X509_NAME_ENTRY_set_data XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_set_data
%xdefine X509_NAME_ENTRY_set_object XCRYPTO_PREFIX %+ _X509_NAME_ENTRY_set_object
%xdefine X509_NAME_INTERNAL_it XCRYPTO_PREFIX %+ _X509_NAME_INTERNAL_it
%xdefine X509_NAME_add_entry XCRYPTO_PREFIX %+ _X509_NAME_add_entry
%xdefine X509_NAME_add_entry_by_NID XCRYPTO_PREFIX %+ _X509_NAME_add_entry_by_NID
%xdefine X509_NAME_add_entry_by_OBJ XCRYPTO_PREFIX %+ _X509_NAME_add_entry_by_OBJ
%xdefine X509_NAME_add_entry_by_txt XCRYPTO_PREFIX %+ _X509_NAME_add_entry_by_txt
%xdefine X509_NAME_cmp XCRYPTO_PREFIX %+ _X509_NAME_cmp
%xdefine X509_NAME_delete_entry XCRYPTO_PREFIX %+ _X509_NAME_delete_entry
%xdefine X509_NAME_digest XCRYPTO_PREFIX %+ _X509_NAME_digest
%xdefine X509_NAME_dup XCRYPTO_PREFIX %+ _X509_NAME_dup
%xdefine X509_NAME_entry_count XCRYPTO_PREFIX %+ _X509_NAME_entry_count
%xdefine X509_NAME_free XCRYPTO_PREFIX %+ _X509_NAME_free
%xdefine X509_NAME_get0_der XCRYPTO_PREFIX %+ _X509_NAME_get0_der
%xdefine X509_NAME_get_entry XCRYPTO_PREFIX %+ _X509_NAME_get_entry
%xdefine X509_NAME_get_index_by_NID XCRYPTO_PREFIX %+ _X509_NAME_get_index_by_NID
%xdefine X509_NAME_get_index_by_OBJ XCRYPTO_PREFIX %+ _X509_NAME_get_index_by_OBJ
%xdefine X509_NAME_get_text_by_NID XCRYPTO_PREFIX %+ _X509_NAME_get_text_by_NID
%xdefine X509_NAME_get_text_by_OBJ XCRYPTO_PREFIX %+ _X509_NAME_get_text_by_OBJ
%xdefine X509_NAME_hash XCRYPTO_PREFIX %+ _X509_NAME_hash
%xdefine X509_NAME_hash_old XCRYPTO_PREFIX %+ _X509_NAME_hash_old
%xdefine X509_NAME_it XCRYPTO_PREFIX %+ _X509_NAME_it
%xdefine X509_NAME_new XCRYPTO_PREFIX %+ _X509_NAME_new
%xdefine X509_NAME_oneline XCRYPTO_PREFIX %+ _X509_NAME_oneline
%xdefine X509_NAME_print XCRYPTO_PREFIX %+ _X509_NAME_print
%xdefine X509_NAME_print_ex XCRYPTO_PREFIX %+ _X509_NAME_print_ex
%xdefine X509_NAME_print_ex_fp XCRYPTO_PREFIX %+ _X509_NAME_print_ex_fp
%xdefine X509_NAME_set XCRYPTO_PREFIX %+ _X509_NAME_set
%xdefine X509_OBJECT_free_contents XCRYPTO_PREFIX %+ _X509_OBJECT_free_contents
%xdefine X509_OBJECT_get0_X509 XCRYPTO_PREFIX %+ _X509_OBJECT_get0_X509
%xdefine X509_OBJECT_get_type XCRYPTO_PREFIX %+ _X509_OBJECT_get_type
%xdefine X509_OBJECT_idx_by_subject XCRYPTO_PREFIX %+ _X509_OBJECT_idx_by_subject
%xdefine X509_OBJECT_retrieve_by_subject XCRYPTO_PREFIX %+ _X509_OBJECT_retrieve_by_subject
%xdefine X509_OBJECT_retrieve_match XCRYPTO_PREFIX %+ _X509_OBJECT_retrieve_match
%xdefine X509_OBJECT_up_ref_count XCRYPTO_PREFIX %+ _X509_OBJECT_up_ref_count
%xdefine X509_PKEY_free XCRYPTO_PREFIX %+ _X509_PKEY_free
%xdefine X509_PKEY_new XCRYPTO_PREFIX %+ _X509_PKEY_new
%xdefine X509_POLICY_NODE_print XCRYPTO_PREFIX %+ _X509_POLICY_NODE_print
%xdefine X509_PUBKEY_free XCRYPTO_PREFIX %+ _X509_PUBKEY_free
%xdefine X509_PUBKEY_get XCRYPTO_PREFIX %+ _X509_PUBKEY_get
%xdefine X509_PUBKEY_get0_param XCRYPTO_PREFIX %+ _X509_PUBKEY_get0_param
%xdefine X509_PUBKEY_it XCRYPTO_PREFIX %+ _X509_PUBKEY_it
%xdefine X509_PUBKEY_new XCRYPTO_PREFIX %+ _X509_PUBKEY_new
%xdefine X509_PUBKEY_set XCRYPTO_PREFIX %+ _X509_PUBKEY_set
%xdefine X509_PUBKEY_set0_param XCRYPTO_PREFIX %+ _X509_PUBKEY_set0_param
%xdefine X509_PURPOSE_add XCRYPTO_PREFIX %+ _X509_PURPOSE_add
%xdefine X509_PURPOSE_cleanup XCRYPTO_PREFIX %+ _X509_PURPOSE_cleanup
%xdefine X509_PURPOSE_get0 XCRYPTO_PREFIX %+ _X509_PURPOSE_get0
%xdefine X509_PURPOSE_get0_name XCRYPTO_PREFIX %+ _X509_PURPOSE_get0_name
%xdefine X509_PURPOSE_get0_sname XCRYPTO_PREFIX %+ _X509_PURPOSE_get0_sname
%xdefine X509_PURPOSE_get_by_id XCRYPTO_PREFIX %+ _X509_PURPOSE_get_by_id
%xdefine X509_PURPOSE_get_by_sname XCRYPTO_PREFIX %+ _X509_PURPOSE_get_by_sname
%xdefine X509_PURPOSE_get_count XCRYPTO_PREFIX %+ _X509_PURPOSE_get_count
%xdefine X509_PURPOSE_get_id XCRYPTO_PREFIX %+ _X509_PURPOSE_get_id
%xdefine X509_PURPOSE_get_trust XCRYPTO_PREFIX %+ _X509_PURPOSE_get_trust
%xdefine X509_PURPOSE_set XCRYPTO_PREFIX %+ _X509_PURPOSE_set
%xdefine X509_REQ_INFO_free XCRYPTO_PREFIX %+ _X509_REQ_INFO_free
%xdefine X509_REQ_INFO_it XCRYPTO_PREFIX %+ _X509_REQ_INFO_it
%xdefine X509_REQ_INFO_new XCRYPTO_PREFIX %+ _X509_REQ_INFO_new
%xdefine X509_REQ_add1_attr XCRYPTO_PREFIX %+ _X509_REQ_add1_attr
%xdefine X509_REQ_add1_attr_by_NID XCRYPTO_PREFIX %+ _X509_REQ_add1_attr_by_NID
%xdefine X509_REQ_add1_attr_by_OBJ XCRYPTO_PREFIX %+ _X509_REQ_add1_attr_by_OBJ
%xdefine X509_REQ_add1_attr_by_txt XCRYPTO_PREFIX %+ _X509_REQ_add1_attr_by_txt
%xdefine X509_REQ_add_extensions XCRYPTO_PREFIX %+ _X509_REQ_add_extensions
%xdefine X509_REQ_add_extensions_nid XCRYPTO_PREFIX %+ _X509_REQ_add_extensions_nid
%xdefine X509_REQ_check_private_key XCRYPTO_PREFIX %+ _X509_REQ_check_private_key
%xdefine X509_REQ_delete_attr XCRYPTO_PREFIX %+ _X509_REQ_delete_attr
%xdefine X509_REQ_digest XCRYPTO_PREFIX %+ _X509_REQ_digest
%xdefine X509_REQ_dup XCRYPTO_PREFIX %+ _X509_REQ_dup
%xdefine X509_REQ_extension_nid XCRYPTO_PREFIX %+ _X509_REQ_extension_nid
%xdefine X509_REQ_free XCRYPTO_PREFIX %+ _X509_REQ_free
%xdefine X509_REQ_get0_signature XCRYPTO_PREFIX %+ _X509_REQ_get0_signature
%xdefine X509_REQ_get1_email XCRYPTO_PREFIX %+ _X509_REQ_get1_email
%xdefine X509_REQ_get_attr XCRYPTO_PREFIX %+ _X509_REQ_get_attr
%xdefine X509_REQ_get_attr_by_NID XCRYPTO_PREFIX %+ _X509_REQ_get_attr_by_NID
%xdefine X509_REQ_get_attr_by_OBJ XCRYPTO_PREFIX %+ _X509_REQ_get_attr_by_OBJ
%xdefine X509_REQ_get_attr_count XCRYPTO_PREFIX %+ _X509_REQ_get_attr_count
%xdefine X509_REQ_get_extension_nids XCRYPTO_PREFIX %+ _X509_REQ_get_extension_nids
%xdefine X509_REQ_get_extensions XCRYPTO_PREFIX %+ _X509_REQ_get_extensions
%xdefine X509_REQ_get_pubkey XCRYPTO_PREFIX %+ _X509_REQ_get_pubkey
%xdefine X509_REQ_get_signature_nid XCRYPTO_PREFIX %+ _X509_REQ_get_signature_nid
%xdefine X509_REQ_it XCRYPTO_PREFIX %+ _X509_REQ_it
%xdefine X509_REQ_new XCRYPTO_PREFIX %+ _X509_REQ_new
%xdefine X509_REQ_print XCRYPTO_PREFIX %+ _X509_REQ_print
%xdefine X509_REQ_print_ex XCRYPTO_PREFIX %+ _X509_REQ_print_ex
%xdefine X509_REQ_print_fp XCRYPTO_PREFIX %+ _X509_REQ_print_fp
%xdefine X509_REQ_set_extension_nids XCRYPTO_PREFIX %+ _X509_REQ_set_extension_nids
%xdefine X509_REQ_set_pubkey XCRYPTO_PREFIX %+ _X509_REQ_set_pubkey
%xdefine X509_REQ_set_subject_name XCRYPTO_PREFIX %+ _X509_REQ_set_subject_name
%xdefine X509_REQ_set_version XCRYPTO_PREFIX %+ _X509_REQ_set_version
%xdefine X509_REQ_sign XCRYPTO_PREFIX %+ _X509_REQ_sign
%xdefine X509_REQ_sign_ctx XCRYPTO_PREFIX %+ _X509_REQ_sign_ctx
%xdefine X509_REQ_to_X509 XCRYPTO_PREFIX %+ _X509_REQ_to_X509
%xdefine X509_REQ_verify XCRYPTO_PREFIX %+ _X509_REQ_verify
%xdefine X509_REVOKED_add1_ext_i2d XCRYPTO_PREFIX %+ _X509_REVOKED_add1_ext_i2d
%xdefine X509_REVOKED_add_ext XCRYPTO_PREFIX %+ _X509_REVOKED_add_ext
%xdefine X509_REVOKED_delete_ext XCRYPTO_PREFIX %+ _X509_REVOKED_delete_ext
%xdefine X509_REVOKED_dup XCRYPTO_PREFIX %+ _X509_REVOKED_dup
%xdefine X509_REVOKED_free XCRYPTO_PREFIX %+ _X509_REVOKED_free
%xdefine X509_REVOKED_get0_revocationDate XCRYPTO_PREFIX %+ _X509_REVOKED_get0_revocationDate
%xdefine X509_REVOKED_get0_serialNumber XCRYPTO_PREFIX %+ _X509_REVOKED_get0_serialNumber
%xdefine X509_REVOKED_get_ext XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext
%xdefine X509_REVOKED_get_ext_by_NID XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_by_NID
%xdefine X509_REVOKED_get_ext_by_OBJ XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_by_OBJ
%xdefine X509_REVOKED_get_ext_by_critical XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_by_critical
%xdefine X509_REVOKED_get_ext_count XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_count
%xdefine X509_REVOKED_get_ext_d2i XCRYPTO_PREFIX %+ _X509_REVOKED_get_ext_d2i
%xdefine X509_REVOKED_it XCRYPTO_PREFIX %+ _X509_REVOKED_it
%xdefine X509_REVOKED_new XCRYPTO_PREFIX %+ _X509_REVOKED_new
%xdefine X509_REVOKED_set_revocationDate XCRYPTO_PREFIX %+ _X509_REVOKED_set_revocationDate
%xdefine X509_REVOKED_set_serialNumber XCRYPTO_PREFIX %+ _X509_REVOKED_set_serialNumber
%xdefine X509_SIG_free XCRYPTO_PREFIX %+ _X509_SIG_free
%xdefine X509_SIG_it XCRYPTO_PREFIX %+ _X509_SIG_it
%xdefine X509_SIG_new XCRYPTO_PREFIX %+ _X509_SIG_new
%xdefine X509_STORE_CTX_cleanup XCRYPTO_PREFIX %+ _X509_STORE_CTX_cleanup
%xdefine X509_STORE_CTX_free XCRYPTO_PREFIX %+ _X509_STORE_CTX_free
%xdefine X509_STORE_CTX_get0_cert XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_cert
%xdefine X509_STORE_CTX_get0_chain XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_chain
%xdefine X509_STORE_CTX_get0_current_crl XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_current_crl
%xdefine X509_STORE_CTX_get0_current_issuer XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_current_issuer
%xdefine X509_STORE_CTX_get0_param XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_param
%xdefine X509_STORE_CTX_get0_parent_ctx XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_parent_ctx
%xdefine X509_STORE_CTX_get0_policy_tree XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_policy_tree
%xdefine X509_STORE_CTX_get0_store XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_store
%xdefine X509_STORE_CTX_get0_untrusted XCRYPTO_PREFIX %+ _X509_STORE_CTX_get0_untrusted
%xdefine X509_STORE_CTX_get1_chain XCRYPTO_PREFIX %+ _X509_STORE_CTX_get1_chain
%xdefine X509_STORE_CTX_get1_issuer XCRYPTO_PREFIX %+ _X509_STORE_CTX_get1_issuer
%xdefine X509_STORE_CTX_get_chain XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_chain
%xdefine X509_STORE_CTX_get_current_cert XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_current_cert
%xdefine X509_STORE_CTX_get_error XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_error
%xdefine X509_STORE_CTX_get_error_depth XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_error_depth
%xdefine X509_STORE_CTX_get_ex_data XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_ex_data
%xdefine X509_STORE_CTX_get_ex_new_index XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_ex_new_index
%xdefine X509_STORE_CTX_get_explicit_policy XCRYPTO_PREFIX %+ _X509_STORE_CTX_get_explicit_policy
%xdefine X509_STORE_CTX_init XCRYPTO_PREFIX %+ _X509_STORE_CTX_init
%xdefine X509_STORE_CTX_new XCRYPTO_PREFIX %+ _X509_STORE_CTX_new
%xdefine X509_STORE_CTX_purpose_inherit XCRYPTO_PREFIX %+ _X509_STORE_CTX_purpose_inherit
%xdefine X509_STORE_CTX_set0_crls XCRYPTO_PREFIX %+ _X509_STORE_CTX_set0_crls
%xdefine X509_STORE_CTX_set0_param XCRYPTO_PREFIX %+ _X509_STORE_CTX_set0_param
%xdefine X509_STORE_CTX_set_cert XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_cert
%xdefine X509_STORE_CTX_set_chain XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_chain
%xdefine X509_STORE_CTX_set_default XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_default
%xdefine X509_STORE_CTX_set_depth XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_depth
%xdefine X509_STORE_CTX_set_error XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_error
%xdefine X509_STORE_CTX_set_ex_data XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_ex_data
%xdefine X509_STORE_CTX_set_flags XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_flags
%xdefine X509_STORE_CTX_set_purpose XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_purpose
%xdefine X509_STORE_CTX_set_time XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_time
%xdefine X509_STORE_CTX_set_trust XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_trust
%xdefine X509_STORE_CTX_set_verify_cb XCRYPTO_PREFIX %+ _X509_STORE_CTX_set_verify_cb
%xdefine X509_STORE_CTX_trusted_stack XCRYPTO_PREFIX %+ _X509_STORE_CTX_trusted_stack
%xdefine X509_STORE_CTX_zero XCRYPTO_PREFIX %+ _X509_STORE_CTX_zero
%xdefine X509_STORE_add_cert XCRYPTO_PREFIX %+ _X509_STORE_add_cert
%xdefine X509_STORE_add_crl XCRYPTO_PREFIX %+ _X509_STORE_add_crl
%xdefine X509_STORE_add_lookup XCRYPTO_PREFIX %+ _X509_STORE_add_lookup
%xdefine X509_STORE_free XCRYPTO_PREFIX %+ _X509_STORE_free
%xdefine X509_STORE_get0_objects XCRYPTO_PREFIX %+ _X509_STORE_get0_objects
%xdefine X509_STORE_get0_param XCRYPTO_PREFIX %+ _X509_STORE_get0_param
%xdefine X509_STORE_get1_certs XCRYPTO_PREFIX %+ _X509_STORE_get1_certs
%xdefine X509_STORE_get1_crls XCRYPTO_PREFIX %+ _X509_STORE_get1_crls
%xdefine X509_STORE_get_by_subject XCRYPTO_PREFIX %+ _X509_STORE_get_by_subject
%xdefine X509_STORE_get_cert_crl XCRYPTO_PREFIX %+ _X509_STORE_get_cert_crl
%xdefine X509_STORE_get_check_crl XCRYPTO_PREFIX %+ _X509_STORE_get_check_crl
%xdefine X509_STORE_get_check_issued XCRYPTO_PREFIX %+ _X509_STORE_get_check_issued
%xdefine X509_STORE_get_check_revocation XCRYPTO_PREFIX %+ _X509_STORE_get_check_revocation
%xdefine X509_STORE_get_cleanup XCRYPTO_PREFIX %+ _X509_STORE_get_cleanup
%xdefine X509_STORE_get_get_crl XCRYPTO_PREFIX %+ _X509_STORE_get_get_crl
%xdefine X509_STORE_get_get_issuer XCRYPTO_PREFIX %+ _X509_STORE_get_get_issuer
%xdefine X509_STORE_get_lookup_certs XCRYPTO_PREFIX %+ _X509_STORE_get_lookup_certs
%xdefine X509_STORE_get_lookup_crls XCRYPTO_PREFIX %+ _X509_STORE_get_lookup_crls
%xdefine X509_STORE_get_verify XCRYPTO_PREFIX %+ _X509_STORE_get_verify
%xdefine X509_STORE_get_verify_cb XCRYPTO_PREFIX %+ _X509_STORE_get_verify_cb
%xdefine X509_STORE_load_locations XCRYPTO_PREFIX %+ _X509_STORE_load_locations
%xdefine X509_STORE_new XCRYPTO_PREFIX %+ _X509_STORE_new
%xdefine X509_STORE_set0_additional_untrusted XCRYPTO_PREFIX %+ _X509_STORE_set0_additional_untrusted
%xdefine X509_STORE_set1_param XCRYPTO_PREFIX %+ _X509_STORE_set1_param
%xdefine X509_STORE_set_cert_crl XCRYPTO_PREFIX %+ _X509_STORE_set_cert_crl
%xdefine X509_STORE_set_check_crl XCRYPTO_PREFIX %+ _X509_STORE_set_check_crl
%xdefine X509_STORE_set_check_issued XCRYPTO_PREFIX %+ _X509_STORE_set_check_issued
%xdefine X509_STORE_set_check_revocation XCRYPTO_PREFIX %+ _X509_STORE_set_check_revocation
%xdefine X509_STORE_set_cleanup XCRYPTO_PREFIX %+ _X509_STORE_set_cleanup
%xdefine X509_STORE_set_default_paths XCRYPTO_PREFIX %+ _X509_STORE_set_default_paths
%xdefine X509_STORE_set_depth XCRYPTO_PREFIX %+ _X509_STORE_set_depth
%xdefine X509_STORE_set_flags XCRYPTO_PREFIX %+ _X509_STORE_set_flags
%xdefine X509_STORE_set_get_crl XCRYPTO_PREFIX %+ _X509_STORE_set_get_crl
%xdefine X509_STORE_set_get_issuer XCRYPTO_PREFIX %+ _X509_STORE_set_get_issuer
%xdefine X509_STORE_set_lookup_certs XCRYPTO_PREFIX %+ _X509_STORE_set_lookup_certs
%xdefine X509_STORE_set_lookup_crls XCRYPTO_PREFIX %+ _X509_STORE_set_lookup_crls
%xdefine X509_STORE_set_purpose XCRYPTO_PREFIX %+ _X509_STORE_set_purpose
%xdefine X509_STORE_set_trust XCRYPTO_PREFIX %+ _X509_STORE_set_trust
%xdefine X509_STORE_set_verify XCRYPTO_PREFIX %+ _X509_STORE_set_verify
%xdefine X509_STORE_set_verify_cb XCRYPTO_PREFIX %+ _X509_STORE_set_verify_cb
%xdefine X509_STORE_up_ref XCRYPTO_PREFIX %+ _X509_STORE_up_ref
%xdefine X509_TRUST_add XCRYPTO_PREFIX %+ _X509_TRUST_add
%xdefine X509_TRUST_cleanup XCRYPTO_PREFIX %+ _X509_TRUST_cleanup
%xdefine X509_TRUST_get0 XCRYPTO_PREFIX %+ _X509_TRUST_get0
%xdefine X509_TRUST_get0_name XCRYPTO_PREFIX %+ _X509_TRUST_get0_name
%xdefine X509_TRUST_get_by_id XCRYPTO_PREFIX %+ _X509_TRUST_get_by_id
%xdefine X509_TRUST_get_count XCRYPTO_PREFIX %+ _X509_TRUST_get_count
%xdefine X509_TRUST_get_flags XCRYPTO_PREFIX %+ _X509_TRUST_get_flags
%xdefine X509_TRUST_get_trust XCRYPTO_PREFIX %+ _X509_TRUST_get_trust
%xdefine X509_TRUST_set XCRYPTO_PREFIX %+ _X509_TRUST_set
%xdefine X509_TRUST_set_default XCRYPTO_PREFIX %+ _X509_TRUST_set_default
%xdefine X509_VAL_free XCRYPTO_PREFIX %+ _X509_VAL_free
%xdefine X509_VAL_it XCRYPTO_PREFIX %+ _X509_VAL_it
%xdefine X509_VAL_new XCRYPTO_PREFIX %+ _X509_VAL_new
%xdefine X509_VERIFY_PARAM_add0_policy XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_add0_policy
%xdefine X509_VERIFY_PARAM_add0_table XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_add0_table
%xdefine X509_VERIFY_PARAM_add1_host XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_add1_host
%xdefine X509_VERIFY_PARAM_clear_flags XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_clear_flags
%xdefine X509_VERIFY_PARAM_free XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_free
%xdefine X509_VERIFY_PARAM_get0 XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get0
%xdefine X509_VERIFY_PARAM_get0_name XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get0_name
%xdefine X509_VERIFY_PARAM_get0_peername XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get0_peername
%xdefine X509_VERIFY_PARAM_get_count XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get_count
%xdefine X509_VERIFY_PARAM_get_depth XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get_depth
%xdefine X509_VERIFY_PARAM_get_flags XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_get_flags
%xdefine X509_VERIFY_PARAM_inherit XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_inherit
%xdefine X509_VERIFY_PARAM_lookup XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_lookup
%xdefine X509_VERIFY_PARAM_new XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_new
%xdefine X509_VERIFY_PARAM_set1 XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1
%xdefine X509_VERIFY_PARAM_set1_email XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_email
%xdefine X509_VERIFY_PARAM_set1_host XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_host
%xdefine X509_VERIFY_PARAM_set1_ip XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_ip
%xdefine X509_VERIFY_PARAM_set1_ip_asc XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_ip_asc
%xdefine X509_VERIFY_PARAM_set1_name XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_name
%xdefine X509_VERIFY_PARAM_set1_policies XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set1_policies
%xdefine X509_VERIFY_PARAM_set_depth XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_depth
%xdefine X509_VERIFY_PARAM_set_flags XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_flags
%xdefine X509_VERIFY_PARAM_set_hostflags XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_hostflags
%xdefine X509_VERIFY_PARAM_set_purpose XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_purpose
%xdefine X509_VERIFY_PARAM_set_time XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_time
%xdefine X509_VERIFY_PARAM_set_trust XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_set_trust
%xdefine X509_VERIFY_PARAM_table_cleanup XCRYPTO_PREFIX %+ _X509_VERIFY_PARAM_table_cleanup
%xdefine X509_add1_ext_i2d XCRYPTO_PREFIX %+ _X509_add1_ext_i2d
%xdefine X509_add1_reject_object XCRYPTO_PREFIX %+ _X509_add1_reject_object
%xdefine X509_add1_trust_object XCRYPTO_PREFIX %+ _X509_add1_trust_object
%xdefine X509_add_ext XCRYPTO_PREFIX %+ _X509_add_ext
%xdefine X509_alias_get0 XCRYPTO_PREFIX %+ _X509_alias_get0
%xdefine X509_alias_set1 XCRYPTO_PREFIX %+ _X509_alias_set1
%xdefine X509_chain_check_suiteb XCRYPTO_PREFIX %+ _X509_chain_check_suiteb
%xdefine X509_chain_up_ref XCRYPTO_PREFIX %+ _X509_chain_up_ref
%xdefine X509_check_akid XCRYPTO_PREFIX %+ _X509_check_akid
%xdefine X509_check_ca XCRYPTO_PREFIX %+ _X509_check_ca
%xdefine X509_check_email XCRYPTO_PREFIX %+ _X509_check_email
%xdefine X509_check_host XCRYPTO_PREFIX %+ _X509_check_host
%xdefine X509_check_ip XCRYPTO_PREFIX %+ _X509_check_ip
%xdefine X509_check_ip_asc XCRYPTO_PREFIX %+ _X509_check_ip_asc
%xdefine X509_check_issued XCRYPTO_PREFIX %+ _X509_check_issued
%xdefine X509_check_private_key XCRYPTO_PREFIX %+ _X509_check_private_key
%xdefine X509_check_purpose XCRYPTO_PREFIX %+ _X509_check_purpose
%xdefine X509_check_trust XCRYPTO_PREFIX %+ _X509_check_trust
%xdefine X509_cmp XCRYPTO_PREFIX %+ _X509_cmp
%xdefine X509_cmp_current_time XCRYPTO_PREFIX %+ _X509_cmp_current_time
%xdefine X509_cmp_time XCRYPTO_PREFIX %+ _X509_cmp_time
%xdefine X509_delete_ext XCRYPTO_PREFIX %+ _X509_delete_ext
%xdefine X509_digest XCRYPTO_PREFIX %+ _X509_digest
%xdefine X509_dup XCRYPTO_PREFIX %+ _X509_dup
%xdefine X509_email_free XCRYPTO_PREFIX %+ _X509_email_free
%xdefine X509_find_by_issuer_and_serial XCRYPTO_PREFIX %+ _X509_find_by_issuer_and_serial
%xdefine X509_find_by_subject XCRYPTO_PREFIX %+ _X509_find_by_subject
%xdefine X509_free XCRYPTO_PREFIX %+ _X509_free
%xdefine X509_get0_extensions XCRYPTO_PREFIX %+ _X509_get0_extensions
%xdefine X509_get0_notAfter XCRYPTO_PREFIX %+ _X509_get0_notAfter
%xdefine X509_get0_notBefore XCRYPTO_PREFIX %+ _X509_get0_notBefore
%xdefine X509_get0_pubkey_bitstr XCRYPTO_PREFIX %+ _X509_get0_pubkey_bitstr
%xdefine X509_get0_signature XCRYPTO_PREFIX %+ _X509_get0_signature
%xdefine X509_get0_tbs_sigalg XCRYPTO_PREFIX %+ _X509_get0_tbs_sigalg
%xdefine X509_get1_email XCRYPTO_PREFIX %+ _X509_get1_email
%xdefine X509_get1_ocsp XCRYPTO_PREFIX %+ _X509_get1_ocsp
%xdefine X509_get_default_cert_area XCRYPTO_PREFIX %+ _X509_get_default_cert_area
%xdefine X509_get_default_cert_dir XCRYPTO_PREFIX %+ _X509_get_default_cert_dir
%xdefine X509_get_default_cert_dir_env XCRYPTO_PREFIX %+ _X509_get_default_cert_dir_env
%xdefine X509_get_default_cert_file XCRYPTO_PREFIX %+ _X509_get_default_cert_file
%xdefine X509_get_default_cert_file_env XCRYPTO_PREFIX %+ _X509_get_default_cert_file_env
%xdefine X509_get_default_private_dir XCRYPTO_PREFIX %+ _X509_get_default_private_dir
%xdefine X509_get_ex_data XCRYPTO_PREFIX %+ _X509_get_ex_data
%xdefine X509_get_ex_new_index XCRYPTO_PREFIX %+ _X509_get_ex_new_index
%xdefine X509_get_ext XCRYPTO_PREFIX %+ _X509_get_ext
%xdefine X509_get_ext_by_NID XCRYPTO_PREFIX %+ _X509_get_ext_by_NID
%xdefine X509_get_ext_by_OBJ XCRYPTO_PREFIX %+ _X509_get_ext_by_OBJ
%xdefine X509_get_ext_by_critical XCRYPTO_PREFIX %+ _X509_get_ext_by_critical
%xdefine X509_get_ext_count XCRYPTO_PREFIX %+ _X509_get_ext_count
%xdefine X509_get_ext_d2i XCRYPTO_PREFIX %+ _X509_get_ext_d2i
%xdefine X509_get_extended_key_usage XCRYPTO_PREFIX %+ _X509_get_extended_key_usage
%xdefine X509_get_extension_flags XCRYPTO_PREFIX %+ _X509_get_extension_flags
%xdefine X509_get_issuer_name XCRYPTO_PREFIX %+ _X509_get_issuer_name
%xdefine X509_get_key_usage XCRYPTO_PREFIX %+ _X509_get_key_usage
%xdefine X509_get_pubkey XCRYPTO_PREFIX %+ _X509_get_pubkey
%xdefine X509_get_serialNumber XCRYPTO_PREFIX %+ _X509_get_serialNumber
%xdefine X509_get_signature_nid XCRYPTO_PREFIX %+ _X509_get_signature_nid
%xdefine X509_get_subject_name XCRYPTO_PREFIX %+ _X509_get_subject_name
%xdefine X509_getm_notAfter XCRYPTO_PREFIX %+ _X509_getm_notAfter
%xdefine X509_getm_notBefore XCRYPTO_PREFIX %+ _X509_getm_notBefore
%xdefine X509_gmtime_adj XCRYPTO_PREFIX %+ _X509_gmtime_adj
%xdefine X509_issuer_and_serial_cmp XCRYPTO_PREFIX %+ _X509_issuer_and_serial_cmp
%xdefine X509_issuer_and_serial_hash XCRYPTO_PREFIX %+ _X509_issuer_and_serial_hash
%xdefine X509_issuer_name_cmp XCRYPTO_PREFIX %+ _X509_issuer_name_cmp
%xdefine X509_issuer_name_hash XCRYPTO_PREFIX %+ _X509_issuer_name_hash
%xdefine X509_issuer_name_hash_old XCRYPTO_PREFIX %+ _X509_issuer_name_hash_old
%xdefine X509_it XCRYPTO_PREFIX %+ _X509_it
%xdefine X509_keyid_get0 XCRYPTO_PREFIX %+ _X509_keyid_get0
%xdefine X509_keyid_set1 XCRYPTO_PREFIX %+ _X509_keyid_set1
%xdefine X509_load_cert_crl_file XCRYPTO_PREFIX %+ _X509_load_cert_crl_file
%xdefine X509_load_cert_file XCRYPTO_PREFIX %+ _X509_load_cert_file
%xdefine X509_load_crl_file XCRYPTO_PREFIX %+ _X509_load_crl_file
%xdefine X509_new XCRYPTO_PREFIX %+ _X509_new
%xdefine X509_ocspid_print XCRYPTO_PREFIX %+ _X509_ocspid_print
%xdefine X509_parse_from_buffer XCRYPTO_PREFIX %+ _X509_parse_from_buffer
%xdefine X509_policy_check XCRYPTO_PREFIX %+ _X509_policy_check
%xdefine X509_policy_level_get0_node XCRYPTO_PREFIX %+ _X509_policy_level_get0_node
%xdefine X509_policy_level_node_count XCRYPTO_PREFIX %+ _X509_policy_level_node_count
%xdefine X509_policy_node_get0_parent XCRYPTO_PREFIX %+ _X509_policy_node_get0_parent
%xdefine X509_policy_node_get0_policy XCRYPTO_PREFIX %+ _X509_policy_node_get0_policy
%xdefine X509_policy_node_get0_qualifiers XCRYPTO_PREFIX %+ _X509_policy_node_get0_qualifiers
%xdefine X509_policy_tree_free XCRYPTO_PREFIX %+ _X509_policy_tree_free
%xdefine X509_policy_tree_get0_level XCRYPTO_PREFIX %+ _X509_policy_tree_get0_level
%xdefine X509_policy_tree_get0_policies XCRYPTO_PREFIX %+ _X509_policy_tree_get0_policies
%xdefine X509_policy_tree_get0_user_policies XCRYPTO_PREFIX %+ _X509_policy_tree_get0_user_policies
%xdefine X509_policy_tree_level_count XCRYPTO_PREFIX %+ _X509_policy_tree_level_count
%xdefine X509_print XCRYPTO_PREFIX %+ _X509_print
%xdefine X509_print_ex XCRYPTO_PREFIX %+ _X509_print_ex
%xdefine X509_print_ex_fp XCRYPTO_PREFIX %+ _X509_print_ex_fp
%xdefine X509_print_fp XCRYPTO_PREFIX %+ _X509_print_fp
%xdefine X509_pubkey_digest XCRYPTO_PREFIX %+ _X509_pubkey_digest
%xdefine X509_reject_clear XCRYPTO_PREFIX %+ _X509_reject_clear
%xdefine X509_set_ex_data XCRYPTO_PREFIX %+ _X509_set_ex_data
%xdefine X509_set_issuer_name XCRYPTO_PREFIX %+ _X509_set_issuer_name
%xdefine X509_set_notAfter XCRYPTO_PREFIX %+ _X509_set_notAfter
%xdefine X509_set_notBefore XCRYPTO_PREFIX %+ _X509_set_notBefore
%xdefine X509_set_pubkey XCRYPTO_PREFIX %+ _X509_set_pubkey
%xdefine X509_set_serialNumber XCRYPTO_PREFIX %+ _X509_set_serialNumber
%xdefine X509_set_subject_name XCRYPTO_PREFIX %+ _X509_set_subject_name
%xdefine X509_set_version XCRYPTO_PREFIX %+ _X509_set_version
%xdefine X509_sign XCRYPTO_PREFIX %+ _X509_sign
%xdefine X509_sign_ctx XCRYPTO_PREFIX %+ _X509_sign_ctx
%xdefine X509_signature_dump XCRYPTO_PREFIX %+ _X509_signature_dump
%xdefine X509_signature_print XCRYPTO_PREFIX %+ _X509_signature_print
%xdefine X509_subject_name_cmp XCRYPTO_PREFIX %+ _X509_subject_name_cmp
%xdefine X509_subject_name_hash XCRYPTO_PREFIX %+ _X509_subject_name_hash
%xdefine X509_subject_name_hash_old XCRYPTO_PREFIX %+ _X509_subject_name_hash_old
%xdefine X509_supported_extension XCRYPTO_PREFIX %+ _X509_supported_extension
%xdefine X509_time_adj XCRYPTO_PREFIX %+ _X509_time_adj
%xdefine X509_time_adj_ex XCRYPTO_PREFIX %+ _X509_time_adj_ex
%xdefine X509_to_X509_REQ XCRYPTO_PREFIX %+ _X509_to_X509_REQ
%xdefine X509_trust_clear XCRYPTO_PREFIX %+ _X509_trust_clear
%xdefine X509_up_ref XCRYPTO_PREFIX %+ _X509_up_ref
%xdefine X509_verify XCRYPTO_PREFIX %+ _X509_verify
%xdefine X509_verify_cert XCRYPTO_PREFIX %+ _X509_verify_cert
%xdefine X509_verify_cert_error_string XCRYPTO_PREFIX %+ _X509_verify_cert_error_string
%xdefine X509at_add1_attr XCRYPTO_PREFIX %+ _X509at_add1_attr
%xdefine X509at_add1_attr_by_NID XCRYPTO_PREFIX %+ _X509at_add1_attr_by_NID
%xdefine X509at_add1_attr_by_OBJ XCRYPTO_PREFIX %+ _X509at_add1_attr_by_OBJ
%xdefine X509at_add1_attr_by_txt XCRYPTO_PREFIX %+ _X509at_add1_attr_by_txt
%xdefine X509at_delete_attr XCRYPTO_PREFIX %+ _X509at_delete_attr
%xdefine X509at_get0_data_by_OBJ XCRYPTO_PREFIX %+ _X509at_get0_data_by_OBJ
%xdefine X509at_get_attr XCRYPTO_PREFIX %+ _X509at_get_attr
%xdefine X509at_get_attr_by_NID XCRYPTO_PREFIX %+ _X509at_get_attr_by_NID
%xdefine X509at_get_attr_by_OBJ XCRYPTO_PREFIX %+ _X509at_get_attr_by_OBJ
%xdefine X509at_get_attr_count XCRYPTO_PREFIX %+ _X509at_get_attr_count
%xdefine X509v3_add_ext XCRYPTO_PREFIX %+ _X509v3_add_ext
%xdefine X509v3_delete_ext XCRYPTO_PREFIX %+ _X509v3_delete_ext
%xdefine X509v3_get_ext XCRYPTO_PREFIX %+ _X509v3_get_ext
%xdefine X509v3_get_ext_by_NID XCRYPTO_PREFIX %+ _X509v3_get_ext_by_NID
%xdefine X509v3_get_ext_by_OBJ XCRYPTO_PREFIX %+ _X509v3_get_ext_by_OBJ
%xdefine X509v3_get_ext_by_critical XCRYPTO_PREFIX %+ _X509v3_get_ext_by_critical
%xdefine X509v3_get_ext_count XCRYPTO_PREFIX %+ _X509v3_get_ext_count
%xdefine __clang_at_available_requires_core_foundation_framework XCRYPTO_PREFIX %+ ___clang_at_available_requires_core_foundation_framework
%xdefine __clang_call_terminate XCRYPTO_PREFIX %+ ___clang_call_terminate
%xdefine a2i_GENERAL_NAME XCRYPTO_PREFIX %+ _a2i_GENERAL_NAME
%xdefine a2i_IPADDRESS XCRYPTO_PREFIX %+ _a2i_IPADDRESS
%xdefine a2i_IPADDRESS_NC XCRYPTO_PREFIX %+ _a2i_IPADDRESS_NC
%xdefine a2i_ipadd XCRYPTO_PREFIX %+ _a2i_ipadd
%xdefine aes128gcmsiv_aes_ks XCRYPTO_PREFIX %+ _aes128gcmsiv_aes_ks
%xdefine aes128gcmsiv_aes_ks_enc_x1 XCRYPTO_PREFIX %+ _aes128gcmsiv_aes_ks_enc_x1
%xdefine aes128gcmsiv_dec XCRYPTO_PREFIX %+ _aes128gcmsiv_dec
%xdefine aes128gcmsiv_ecb_enc_block XCRYPTO_PREFIX %+ _aes128gcmsiv_ecb_enc_block
%xdefine aes128gcmsiv_enc_msg_x4 XCRYPTO_PREFIX %+ _aes128gcmsiv_enc_msg_x4
%xdefine aes128gcmsiv_enc_msg_x8 XCRYPTO_PREFIX %+ _aes128gcmsiv_enc_msg_x8
%xdefine aes128gcmsiv_kdf XCRYPTO_PREFIX %+ _aes128gcmsiv_kdf
%xdefine aes256gcmsiv_aes_ks XCRYPTO_PREFIX %+ _aes256gcmsiv_aes_ks
%xdefine aes256gcmsiv_aes_ks_enc_x1 XCRYPTO_PREFIX %+ _aes256gcmsiv_aes_ks_enc_x1
%xdefine aes256gcmsiv_dec XCRYPTO_PREFIX %+ _aes256gcmsiv_dec
%xdefine aes256gcmsiv_ecb_enc_block XCRYPTO_PREFIX %+ _aes256gcmsiv_ecb_enc_block
%xdefine aes256gcmsiv_enc_msg_x4 XCRYPTO_PREFIX %+ _aes256gcmsiv_enc_msg_x4
%xdefine aes256gcmsiv_enc_msg_x8 XCRYPTO_PREFIX %+ _aes256gcmsiv_enc_msg_x8
%xdefine aes256gcmsiv_kdf XCRYPTO_PREFIX %+ _aes256gcmsiv_kdf
%xdefine aes_ctr_set_key XCRYPTO_PREFIX %+ _aes_ctr_set_key
%xdefine aes_hw_cbc_encrypt XCRYPTO_PREFIX %+ _aes_hw_cbc_encrypt
%xdefine aes_hw_ctr32_encrypt_blocks XCRYPTO_PREFIX %+ _aes_hw_ctr32_encrypt_blocks
%xdefine aes_hw_decrypt XCRYPTO_PREFIX %+ _aes_hw_decrypt
%xdefine aes_hw_ecb_encrypt XCRYPTO_PREFIX %+ _aes_hw_ecb_encrypt
%xdefine aes_hw_encrypt XCRYPTO_PREFIX %+ _aes_hw_encrypt
%xdefine aes_hw_set_decrypt_key XCRYPTO_PREFIX %+ _aes_hw_set_decrypt_key
%xdefine aes_hw_set_encrypt_key XCRYPTO_PREFIX %+ _aes_hw_set_encrypt_key
%xdefine aes_nohw_cbc_encrypt XCRYPTO_PREFIX %+ _aes_nohw_cbc_encrypt
%xdefine aes_nohw_ctr32_encrypt_blocks XCRYPTO_PREFIX %+ _aes_nohw_ctr32_encrypt_blocks
%xdefine aes_nohw_decrypt XCRYPTO_PREFIX %+ _aes_nohw_decrypt
%xdefine aes_nohw_encrypt XCRYPTO_PREFIX %+ _aes_nohw_encrypt
%xdefine aes_nohw_set_decrypt_key XCRYPTO_PREFIX %+ _aes_nohw_set_decrypt_key
%xdefine aes_nohw_set_encrypt_key XCRYPTO_PREFIX %+ _aes_nohw_set_encrypt_key
%xdefine aesgcmsiv_htable6_init XCRYPTO_PREFIX %+ _aesgcmsiv_htable6_init
%xdefine aesgcmsiv_htable_init XCRYPTO_PREFIX %+ _aesgcmsiv_htable_init
%xdefine aesgcmsiv_htable_polyval XCRYPTO_PREFIX %+ _aesgcmsiv_htable_polyval
%xdefine aesgcmsiv_polyval_horner XCRYPTO_PREFIX %+ _aesgcmsiv_polyval_horner
%xdefine aesni_gcm_decrypt XCRYPTO_PREFIX %+ _aesni_gcm_decrypt
%xdefine aesni_gcm_encrypt XCRYPTO_PREFIX %+ _aesni_gcm_encrypt
%xdefine asn1_do_adb XCRYPTO_PREFIX %+ _asn1_do_adb
%xdefine asn1_enc_free XCRYPTO_PREFIX %+ _asn1_enc_free
%xdefine asn1_enc_init XCRYPTO_PREFIX %+ _asn1_enc_init
%xdefine asn1_enc_restore XCRYPTO_PREFIX %+ _asn1_enc_restore
%xdefine asn1_enc_save XCRYPTO_PREFIX %+ _asn1_enc_save
%xdefine asn1_ex_c2i XCRYPTO_PREFIX %+ _asn1_ex_c2i
%xdefine asn1_ex_i2c XCRYPTO_PREFIX %+ _asn1_ex_i2c
%xdefine asn1_generalizedtime_to_tm XCRYPTO_PREFIX %+ _asn1_generalizedtime_to_tm
%xdefine asn1_get_choice_selector XCRYPTO_PREFIX %+ _asn1_get_choice_selector
%xdefine asn1_get_field_ptr XCRYPTO_PREFIX %+ _asn1_get_field_ptr
%xdefine asn1_item_combine_free XCRYPTO_PREFIX %+ _asn1_item_combine_free
%xdefine asn1_refcount_dec_and_test_zero XCRYPTO_PREFIX %+ _asn1_refcount_dec_and_test_zero
%xdefine asn1_refcount_set_one XCRYPTO_PREFIX %+ _asn1_refcount_set_one
%xdefine asn1_set_choice_selector XCRYPTO_PREFIX %+ _asn1_set_choice_selector
%xdefine asn1_utctime_to_tm XCRYPTO_PREFIX %+ _asn1_utctime_to_tm
%xdefine beeu_mod_inverse_vartime XCRYPTO_PREFIX %+ _beeu_mod_inverse_vartime
%xdefine bio_clear_socket_error XCRYPTO_PREFIX %+ _bio_clear_socket_error
%xdefine bio_fd_should_retry XCRYPTO_PREFIX %+ _bio_fd_should_retry
%xdefine bio_ip_and_port_to_socket_and_addr XCRYPTO_PREFIX %+ _bio_ip_and_port_to_socket_and_addr
%xdefine bio_sock_error XCRYPTO_PREFIX %+ _bio_sock_error
%xdefine bio_socket_nbio XCRYPTO_PREFIX %+ _bio_socket_nbio
%xdefine bn_abs_sub_consttime XCRYPTO_PREFIX %+ _bn_abs_sub_consttime
%xdefine bn_add_words XCRYPTO_PREFIX %+ _bn_add_words
%xdefine bn_copy_words XCRYPTO_PREFIX %+ _bn_copy_words
%xdefine bn_div_consttime XCRYPTO_PREFIX %+ _bn_div_consttime
%xdefine bn_expand XCRYPTO_PREFIX %+ _bn_expand
%xdefine bn_fits_in_words XCRYPTO_PREFIX %+ _bn_fits_in_words
%xdefine bn_from_montgomery XCRYPTO_PREFIX %+ _bn_from_montgomery
%xdefine bn_from_montgomery_small XCRYPTO_PREFIX %+ _bn_from_montgomery_small
%xdefine bn_gather5 XCRYPTO_PREFIX %+ _bn_gather5
%xdefine bn_in_range_words XCRYPTO_PREFIX %+ _bn_in_range_words
%xdefine bn_is_bit_set_words XCRYPTO_PREFIX %+ _bn_is_bit_set_words
%xdefine bn_is_relatively_prime XCRYPTO_PREFIX %+ _bn_is_relatively_prime
%xdefine bn_jacobi XCRYPTO_PREFIX %+ _bn_jacobi
%xdefine bn_lcm_consttime XCRYPTO_PREFIX %+ _bn_lcm_consttime
%xdefine bn_less_than_montgomery_R XCRYPTO_PREFIX %+ _bn_less_than_montgomery_R
%xdefine bn_less_than_words XCRYPTO_PREFIX %+ _bn_less_than_words
%xdefine bn_miller_rabin_init XCRYPTO_PREFIX %+ _bn_miller_rabin_init
%xdefine bn_miller_rabin_iteration XCRYPTO_PREFIX %+ _bn_miller_rabin_iteration
%xdefine bn_minimal_width XCRYPTO_PREFIX %+ _bn_minimal_width
%xdefine bn_mod_add_consttime XCRYPTO_PREFIX %+ _bn_mod_add_consttime
%xdefine bn_mod_add_words XCRYPTO_PREFIX %+ _bn_mod_add_words
%xdefine bn_mod_exp_base_2_consttime XCRYPTO_PREFIX %+ _bn_mod_exp_base_2_consttime
%xdefine bn_mod_exp_mont_small XCRYPTO_PREFIX %+ _bn_mod_exp_mont_small
%xdefine bn_mod_inverse0_prime_mont_small XCRYPTO_PREFIX %+ _bn_mod_inverse0_prime_mont_small
%xdefine bn_mod_inverse_consttime XCRYPTO_PREFIX %+ _bn_mod_inverse_consttime
%xdefine bn_mod_inverse_prime XCRYPTO_PREFIX %+ _bn_mod_inverse_prime
%xdefine bn_mod_inverse_secret_prime XCRYPTO_PREFIX %+ _bn_mod_inverse_secret_prime
%xdefine bn_mod_lshift1_consttime XCRYPTO_PREFIX %+ _bn_mod_lshift1_consttime
%xdefine bn_mod_lshift_consttime XCRYPTO_PREFIX %+ _bn_mod_lshift_consttime
%xdefine bn_mod_mul_montgomery_small XCRYPTO_PREFIX %+ _bn_mod_mul_montgomery_small
%xdefine bn_mod_sub_consttime XCRYPTO_PREFIX %+ _bn_mod_sub_consttime
%xdefine bn_mod_sub_words XCRYPTO_PREFIX %+ _bn_mod_sub_words
%xdefine bn_mod_u16_consttime XCRYPTO_PREFIX %+ _bn_mod_u16_consttime
%xdefine bn_mont_n0 XCRYPTO_PREFIX %+ _bn_mont_n0
%xdefine bn_mul_add_words XCRYPTO_PREFIX %+ _bn_mul_add_words
%xdefine bn_mul_comba4 XCRYPTO_PREFIX %+ _bn_mul_comba4
%xdefine bn_mul_comba8 XCRYPTO_PREFIX %+ _bn_mul_comba8
%xdefine bn_mul_consttime XCRYPTO_PREFIX %+ _bn_mul_consttime
%xdefine bn_mul_mont XCRYPTO_PREFIX %+ _bn_mul_mont
%xdefine bn_mul_mont_gather5 XCRYPTO_PREFIX %+ _bn_mul_mont_gather5
%xdefine bn_mul_small XCRYPTO_PREFIX %+ _bn_mul_small
%xdefine bn_mul_words XCRYPTO_PREFIX %+ _bn_mul_words
%xdefine bn_odd_number_is_obviously_composite XCRYPTO_PREFIX %+ _bn_odd_number_is_obviously_composite
%xdefine bn_one_to_montgomery XCRYPTO_PREFIX %+ _bn_one_to_montgomery
%xdefine bn_power5 XCRYPTO_PREFIX %+ _bn_power5
%xdefine bn_rand_range_words XCRYPTO_PREFIX %+ _bn_rand_range_words
%xdefine bn_rand_secret_range XCRYPTO_PREFIX %+ _bn_rand_secret_range
%xdefine bn_reduce_once XCRYPTO_PREFIX %+ _bn_reduce_once
%xdefine bn_reduce_once_in_place XCRYPTO_PREFIX %+ _bn_reduce_once_in_place
%xdefine bn_resize_words XCRYPTO_PREFIX %+ _bn_resize_words
%xdefine bn_rshift1_words XCRYPTO_PREFIX %+ _bn_rshift1_words
%xdefine bn_rshift_secret_shift XCRYPTO_PREFIX %+ _bn_rshift_secret_shift
%xdefine bn_rshift_words XCRYPTO_PREFIX %+ _bn_rshift_words
%xdefine bn_scatter5 XCRYPTO_PREFIX %+ _bn_scatter5
%xdefine bn_select_words XCRYPTO_PREFIX %+ _bn_select_words
%xdefine bn_set_minimal_width XCRYPTO_PREFIX %+ _bn_set_minimal_width
%xdefine bn_set_words XCRYPTO_PREFIX %+ _bn_set_words
%xdefine bn_sqr8x_internal XCRYPTO_PREFIX %+ _bn_sqr8x_internal
%xdefine bn_sqr_comba4 XCRYPTO_PREFIX %+ _bn_sqr_comba4
%xdefine bn_sqr_comba8 XCRYPTO_PREFIX %+ _bn_sqr_comba8
%xdefine bn_sqr_consttime XCRYPTO_PREFIX %+ _bn_sqr_consttime
%xdefine bn_sqr_small XCRYPTO_PREFIX %+ _bn_sqr_small
%xdefine bn_sqr_words XCRYPTO_PREFIX %+ _bn_sqr_words
%xdefine bn_sqrx8x_internal XCRYPTO_PREFIX %+ _bn_sqrx8x_internal
%xdefine bn_sub_words XCRYPTO_PREFIX %+ _bn_sub_words
%xdefine bn_to_montgomery_small XCRYPTO_PREFIX %+ _bn_to_montgomery_small
%xdefine bn_uadd_consttime XCRYPTO_PREFIX %+ _bn_uadd_consttime
%xdefine bn_usub_consttime XCRYPTO_PREFIX %+ _bn_usub_consttime
%xdefine bn_wexpand XCRYPTO_PREFIX %+ _bn_wexpand
%xdefine boringssl_fips_self_test XCRYPTO_PREFIX %+ _boringssl_fips_self_test
%xdefine c2i_ASN1_BIT_STRING XCRYPTO_PREFIX %+ _c2i_ASN1_BIT_STRING
%xdefine c2i_ASN1_INTEGER XCRYPTO_PREFIX %+ _c2i_ASN1_INTEGER
%xdefine c2i_ASN1_OBJECT XCRYPTO_PREFIX %+ _c2i_ASN1_OBJECT
%xdefine cbb_add_latin1 XCRYPTO_PREFIX %+ _cbb_add_latin1
%xdefine cbb_add_ucs2_be XCRYPTO_PREFIX %+ _cbb_add_ucs2_be
%xdefine cbb_add_utf32_be XCRYPTO_PREFIX %+ _cbb_add_utf32_be
%xdefine cbb_add_utf8 XCRYPTO_PREFIX %+ _cbb_add_utf8
%xdefine cbb_get_utf8_len XCRYPTO_PREFIX %+ _cbb_get_utf8_len
%xdefine cbs_get_latin1 XCRYPTO_PREFIX %+ _cbs_get_latin1
%xdefine cbs_get_ucs2_be XCRYPTO_PREFIX %+ _cbs_get_ucs2_be
%xdefine cbs_get_utf32_be XCRYPTO_PREFIX %+ _cbs_get_utf32_be
%xdefine cbs_get_utf8 XCRYPTO_PREFIX %+ _cbs_get_utf8
%xdefine chacha20_poly1305_open XCRYPTO_PREFIX %+ _chacha20_poly1305_open
%xdefine chacha20_poly1305_seal XCRYPTO_PREFIX %+ _chacha20_poly1305_seal
%xdefine crypto_gcm_clmul_enabled XCRYPTO_PREFIX %+ _crypto_gcm_clmul_enabled
%xdefine d2i_ACCESS_DESCRIPTION XCRYPTO_PREFIX %+ _d2i_ACCESS_DESCRIPTION
%xdefine d2i_ASN1_BIT_STRING XCRYPTO_PREFIX %+ _d2i_ASN1_BIT_STRING
%xdefine d2i_ASN1_BMPSTRING XCRYPTO_PREFIX %+ _d2i_ASN1_BMPSTRING
%xdefine d2i_ASN1_BOOLEAN XCRYPTO_PREFIX %+ _d2i_ASN1_BOOLEAN
%xdefine d2i_ASN1_ENUMERATED XCRYPTO_PREFIX %+ _d2i_ASN1_ENUMERATED
%xdefine d2i_ASN1_GENERALIZEDTIME XCRYPTO_PREFIX %+ _d2i_ASN1_GENERALIZEDTIME
%xdefine d2i_ASN1_GENERALSTRING XCRYPTO_PREFIX %+ _d2i_ASN1_GENERALSTRING
%xdefine d2i_ASN1_IA5STRING XCRYPTO_PREFIX %+ _d2i_ASN1_IA5STRING
%xdefine d2i_ASN1_INTEGER XCRYPTO_PREFIX %+ _d2i_ASN1_INTEGER
%xdefine d2i_ASN1_NULL XCRYPTO_PREFIX %+ _d2i_ASN1_NULL
%xdefine d2i_ASN1_OBJECT XCRYPTO_PREFIX %+ _d2i_ASN1_OBJECT
%xdefine d2i_ASN1_OCTET_STRING XCRYPTO_PREFIX %+ _d2i_ASN1_OCTET_STRING
%xdefine d2i_ASN1_PRINTABLE XCRYPTO_PREFIX %+ _d2i_ASN1_PRINTABLE
%xdefine d2i_ASN1_PRINTABLESTRING XCRYPTO_PREFIX %+ _d2i_ASN1_PRINTABLESTRING
%xdefine d2i_ASN1_SEQUENCE_ANY XCRYPTO_PREFIX %+ _d2i_ASN1_SEQUENCE_ANY
%xdefine d2i_ASN1_SET_ANY XCRYPTO_PREFIX %+ _d2i_ASN1_SET_ANY
%xdefine d2i_ASN1_T61STRING XCRYPTO_PREFIX %+ _d2i_ASN1_T61STRING
%xdefine d2i_ASN1_TIME XCRYPTO_PREFIX %+ _d2i_ASN1_TIME
%xdefine d2i_ASN1_TYPE XCRYPTO_PREFIX %+ _d2i_ASN1_TYPE
%xdefine d2i_ASN1_UNIVERSALSTRING XCRYPTO_PREFIX %+ _d2i_ASN1_UNIVERSALSTRING
%xdefine d2i_ASN1_UTCTIME XCRYPTO_PREFIX %+ _d2i_ASN1_UTCTIME
%xdefine d2i_ASN1_UTF8STRING XCRYPTO_PREFIX %+ _d2i_ASN1_UTF8STRING
%xdefine d2i_ASN1_VISIBLESTRING XCRYPTO_PREFIX %+ _d2i_ASN1_VISIBLESTRING
%xdefine d2i_AUTHORITY_INFO_ACCESS XCRYPTO_PREFIX %+ _d2i_AUTHORITY_INFO_ACCESS
%xdefine d2i_AUTHORITY_KEYID XCRYPTO_PREFIX %+ _d2i_AUTHORITY_KEYID
%xdefine d2i_AutoPrivateKey XCRYPTO_PREFIX %+ _d2i_AutoPrivateKey
%xdefine d2i_BASIC_CONSTRAINTS XCRYPTO_PREFIX %+ _d2i_BASIC_CONSTRAINTS
%xdefine d2i_CERTIFICATEPOLICIES XCRYPTO_PREFIX %+ _d2i_CERTIFICATEPOLICIES
%xdefine d2i_CRL_DIST_POINTS XCRYPTO_PREFIX %+ _d2i_CRL_DIST_POINTS
%xdefine d2i_DHparams XCRYPTO_PREFIX %+ _d2i_DHparams
%xdefine d2i_DHparams_bio XCRYPTO_PREFIX %+ _d2i_DHparams_bio
%xdefine d2i_DIRECTORYSTRING XCRYPTO_PREFIX %+ _d2i_DIRECTORYSTRING
%xdefine d2i_DISPLAYTEXT XCRYPTO_PREFIX %+ _d2i_DISPLAYTEXT
%xdefine d2i_DIST_POINT XCRYPTO_PREFIX %+ _d2i_DIST_POINT
%xdefine d2i_DIST_POINT_NAME XCRYPTO_PREFIX %+ _d2i_DIST_POINT_NAME
%xdefine d2i_DSAPrivateKey XCRYPTO_PREFIX %+ _d2i_DSAPrivateKey
%xdefine d2i_DSAPrivateKey_bio XCRYPTO_PREFIX %+ _d2i_DSAPrivateKey_bio
%xdefine d2i_DSAPrivateKey_fp XCRYPTO_PREFIX %+ _d2i_DSAPrivateKey_fp
%xdefine d2i_DSAPublicKey XCRYPTO_PREFIX %+ _d2i_DSAPublicKey
%xdefine d2i_DSA_PUBKEY XCRYPTO_PREFIX %+ _d2i_DSA_PUBKEY
%xdefine d2i_DSA_PUBKEY_bio XCRYPTO_PREFIX %+ _d2i_DSA_PUBKEY_bio
%xdefine d2i_DSA_PUBKEY_fp XCRYPTO_PREFIX %+ _d2i_DSA_PUBKEY_fp
%xdefine d2i_DSA_SIG XCRYPTO_PREFIX %+ _d2i_DSA_SIG
%xdefine d2i_DSAparams XCRYPTO_PREFIX %+ _d2i_DSAparams
%xdefine d2i_ECDSA_SIG XCRYPTO_PREFIX %+ _d2i_ECDSA_SIG
%xdefine d2i_ECParameters XCRYPTO_PREFIX %+ _d2i_ECParameters
%xdefine d2i_ECPrivateKey XCRYPTO_PREFIX %+ _d2i_ECPrivateKey
%xdefine d2i_ECPrivateKey_bio XCRYPTO_PREFIX %+ _d2i_ECPrivateKey_bio
%xdefine d2i_ECPrivateKey_fp XCRYPTO_PREFIX %+ _d2i_ECPrivateKey_fp
%xdefine d2i_EC_PUBKEY XCRYPTO_PREFIX %+ _d2i_EC_PUBKEY
%xdefine d2i_EC_PUBKEY_bio XCRYPTO_PREFIX %+ _d2i_EC_PUBKEY_bio
%xdefine d2i_EC_PUBKEY_fp XCRYPTO_PREFIX %+ _d2i_EC_PUBKEY_fp
%xdefine d2i_EDIPARTYNAME XCRYPTO_PREFIX %+ _d2i_EDIPARTYNAME
%xdefine d2i_EXTENDED_KEY_USAGE XCRYPTO_PREFIX %+ _d2i_EXTENDED_KEY_USAGE
%xdefine d2i_GENERAL_NAME XCRYPTO_PREFIX %+ _d2i_GENERAL_NAME
%xdefine d2i_GENERAL_NAMES XCRYPTO_PREFIX %+ _d2i_GENERAL_NAMES
%xdefine d2i_ISSUING_DIST_POINT XCRYPTO_PREFIX %+ _d2i_ISSUING_DIST_POINT
%xdefine d2i_NETSCAPE_SPKAC XCRYPTO_PREFIX %+ _d2i_NETSCAPE_SPKAC
%xdefine d2i_NETSCAPE_SPKI XCRYPTO_PREFIX %+ _d2i_NETSCAPE_SPKI
%xdefine d2i_NOTICEREF XCRYPTO_PREFIX %+ _d2i_NOTICEREF
%xdefine d2i_OTHERNAME XCRYPTO_PREFIX %+ _d2i_OTHERNAME
%xdefine d2i_PKCS12 XCRYPTO_PREFIX %+ _d2i_PKCS12
%xdefine d2i_PKCS12_bio XCRYPTO_PREFIX %+ _d2i_PKCS12_bio
%xdefine d2i_PKCS12_fp XCRYPTO_PREFIX %+ _d2i_PKCS12_fp
%xdefine d2i_PKCS7 XCRYPTO_PREFIX %+ _d2i_PKCS7
%xdefine d2i_PKCS7_bio XCRYPTO_PREFIX %+ _d2i_PKCS7_bio
%xdefine d2i_PKCS8PrivateKey_bio XCRYPTO_PREFIX %+ _d2i_PKCS8PrivateKey_bio
%xdefine d2i_PKCS8PrivateKey_fp XCRYPTO_PREFIX %+ _d2i_PKCS8PrivateKey_fp
%xdefine d2i_PKCS8_PRIV_KEY_INFO XCRYPTO_PREFIX %+ _d2i_PKCS8_PRIV_KEY_INFO
%xdefine d2i_PKCS8_PRIV_KEY_INFO_bio XCRYPTO_PREFIX %+ _d2i_PKCS8_PRIV_KEY_INFO_bio
%xdefine d2i_PKCS8_PRIV_KEY_INFO_fp XCRYPTO_PREFIX %+ _d2i_PKCS8_PRIV_KEY_INFO_fp
%xdefine d2i_PKCS8_bio XCRYPTO_PREFIX %+ _d2i_PKCS8_bio
%xdefine d2i_PKCS8_fp XCRYPTO_PREFIX %+ _d2i_PKCS8_fp
%xdefine d2i_PKEY_USAGE_PERIOD XCRYPTO_PREFIX %+ _d2i_PKEY_USAGE_PERIOD
%xdefine d2i_POLICYINFO XCRYPTO_PREFIX %+ _d2i_POLICYINFO
%xdefine d2i_POLICYQUALINFO XCRYPTO_PREFIX %+ _d2i_POLICYQUALINFO
%xdefine d2i_PROXY_CERT_INFO_EXTENSION XCRYPTO_PREFIX %+ _d2i_PROXY_CERT_INFO_EXTENSION
%xdefine d2i_PROXY_POLICY XCRYPTO_PREFIX %+ _d2i_PROXY_POLICY
%xdefine d2i_PUBKEY XCRYPTO_PREFIX %+ _d2i_PUBKEY
%xdefine d2i_PUBKEY_bio XCRYPTO_PREFIX %+ _d2i_PUBKEY_bio
%xdefine d2i_PUBKEY_fp XCRYPTO_PREFIX %+ _d2i_PUBKEY_fp
%xdefine d2i_PrivateKey XCRYPTO_PREFIX %+ _d2i_PrivateKey
%xdefine d2i_PrivateKey_bio XCRYPTO_PREFIX %+ _d2i_PrivateKey_bio
%xdefine d2i_PrivateKey_fp XCRYPTO_PREFIX %+ _d2i_PrivateKey_fp
%xdefine d2i_PublicKey XCRYPTO_PREFIX %+ _d2i_PublicKey
%xdefine d2i_RSAPrivateKey XCRYPTO_PREFIX %+ _d2i_RSAPrivateKey
%xdefine d2i_RSAPrivateKey_bio XCRYPTO_PREFIX %+ _d2i_RSAPrivateKey_bio
%xdefine d2i_RSAPrivateKey_fp XCRYPTO_PREFIX %+ _d2i_RSAPrivateKey_fp
%xdefine d2i_RSAPublicKey XCRYPTO_PREFIX %+ _d2i_RSAPublicKey
%xdefine d2i_RSAPublicKey_bio XCRYPTO_PREFIX %+ _d2i_RSAPublicKey_bio
%xdefine d2i_RSAPublicKey_fp XCRYPTO_PREFIX %+ _d2i_RSAPublicKey_fp
%xdefine d2i_RSA_PSS_PARAMS XCRYPTO_PREFIX %+ _d2i_RSA_PSS_PARAMS
%xdefine d2i_RSA_PUBKEY XCRYPTO_PREFIX %+ _d2i_RSA_PUBKEY
%xdefine d2i_RSA_PUBKEY_bio XCRYPTO_PREFIX %+ _d2i_RSA_PUBKEY_bio
%xdefine d2i_RSA_PUBKEY_fp XCRYPTO_PREFIX %+ _d2i_RSA_PUBKEY_fp
%xdefine d2i_SSL_SESSION XCRYPTO_PREFIX %+ _d2i_SSL_SESSION
%xdefine d2i_SSL_SESSION_bio XCRYPTO_PREFIX %+ _d2i_SSL_SESSION_bio
%xdefine d2i_SXNET XCRYPTO_PREFIX %+ _d2i_SXNET
%xdefine d2i_SXNETID XCRYPTO_PREFIX %+ _d2i_SXNETID
%xdefine d2i_USERNOTICE XCRYPTO_PREFIX %+ _d2i_USERNOTICE
%xdefine d2i_X509 XCRYPTO_PREFIX %+ _d2i_X509
%xdefine d2i_X509_ALGOR XCRYPTO_PREFIX %+ _d2i_X509_ALGOR
%xdefine d2i_X509_ALGORS XCRYPTO_PREFIX %+ _d2i_X509_ALGORS
%xdefine d2i_X509_ATTRIBUTE XCRYPTO_PREFIX %+ _d2i_X509_ATTRIBUTE
%xdefine d2i_X509_AUX XCRYPTO_PREFIX %+ _d2i_X509_AUX
%xdefine d2i_X509_CERT_AUX XCRYPTO_PREFIX %+ _d2i_X509_CERT_AUX
%xdefine d2i_X509_CINF XCRYPTO_PREFIX %+ _d2i_X509_CINF
%xdefine d2i_X509_CRL XCRYPTO_PREFIX %+ _d2i_X509_CRL
%xdefine d2i_X509_CRL_INFO XCRYPTO_PREFIX %+ _d2i_X509_CRL_INFO
%xdefine d2i_X509_CRL_bio XCRYPTO_PREFIX %+ _d2i_X509_CRL_bio
%xdefine d2i_X509_CRL_fp XCRYPTO_PREFIX %+ _d2i_X509_CRL_fp
%xdefine d2i_X509_EXTENSION XCRYPTO_PREFIX %+ _d2i_X509_EXTENSION
%xdefine d2i_X509_EXTENSIONS XCRYPTO_PREFIX %+ _d2i_X509_EXTENSIONS
%xdefine d2i_X509_NAME XCRYPTO_PREFIX %+ _d2i_X509_NAME
%xdefine d2i_X509_NAME_ENTRY XCRYPTO_PREFIX %+ _d2i_X509_NAME_ENTRY
%xdefine d2i_X509_PUBKEY XCRYPTO_PREFIX %+ _d2i_X509_PUBKEY
%xdefine d2i_X509_REQ XCRYPTO_PREFIX %+ _d2i_X509_REQ
%xdefine d2i_X509_REQ_INFO XCRYPTO_PREFIX %+ _d2i_X509_REQ_INFO
%xdefine d2i_X509_REQ_bio XCRYPTO_PREFIX %+ _d2i_X509_REQ_bio
%xdefine d2i_X509_REQ_fp XCRYPTO_PREFIX %+ _d2i_X509_REQ_fp
%xdefine d2i_X509_REVOKED XCRYPTO_PREFIX %+ _d2i_X509_REVOKED
%xdefine d2i_X509_SIG XCRYPTO_PREFIX %+ _d2i_X509_SIG
%xdefine d2i_X509_VAL XCRYPTO_PREFIX %+ _d2i_X509_VAL
%xdefine d2i_X509_bio XCRYPTO_PREFIX %+ _d2i_X509_bio
%xdefine d2i_X509_fp XCRYPTO_PREFIX %+ _d2i_X509_fp
%xdefine dsa_asn1_meth XCRYPTO_PREFIX %+ _dsa_asn1_meth
%xdefine ec_GFp_mont_add XCRYPTO_PREFIX %+ _ec_GFp_mont_add
%xdefine ec_GFp_mont_dbl XCRYPTO_PREFIX %+ _ec_GFp_mont_dbl
%xdefine ec_GFp_mont_felem_from_bytes XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_from_bytes
%xdefine ec_GFp_mont_felem_mul XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_mul
%xdefine ec_GFp_mont_felem_sqr XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_sqr
%xdefine ec_GFp_mont_felem_to_bytes XCRYPTO_PREFIX %+ _ec_GFp_mont_felem_to_bytes
%xdefine ec_GFp_mont_group_finish XCRYPTO_PREFIX %+ _ec_GFp_mont_group_finish
%xdefine ec_GFp_mont_group_init XCRYPTO_PREFIX %+ _ec_GFp_mont_group_init
%xdefine ec_GFp_mont_group_set_curve XCRYPTO_PREFIX %+ _ec_GFp_mont_group_set_curve
%xdefine ec_GFp_mont_init_precomp XCRYPTO_PREFIX %+ _ec_GFp_mont_init_precomp
%xdefine ec_GFp_mont_mul XCRYPTO_PREFIX %+ _ec_GFp_mont_mul
%xdefine ec_GFp_mont_mul_base XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_base
%xdefine ec_GFp_mont_mul_batch XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_batch
%xdefine ec_GFp_mont_mul_precomp XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_precomp
%xdefine ec_GFp_mont_mul_public XCRYPTO_PREFIX %+ _ec_GFp_mont_mul_public
%xdefine ec_GFp_nistp_recode_scalar_bits XCRYPTO_PREFIX %+ _ec_GFp_nistp_recode_scalar_bits
%xdefine ec_GFp_simple_cmp_x_coordinate XCRYPTO_PREFIX %+ _ec_GFp_simple_cmp_x_coordinate
%xdefine ec_GFp_simple_felem_from_bytes XCRYPTO_PREFIX %+ _ec_GFp_simple_felem_from_bytes
%xdefine ec_GFp_simple_felem_to_bytes XCRYPTO_PREFIX %+ _ec_GFp_simple_felem_to_bytes
%xdefine ec_GFp_simple_group_finish XCRYPTO_PREFIX %+ _ec_GFp_simple_group_finish
%xdefine ec_GFp_simple_group_get_curve XCRYPTO_PREFIX %+ _ec_GFp_simple_group_get_curve
%xdefine ec_GFp_simple_group_init XCRYPTO_PREFIX %+ _ec_GFp_simple_group_init
%xdefine ec_GFp_simple_group_set_curve XCRYPTO_PREFIX %+ _ec_GFp_simple_group_set_curve
%xdefine ec_GFp_simple_invert XCRYPTO_PREFIX %+ _ec_GFp_simple_invert
%xdefine ec_GFp_simple_is_at_infinity XCRYPTO_PREFIX %+ _ec_GFp_simple_is_at_infinity
%xdefine ec_GFp_simple_is_on_curve XCRYPTO_PREFIX %+ _ec_GFp_simple_is_on_curve
%xdefine ec_GFp_simple_point_copy XCRYPTO_PREFIX %+ _ec_GFp_simple_point_copy
%xdefine ec_GFp_simple_point_init XCRYPTO_PREFIX %+ _ec_GFp_simple_point_init
%xdefine ec_GFp_simple_point_set_to_infinity XCRYPTO_PREFIX %+ _ec_GFp_simple_point_set_to_infinity
%xdefine ec_GFp_simple_points_equal XCRYPTO_PREFIX %+ _ec_GFp_simple_points_equal
%xdefine ec_affine_jacobian_equal XCRYPTO_PREFIX %+ _ec_affine_jacobian_equal
%xdefine ec_affine_select XCRYPTO_PREFIX %+ _ec_affine_select
%xdefine ec_affine_to_jacobian XCRYPTO_PREFIX %+ _ec_affine_to_jacobian
%xdefine ec_asn1_meth XCRYPTO_PREFIX %+ _ec_asn1_meth
%xdefine ec_bignum_to_felem XCRYPTO_PREFIX %+ _ec_bignum_to_felem
%xdefine ec_bignum_to_scalar XCRYPTO_PREFIX %+ _ec_bignum_to_scalar
%xdefine ec_cmp_x_coordinate XCRYPTO_PREFIX %+ _ec_cmp_x_coordinate
%xdefine ec_compute_wNAF XCRYPTO_PREFIX %+ _ec_compute_wNAF
%xdefine ec_felem_add XCRYPTO_PREFIX %+ _ec_felem_add
%xdefine ec_felem_equal XCRYPTO_PREFIX %+ _ec_felem_equal
%xdefine ec_felem_from_bytes XCRYPTO_PREFIX %+ _ec_felem_from_bytes
%xdefine ec_felem_neg XCRYPTO_PREFIX %+ _ec_felem_neg
%xdefine ec_felem_non_zero_mask XCRYPTO_PREFIX %+ _ec_felem_non_zero_mask
%xdefine ec_felem_select XCRYPTO_PREFIX %+ _ec_felem_select
%xdefine ec_felem_sub XCRYPTO_PREFIX %+ _ec_felem_sub
%xdefine ec_felem_to_bignum XCRYPTO_PREFIX %+ _ec_felem_to_bignum
%xdefine ec_felem_to_bytes XCRYPTO_PREFIX %+ _ec_felem_to_bytes
%xdefine ec_get_x_coordinate_as_bytes XCRYPTO_PREFIX %+ _ec_get_x_coordinate_as_bytes
%xdefine ec_get_x_coordinate_as_scalar XCRYPTO_PREFIX %+ _ec_get_x_coordinate_as_scalar
%xdefine ec_group_new XCRYPTO_PREFIX %+ _ec_group_new
%xdefine ec_hash_to_curve_p384_xmd_sha512_sswu_draft07 XCRYPTO_PREFIX %+ _ec_hash_to_curve_p384_xmd_sha512_sswu_draft07
%xdefine ec_hash_to_curve_p521_xmd_sha512_sswu_draft06 XCRYPTO_PREFIX %+ _ec_hash_to_curve_p521_xmd_sha512_sswu_draft06
%xdefine ec_hash_to_scalar_p384_xmd_sha512_draft07 XCRYPTO_PREFIX %+ _ec_hash_to_scalar_p384_xmd_sha512_draft07
%xdefine ec_hash_to_scalar_p521_xmd_sha512_draft06 XCRYPTO_PREFIX %+ _ec_hash_to_scalar_p521_xmd_sha512_draft06
%xdefine ec_init_precomp XCRYPTO_PREFIX %+ _ec_init_precomp
%xdefine ec_jacobian_to_affine XCRYPTO_PREFIX %+ _ec_jacobian_to_affine
%xdefine ec_jacobian_to_affine_batch XCRYPTO_PREFIX %+ _ec_jacobian_to_affine_batch
%xdefine ec_pkey_meth XCRYPTO_PREFIX %+ _ec_pkey_meth
%xdefine ec_point_from_uncompressed XCRYPTO_PREFIX %+ _ec_point_from_uncompressed
%xdefine ec_point_mul_scalar XCRYPTO_PREFIX %+ _ec_point_mul_scalar
%xdefine ec_point_mul_scalar_base XCRYPTO_PREFIX %+ _ec_point_mul_scalar_base
%xdefine ec_point_mul_scalar_batch XCRYPTO_PREFIX %+ _ec_point_mul_scalar_batch
%xdefine ec_point_mul_scalar_precomp XCRYPTO_PREFIX %+ _ec_point_mul_scalar_precomp
%xdefine ec_point_mul_scalar_public XCRYPTO_PREFIX %+ _ec_point_mul_scalar_public
%xdefine ec_point_select XCRYPTO_PREFIX %+ _ec_point_select
%xdefine ec_point_set_affine_coordinates XCRYPTO_PREFIX %+ _ec_point_set_affine_coordinates
%xdefine ec_point_to_bytes XCRYPTO_PREFIX %+ _ec_point_to_bytes
%xdefine ec_precomp_select XCRYPTO_PREFIX %+ _ec_precomp_select
%xdefine ec_random_nonzero_scalar XCRYPTO_PREFIX %+ _ec_random_nonzero_scalar
%xdefine ec_scalar_add XCRYPTO_PREFIX %+ _ec_scalar_add
%xdefine ec_scalar_equal_vartime XCRYPTO_PREFIX %+ _ec_scalar_equal_vartime
%xdefine ec_scalar_from_bytes XCRYPTO_PREFIX %+ _ec_scalar_from_bytes
%xdefine ec_scalar_from_montgomery XCRYPTO_PREFIX %+ _ec_scalar_from_montgomery
%xdefine ec_scalar_inv0_montgomery XCRYPTO_PREFIX %+ _ec_scalar_inv0_montgomery
%xdefine ec_scalar_is_zero XCRYPTO_PREFIX %+ _ec_scalar_is_zero
%xdefine ec_scalar_mul_montgomery XCRYPTO_PREFIX %+ _ec_scalar_mul_montgomery
%xdefine ec_scalar_neg XCRYPTO_PREFIX %+ _ec_scalar_neg
%xdefine ec_scalar_reduce XCRYPTO_PREFIX %+ _ec_scalar_reduce
%xdefine ec_scalar_select XCRYPTO_PREFIX %+ _ec_scalar_select
%xdefine ec_scalar_sub XCRYPTO_PREFIX %+ _ec_scalar_sub
%xdefine ec_scalar_to_bytes XCRYPTO_PREFIX %+ _ec_scalar_to_bytes
%xdefine ec_scalar_to_montgomery XCRYPTO_PREFIX %+ _ec_scalar_to_montgomery
%xdefine ec_scalar_to_montgomery_inv_vartime XCRYPTO_PREFIX %+ _ec_scalar_to_montgomery_inv_vartime
%xdefine ec_set_to_safe_point XCRYPTO_PREFIX %+ _ec_set_to_safe_point
%xdefine ec_simple_scalar_inv0_montgomery XCRYPTO_PREFIX %+ _ec_simple_scalar_inv0_montgomery
%xdefine ec_simple_scalar_to_montgomery_inv_vartime XCRYPTO_PREFIX %+ _ec_simple_scalar_to_montgomery_inv_vartime
%xdefine ecp_nistz256_avx2_select_w7 XCRYPTO_PREFIX %+ _ecp_nistz256_avx2_select_w7
%xdefine ecp_nistz256_mul_mont XCRYPTO_PREFIX %+ _ecp_nistz256_mul_mont
%xdefine ecp_nistz256_neg XCRYPTO_PREFIX %+ _ecp_nistz256_neg
%xdefine ecp_nistz256_ord_mul_mont XCRYPTO_PREFIX %+ _ecp_nistz256_ord_mul_mont
%xdefine ecp_nistz256_ord_sqr_mont XCRYPTO_PREFIX %+ _ecp_nistz256_ord_sqr_mont
%xdefine ecp_nistz256_point_add XCRYPTO_PREFIX %+ _ecp_nistz256_point_add
%xdefine ecp_nistz256_point_add_affine XCRYPTO_PREFIX %+ _ecp_nistz256_point_add_affine
%xdefine ecp_nistz256_point_double XCRYPTO_PREFIX %+ _ecp_nistz256_point_double
%xdefine ecp_nistz256_select_w5 XCRYPTO_PREFIX %+ _ecp_nistz256_select_w5
%xdefine ecp_nistz256_select_w7 XCRYPTO_PREFIX %+ _ecp_nistz256_select_w7
%xdefine ecp_nistz256_sqr_mont XCRYPTO_PREFIX %+ _ecp_nistz256_sqr_mont
%xdefine ed25519_asn1_meth XCRYPTO_PREFIX %+ _ed25519_asn1_meth
%xdefine ed25519_pkey_meth XCRYPTO_PREFIX %+ _ed25519_pkey_meth
%xdefine gcm_ghash_avx XCRYPTO_PREFIX %+ _gcm_ghash_avx
%xdefine gcm_ghash_clmul XCRYPTO_PREFIX %+ _gcm_ghash_clmul
%xdefine gcm_ghash_neon XCRYPTO_PREFIX %+ _gcm_ghash_neon
%xdefine gcm_ghash_nohw XCRYPTO_PREFIX %+ _gcm_ghash_nohw
%xdefine gcm_ghash_ssse3 XCRYPTO_PREFIX %+ _gcm_ghash_ssse3
%xdefine gcm_ghash_v8 XCRYPTO_PREFIX %+ _gcm_ghash_v8
%xdefine gcm_gmult_avx XCRYPTO_PREFIX %+ _gcm_gmult_avx
%xdefine gcm_gmult_clmul XCRYPTO_PREFIX %+ _gcm_gmult_clmul
%xdefine gcm_gmult_neon XCRYPTO_PREFIX %+ _gcm_gmult_neon
%xdefine gcm_gmult_nohw XCRYPTO_PREFIX %+ _gcm_gmult_nohw
%xdefine gcm_gmult_ssse3 XCRYPTO_PREFIX %+ _gcm_gmult_ssse3
%xdefine gcm_gmult_v8 XCRYPTO_PREFIX %+ _gcm_gmult_v8
%xdefine gcm_init_avx XCRYPTO_PREFIX %+ _gcm_init_avx
%xdefine gcm_init_clmul XCRYPTO_PREFIX %+ _gcm_init_clmul
%xdefine gcm_init_neon XCRYPTO_PREFIX %+ _gcm_init_neon
%xdefine gcm_init_nohw XCRYPTO_PREFIX %+ _gcm_init_nohw
%xdefine gcm_init_ssse3 XCRYPTO_PREFIX %+ _gcm_init_ssse3
%xdefine gcm_init_v8 XCRYPTO_PREFIX %+ _gcm_init_v8
%xdefine i2a_ACCESS_DESCRIPTION XCRYPTO_PREFIX %+ _i2a_ACCESS_DESCRIPTION
%xdefine i2a_ASN1_ENUMERATED XCRYPTO_PREFIX %+ _i2a_ASN1_ENUMERATED
%xdefine i2a_ASN1_INTEGER XCRYPTO_PREFIX %+ _i2a_ASN1_INTEGER
%xdefine i2a_ASN1_OBJECT XCRYPTO_PREFIX %+ _i2a_ASN1_OBJECT
%xdefine i2a_ASN1_STRING XCRYPTO_PREFIX %+ _i2a_ASN1_STRING
%xdefine i2c_ASN1_BIT_STRING XCRYPTO_PREFIX %+ _i2c_ASN1_BIT_STRING
%xdefine i2c_ASN1_INTEGER XCRYPTO_PREFIX %+ _i2c_ASN1_INTEGER
%xdefine i2d_ACCESS_DESCRIPTION XCRYPTO_PREFIX %+ _i2d_ACCESS_DESCRIPTION
%xdefine i2d_ASN1_BIT_STRING XCRYPTO_PREFIX %+ _i2d_ASN1_BIT_STRING
%xdefine i2d_ASN1_BMPSTRING XCRYPTO_PREFIX %+ _i2d_ASN1_BMPSTRING
%xdefine i2d_ASN1_BOOLEAN XCRYPTO_PREFIX %+ _i2d_ASN1_BOOLEAN
%xdefine i2d_ASN1_ENUMERATED XCRYPTO_PREFIX %+ _i2d_ASN1_ENUMERATED
%xdefine i2d_ASN1_GENERALIZEDTIME XCRYPTO_PREFIX %+ _i2d_ASN1_GENERALIZEDTIME
%xdefine i2d_ASN1_GENERALSTRING XCRYPTO_PREFIX %+ _i2d_ASN1_GENERALSTRING
%xdefine i2d_ASN1_IA5STRING XCRYPTO_PREFIX %+ _i2d_ASN1_IA5STRING
%xdefine i2d_ASN1_INTEGER XCRYPTO_PREFIX %+ _i2d_ASN1_INTEGER
%xdefine i2d_ASN1_NULL XCRYPTO_PREFIX %+ _i2d_ASN1_NULL
%xdefine i2d_ASN1_OBJECT XCRYPTO_PREFIX %+ _i2d_ASN1_OBJECT
%xdefine i2d_ASN1_OCTET_STRING XCRYPTO_PREFIX %+ _i2d_ASN1_OCTET_STRING
%xdefine i2d_ASN1_PRINTABLE XCRYPTO_PREFIX %+ _i2d_ASN1_PRINTABLE
%xdefine i2d_ASN1_PRINTABLESTRING XCRYPTO_PREFIX %+ _i2d_ASN1_PRINTABLESTRING
%xdefine i2d_ASN1_SEQUENCE_ANY XCRYPTO_PREFIX %+ _i2d_ASN1_SEQUENCE_ANY
%xdefine i2d_ASN1_SET_ANY XCRYPTO_PREFIX %+ _i2d_ASN1_SET_ANY
%xdefine i2d_ASN1_T61STRING XCRYPTO_PREFIX %+ _i2d_ASN1_T61STRING
%xdefine i2d_ASN1_TIME XCRYPTO_PREFIX %+ _i2d_ASN1_TIME
%xdefine i2d_ASN1_TYPE XCRYPTO_PREFIX %+ _i2d_ASN1_TYPE
%xdefine i2d_ASN1_UNIVERSALSTRING XCRYPTO_PREFIX %+ _i2d_ASN1_UNIVERSALSTRING
%xdefine i2d_ASN1_UTCTIME XCRYPTO_PREFIX %+ _i2d_ASN1_UTCTIME
%xdefine i2d_ASN1_UTF8STRING XCRYPTO_PREFIX %+ _i2d_ASN1_UTF8STRING
%xdefine i2d_ASN1_VISIBLESTRING XCRYPTO_PREFIX %+ _i2d_ASN1_VISIBLESTRING
%xdefine i2d_AUTHORITY_INFO_ACCESS XCRYPTO_PREFIX %+ _i2d_AUTHORITY_INFO_ACCESS
%xdefine i2d_AUTHORITY_KEYID XCRYPTO_PREFIX %+ _i2d_AUTHORITY_KEYID
%xdefine i2d_BASIC_CONSTRAINTS XCRYPTO_PREFIX %+ _i2d_BASIC_CONSTRAINTS
%xdefine i2d_CERTIFICATEPOLICIES XCRYPTO_PREFIX %+ _i2d_CERTIFICATEPOLICIES
%xdefine i2d_CRL_DIST_POINTS XCRYPTO_PREFIX %+ _i2d_CRL_DIST_POINTS
%xdefine i2d_DHparams XCRYPTO_PREFIX %+ _i2d_DHparams
%xdefine i2d_DHparams_bio XCRYPTO_PREFIX %+ _i2d_DHparams_bio
%xdefine i2d_DIRECTORYSTRING XCRYPTO_PREFIX %+ _i2d_DIRECTORYSTRING
%xdefine i2d_DISPLAYTEXT XCRYPTO_PREFIX %+ _i2d_DISPLAYTEXT
%xdefine i2d_DIST_POINT XCRYPTO_PREFIX %+ _i2d_DIST_POINT
%xdefine i2d_DIST_POINT_NAME XCRYPTO_PREFIX %+ _i2d_DIST_POINT_NAME
%xdefine i2d_DSAPrivateKey XCRYPTO_PREFIX %+ _i2d_DSAPrivateKey
%xdefine i2d_DSAPrivateKey_bio XCRYPTO_PREFIX %+ _i2d_DSAPrivateKey_bio
%xdefine i2d_DSAPrivateKey_fp XCRYPTO_PREFIX %+ _i2d_DSAPrivateKey_fp
%xdefine i2d_DSAPublicKey XCRYPTO_PREFIX %+ _i2d_DSAPublicKey
%xdefine i2d_DSA_PUBKEY XCRYPTO_PREFIX %+ _i2d_DSA_PUBKEY
%xdefine i2d_DSA_PUBKEY_bio XCRYPTO_PREFIX %+ _i2d_DSA_PUBKEY_bio
%xdefine i2d_DSA_PUBKEY_fp XCRYPTO_PREFIX %+ _i2d_DSA_PUBKEY_fp
%xdefine i2d_DSA_SIG XCRYPTO_PREFIX %+ _i2d_DSA_SIG
%xdefine i2d_DSAparams XCRYPTO_PREFIX %+ _i2d_DSAparams
%xdefine i2d_ECDSA_SIG XCRYPTO_PREFIX %+ _i2d_ECDSA_SIG
%xdefine i2d_ECParameters XCRYPTO_PREFIX %+ _i2d_ECParameters
%xdefine i2d_ECPrivateKey XCRYPTO_PREFIX %+ _i2d_ECPrivateKey
%xdefine i2d_ECPrivateKey_bio XCRYPTO_PREFIX %+ _i2d_ECPrivateKey_bio
%xdefine i2d_ECPrivateKey_fp XCRYPTO_PREFIX %+ _i2d_ECPrivateKey_fp
%xdefine i2d_EC_PUBKEY XCRYPTO_PREFIX %+ _i2d_EC_PUBKEY
%xdefine i2d_EC_PUBKEY_bio XCRYPTO_PREFIX %+ _i2d_EC_PUBKEY_bio
%xdefine i2d_EC_PUBKEY_fp XCRYPTO_PREFIX %+ _i2d_EC_PUBKEY_fp
%xdefine i2d_EDIPARTYNAME XCRYPTO_PREFIX %+ _i2d_EDIPARTYNAME
%xdefine i2d_EXTENDED_KEY_USAGE XCRYPTO_PREFIX %+ _i2d_EXTENDED_KEY_USAGE
%xdefine i2d_GENERAL_NAME XCRYPTO_PREFIX %+ _i2d_GENERAL_NAME
%xdefine i2d_GENERAL_NAMES XCRYPTO_PREFIX %+ _i2d_GENERAL_NAMES
%xdefine i2d_ISSUING_DIST_POINT XCRYPTO_PREFIX %+ _i2d_ISSUING_DIST_POINT
%xdefine i2d_NETSCAPE_SPKAC XCRYPTO_PREFIX %+ _i2d_NETSCAPE_SPKAC
%xdefine i2d_NETSCAPE_SPKI XCRYPTO_PREFIX %+ _i2d_NETSCAPE_SPKI
%xdefine i2d_NOTICEREF XCRYPTO_PREFIX %+ _i2d_NOTICEREF
%xdefine i2d_OTHERNAME XCRYPTO_PREFIX %+ _i2d_OTHERNAME
%xdefine i2d_PKCS12 XCRYPTO_PREFIX %+ _i2d_PKCS12
%xdefine i2d_PKCS12_bio XCRYPTO_PREFIX %+ _i2d_PKCS12_bio
%xdefine i2d_PKCS12_fp XCRYPTO_PREFIX %+ _i2d_PKCS12_fp
%xdefine i2d_PKCS7 XCRYPTO_PREFIX %+ _i2d_PKCS7
%xdefine i2d_PKCS7_bio XCRYPTO_PREFIX %+ _i2d_PKCS7_bio
%xdefine i2d_PKCS8PrivateKeyInfo_bio XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKeyInfo_bio
%xdefine i2d_PKCS8PrivateKeyInfo_fp XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKeyInfo_fp
%xdefine i2d_PKCS8PrivateKey_bio XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_bio
%xdefine i2d_PKCS8PrivateKey_fp XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_fp
%xdefine i2d_PKCS8PrivateKey_nid_bio XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_nid_bio
%xdefine i2d_PKCS8PrivateKey_nid_fp XCRYPTO_PREFIX %+ _i2d_PKCS8PrivateKey_nid_fp
%xdefine i2d_PKCS8_PRIV_KEY_INFO XCRYPTO_PREFIX %+ _i2d_PKCS8_PRIV_KEY_INFO
%xdefine i2d_PKCS8_PRIV_KEY_INFO_bio XCRYPTO_PREFIX %+ _i2d_PKCS8_PRIV_KEY_INFO_bio
%xdefine i2d_PKCS8_PRIV_KEY_INFO_fp XCRYPTO_PREFIX %+ _i2d_PKCS8_PRIV_KEY_INFO_fp
%xdefine i2d_PKCS8_bio XCRYPTO_PREFIX %+ _i2d_PKCS8_bio
%xdefine i2d_PKCS8_fp XCRYPTO_PREFIX %+ _i2d_PKCS8_fp
%xdefine i2d_PKEY_USAGE_PERIOD XCRYPTO_PREFIX %+ _i2d_PKEY_USAGE_PERIOD
%xdefine i2d_POLICYINFO XCRYPTO_PREFIX %+ _i2d_POLICYINFO
%xdefine i2d_POLICYQUALINFO XCRYPTO_PREFIX %+ _i2d_POLICYQUALINFO
%xdefine i2d_PROXY_CERT_INFO_EXTENSION XCRYPTO_PREFIX %+ _i2d_PROXY_CERT_INFO_EXTENSION
%xdefine i2d_PROXY_POLICY XCRYPTO_PREFIX %+ _i2d_PROXY_POLICY
%xdefine i2d_PUBKEY XCRYPTO_PREFIX %+ _i2d_PUBKEY
%xdefine i2d_PUBKEY_bio XCRYPTO_PREFIX %+ _i2d_PUBKEY_bio
%xdefine i2d_PUBKEY_fp XCRYPTO_PREFIX %+ _i2d_PUBKEY_fp
%xdefine i2d_PrivateKey XCRYPTO_PREFIX %+ _i2d_PrivateKey
%xdefine i2d_PrivateKey_bio XCRYPTO_PREFIX %+ _i2d_PrivateKey_bio
%xdefine i2d_PrivateKey_fp XCRYPTO_PREFIX %+ _i2d_PrivateKey_fp
%xdefine i2d_PublicKey XCRYPTO_PREFIX %+ _i2d_PublicKey
%xdefine i2d_RSAPrivateKey XCRYPTO_PREFIX %+ _i2d_RSAPrivateKey
%xdefine i2d_RSAPrivateKey_bio XCRYPTO_PREFIX %+ _i2d_RSAPrivateKey_bio
%xdefine i2d_RSAPrivateKey_fp XCRYPTO_PREFIX %+ _i2d_RSAPrivateKey_fp
%xdefine i2d_RSAPublicKey XCRYPTO_PREFIX %+ _i2d_RSAPublicKey
%xdefine i2d_RSAPublicKey_bio XCRYPTO_PREFIX %+ _i2d_RSAPublicKey_bio
%xdefine i2d_RSAPublicKey_fp XCRYPTO_PREFIX %+ _i2d_RSAPublicKey_fp
%xdefine i2d_RSA_PSS_PARAMS XCRYPTO_PREFIX %+ _i2d_RSA_PSS_PARAMS
%xdefine i2d_RSA_PUBKEY XCRYPTO_PREFIX %+ _i2d_RSA_PUBKEY
%xdefine i2d_RSA_PUBKEY_bio XCRYPTO_PREFIX %+ _i2d_RSA_PUBKEY_bio
%xdefine i2d_RSA_PUBKEY_fp XCRYPTO_PREFIX %+ _i2d_RSA_PUBKEY_fp
%xdefine i2d_SSL_SESSION XCRYPTO_PREFIX %+ _i2d_SSL_SESSION
%xdefine i2d_SSL_SESSION_bio XCRYPTO_PREFIX %+ _i2d_SSL_SESSION_bio
%xdefine i2d_SXNET XCRYPTO_PREFIX %+ _i2d_SXNET
%xdefine i2d_SXNETID XCRYPTO_PREFIX %+ _i2d_SXNETID
%xdefine i2d_USERNOTICE XCRYPTO_PREFIX %+ _i2d_USERNOTICE
%xdefine i2d_X509 XCRYPTO_PREFIX %+ _i2d_X509
%xdefine i2d_X509_ALGOR XCRYPTO_PREFIX %+ _i2d_X509_ALGOR
%xdefine i2d_X509_ALGORS XCRYPTO_PREFIX %+ _i2d_X509_ALGORS
%xdefine i2d_X509_ATTRIBUTE XCRYPTO_PREFIX %+ _i2d_X509_ATTRIBUTE
%xdefine i2d_X509_AUX XCRYPTO_PREFIX %+ _i2d_X509_AUX
%xdefine i2d_X509_CERT_AUX XCRYPTO_PREFIX %+ _i2d_X509_CERT_AUX
%xdefine i2d_X509_CINF XCRYPTO_PREFIX %+ _i2d_X509_CINF
%xdefine i2d_X509_CRL XCRYPTO_PREFIX %+ _i2d_X509_CRL
%xdefine i2d_X509_CRL_INFO XCRYPTO_PREFIX %+ _i2d_X509_CRL_INFO
%xdefine i2d_X509_CRL_bio XCRYPTO_PREFIX %+ _i2d_X509_CRL_bio
%xdefine i2d_X509_CRL_fp XCRYPTO_PREFIX %+ _i2d_X509_CRL_fp
%xdefine i2d_X509_EXTENSION XCRYPTO_PREFIX %+ _i2d_X509_EXTENSION
%xdefine i2d_X509_EXTENSIONS XCRYPTO_PREFIX %+ _i2d_X509_EXTENSIONS
%xdefine i2d_X509_NAME XCRYPTO_PREFIX %+ _i2d_X509_NAME
%xdefine i2d_X509_NAME_ENTRY XCRYPTO_PREFIX %+ _i2d_X509_NAME_ENTRY
%xdefine i2d_X509_PUBKEY XCRYPTO_PREFIX %+ _i2d_X509_PUBKEY
%xdefine i2d_X509_REQ XCRYPTO_PREFIX %+ _i2d_X509_REQ
%xdefine i2d_X509_REQ_INFO XCRYPTO_PREFIX %+ _i2d_X509_REQ_INFO
%xdefine i2d_X509_REQ_bio XCRYPTO_PREFIX %+ _i2d_X509_REQ_bio
%xdefine i2d_X509_REQ_fp XCRYPTO_PREFIX %+ _i2d_X509_REQ_fp
%xdefine i2d_X509_REVOKED XCRYPTO_PREFIX %+ _i2d_X509_REVOKED
%xdefine i2d_X509_SIG XCRYPTO_PREFIX %+ _i2d_X509_SIG
%xdefine i2d_X509_VAL XCRYPTO_PREFIX %+ _i2d_X509_VAL
%xdefine i2d_X509_bio XCRYPTO_PREFIX %+ _i2d_X509_bio
%xdefine i2d_X509_fp XCRYPTO_PREFIX %+ _i2d_X509_fp
%xdefine i2d_re_X509_CRL_tbs XCRYPTO_PREFIX %+ _i2d_re_X509_CRL_tbs
%xdefine i2d_re_X509_REQ_tbs XCRYPTO_PREFIX %+ _i2d_re_X509_REQ_tbs
%xdefine i2d_re_X509_tbs XCRYPTO_PREFIX %+ _i2d_re_X509_tbs
%xdefine i2o_ECPublicKey XCRYPTO_PREFIX %+ _i2o_ECPublicKey
%xdefine i2s_ASN1_ENUMERATED XCRYPTO_PREFIX %+ _i2s_ASN1_ENUMERATED
%xdefine i2s_ASN1_ENUMERATED_TABLE XCRYPTO_PREFIX %+ _i2s_ASN1_ENUMERATED_TABLE
%xdefine i2s_ASN1_INTEGER XCRYPTO_PREFIX %+ _i2s_ASN1_INTEGER
%xdefine i2s_ASN1_OCTET_STRING XCRYPTO_PREFIX %+ _i2s_ASN1_OCTET_STRING
%xdefine i2t_ASN1_OBJECT XCRYPTO_PREFIX %+ _i2t_ASN1_OBJECT
%xdefine i2v_ASN1_BIT_STRING XCRYPTO_PREFIX %+ _i2v_ASN1_BIT_STRING
%xdefine i2v_GENERAL_NAME XCRYPTO_PREFIX %+ _i2v_GENERAL_NAME
%xdefine i2v_GENERAL_NAMES XCRYPTO_PREFIX %+ _i2v_GENERAL_NAMES
%xdefine kBoringSSLRSASqrtTwo XCRYPTO_PREFIX %+ _kBoringSSLRSASqrtTwo
%xdefine kBoringSSLRSASqrtTwoLen XCRYPTO_PREFIX %+ _kBoringSSLRSASqrtTwoLen
%xdefine kOpenSSLReasonStringData XCRYPTO_PREFIX %+ _kOpenSSLReasonStringData
%xdefine kOpenSSLReasonValues XCRYPTO_PREFIX %+ _kOpenSSLReasonValues
%xdefine kOpenSSLReasonValuesLen XCRYPTO_PREFIX %+ _kOpenSSLReasonValuesLen
%xdefine level_add_node XCRYPTO_PREFIX %+ _level_add_node
%xdefine level_find_node XCRYPTO_PREFIX %+ _level_find_node
%xdefine lh_delete XCRYPTO_PREFIX %+ _lh_delete
%xdefine lh_doall_arg XCRYPTO_PREFIX %+ _lh_doall_arg
%xdefine lh_free XCRYPTO_PREFIX %+ _lh_free
%xdefine lh_insert XCRYPTO_PREFIX %+ _lh_insert
%xdefine lh_new XCRYPTO_PREFIX %+ _lh_new
%xdefine lh_num_items XCRYPTO_PREFIX %+ _lh_num_items
%xdefine lh_retrieve XCRYPTO_PREFIX %+ _lh_retrieve
%xdefine lh_retrieve_key XCRYPTO_PREFIX %+ _lh_retrieve_key
%xdefine lh_strhash XCRYPTO_PREFIX %+ _lh_strhash
%xdefine md4_block_data_order XCRYPTO_PREFIX %+ _md4_block_data_order
%xdefine md5_block_asm_data_order XCRYPTO_PREFIX %+ _md5_block_asm_data_order
%xdefine o2i_ECPublicKey XCRYPTO_PREFIX %+ _o2i_ECPublicKey
%xdefine pkcs12_iterations_acceptable XCRYPTO_PREFIX %+ _pkcs12_iterations_acceptable
%xdefine pkcs12_key_gen XCRYPTO_PREFIX %+ _pkcs12_key_gen
%xdefine pkcs12_pbe_encrypt_init XCRYPTO_PREFIX %+ _pkcs12_pbe_encrypt_init
%xdefine pkcs7_bundle XCRYPTO_PREFIX %+ _pkcs7_bundle
%xdefine pkcs7_parse_header XCRYPTO_PREFIX %+ _pkcs7_parse_header
%xdefine pkcs8_pbe_decrypt XCRYPTO_PREFIX %+ _pkcs8_pbe_decrypt
%xdefine pmbtoken_exp0_blind XCRYPTO_PREFIX %+ _pmbtoken_exp0_blind
%xdefine pmbtoken_exp0_client_key_from_bytes XCRYPTO_PREFIX %+ _pmbtoken_exp0_client_key_from_bytes
%xdefine pmbtoken_exp0_generate_key XCRYPTO_PREFIX %+ _pmbtoken_exp0_generate_key
%xdefine pmbtoken_exp0_issuer_key_from_bytes XCRYPTO_PREFIX %+ _pmbtoken_exp0_issuer_key_from_bytes
%xdefine pmbtoken_exp0_read XCRYPTO_PREFIX %+ _pmbtoken_exp0_read
%xdefine pmbtoken_exp0_sign XCRYPTO_PREFIX %+ _pmbtoken_exp0_sign
%xdefine pmbtoken_exp0_unblind XCRYPTO_PREFIX %+ _pmbtoken_exp0_unblind
%xdefine pmbtoken_exp1_blind XCRYPTO_PREFIX %+ _pmbtoken_exp1_blind
%xdefine pmbtoken_exp1_client_key_from_bytes XCRYPTO_PREFIX %+ _pmbtoken_exp1_client_key_from_bytes
%xdefine pmbtoken_exp1_generate_key XCRYPTO_PREFIX %+ _pmbtoken_exp1_generate_key
%xdefine pmbtoken_exp1_get_h_for_testing XCRYPTO_PREFIX %+ _pmbtoken_exp1_get_h_for_testing
%xdefine pmbtoken_exp1_issuer_key_from_bytes XCRYPTO_PREFIX %+ _pmbtoken_exp1_issuer_key_from_bytes
%xdefine pmbtoken_exp1_read XCRYPTO_PREFIX %+ _pmbtoken_exp1_read
%xdefine pmbtoken_exp1_sign XCRYPTO_PREFIX %+ _pmbtoken_exp1_sign
%xdefine pmbtoken_exp1_unblind XCRYPTO_PREFIX %+ _pmbtoken_exp1_unblind
%xdefine policy_cache_find_data XCRYPTO_PREFIX %+ _policy_cache_find_data
%xdefine policy_cache_free XCRYPTO_PREFIX %+ _policy_cache_free
%xdefine policy_cache_set XCRYPTO_PREFIX %+ _policy_cache_set
%xdefine policy_cache_set_mapping XCRYPTO_PREFIX %+ _policy_cache_set_mapping
%xdefine policy_data_free XCRYPTO_PREFIX %+ _policy_data_free
%xdefine policy_data_new XCRYPTO_PREFIX %+ _policy_data_new
%xdefine policy_node_cmp_new XCRYPTO_PREFIX %+ _policy_node_cmp_new
%xdefine policy_node_free XCRYPTO_PREFIX %+ _policy_node_free
%xdefine policy_node_match XCRYPTO_PREFIX %+ _policy_node_match
%xdefine poly_Rq_mul XCRYPTO_PREFIX %+ _poly_Rq_mul
%xdefine rand_fork_unsafe_buffering_enabled XCRYPTO_PREFIX %+ _rand_fork_unsafe_buffering_enabled
%xdefine rsa_asn1_meth XCRYPTO_PREFIX %+ _rsa_asn1_meth
%xdefine rsa_default_decrypt XCRYPTO_PREFIX %+ _rsa_default_decrypt
%xdefine rsa_default_private_transform XCRYPTO_PREFIX %+ _rsa_default_private_transform
%xdefine rsa_default_sign_raw XCRYPTO_PREFIX %+ _rsa_default_sign_raw
%xdefine rsa_default_size XCRYPTO_PREFIX %+ _rsa_default_size
%xdefine rsa_pkey_meth XCRYPTO_PREFIX %+ _rsa_pkey_meth
%xdefine rsaz_1024_gather5_avx2 XCRYPTO_PREFIX %+ _rsaz_1024_gather5_avx2
%xdefine rsaz_1024_mul_avx2 XCRYPTO_PREFIX %+ _rsaz_1024_mul_avx2
%xdefine rsaz_1024_norm2red_avx2 XCRYPTO_PREFIX %+ _rsaz_1024_norm2red_avx2
%xdefine rsaz_1024_red2norm_avx2 XCRYPTO_PREFIX %+ _rsaz_1024_red2norm_avx2
%xdefine rsaz_1024_scatter5_avx2 XCRYPTO_PREFIX %+ _rsaz_1024_scatter5_avx2
%xdefine rsaz_1024_sqr_avx2 XCRYPTO_PREFIX %+ _rsaz_1024_sqr_avx2
%xdefine s2i_ASN1_INTEGER XCRYPTO_PREFIX %+ _s2i_ASN1_INTEGER
%xdefine s2i_ASN1_OCTET_STRING XCRYPTO_PREFIX %+ _s2i_ASN1_OCTET_STRING
%xdefine sha1_block_data_order XCRYPTO_PREFIX %+ _sha1_block_data_order
%xdefine sha256_block_data_order XCRYPTO_PREFIX %+ _sha256_block_data_order
%xdefine sha512_block_data_order XCRYPTO_PREFIX %+ _sha512_block_data_order
%xdefine sk_CRYPTO_BUFFER_call_copy_func XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_call_copy_func
%xdefine sk_CRYPTO_BUFFER_call_free_func XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_call_free_func
%xdefine sk_CRYPTO_BUFFER_deep_copy XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_deep_copy
%xdefine sk_CRYPTO_BUFFER_new_null XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_new_null
%xdefine sk_CRYPTO_BUFFER_num XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_num
%xdefine sk_CRYPTO_BUFFER_push XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_push
%xdefine sk_CRYPTO_BUFFER_set XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_set
%xdefine sk_CRYPTO_BUFFER_value XCRYPTO_PREFIX %+ _sk_CRYPTO_BUFFER_value
%xdefine sk_SRTP_PROTECTION_PROFILE_new_null XCRYPTO_PREFIX %+ _sk_SRTP_PROTECTION_PROFILE_new_null
%xdefine sk_SRTP_PROTECTION_PROFILE_num XCRYPTO_PREFIX %+ _sk_SRTP_PROTECTION_PROFILE_num
%xdefine sk_SRTP_PROTECTION_PROFILE_push XCRYPTO_PREFIX %+ _sk_SRTP_PROTECTION_PROFILE_push
%xdefine sk_SSL_CIPHER_call_cmp_func XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_call_cmp_func
%xdefine sk_SSL_CIPHER_delete XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_delete
%xdefine sk_SSL_CIPHER_dup XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_dup
%xdefine sk_SSL_CIPHER_find XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_find
%xdefine sk_SSL_CIPHER_new_null XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_new_null
%xdefine sk_SSL_CIPHER_num XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_num
%xdefine sk_SSL_CIPHER_push XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_push
%xdefine sk_SSL_CIPHER_value XCRYPTO_PREFIX %+ _sk_SSL_CIPHER_value
%xdefine sk_X509_NAME_call_cmp_func XCRYPTO_PREFIX %+ _sk_X509_NAME_call_cmp_func
%xdefine sk_X509_NAME_call_copy_func XCRYPTO_PREFIX %+ _sk_X509_NAME_call_copy_func
%xdefine sk_X509_NAME_call_free_func XCRYPTO_PREFIX %+ _sk_X509_NAME_call_free_func
%xdefine sk_X509_NAME_deep_copy XCRYPTO_PREFIX %+ _sk_X509_NAME_deep_copy
%xdefine sk_X509_NAME_find XCRYPTO_PREFIX %+ _sk_X509_NAME_find
%xdefine sk_X509_NAME_free XCRYPTO_PREFIX %+ _sk_X509_NAME_free
%xdefine sk_X509_NAME_new XCRYPTO_PREFIX %+ _sk_X509_NAME_new
%xdefine sk_X509_NAME_new_null XCRYPTO_PREFIX %+ _sk_X509_NAME_new_null
%xdefine sk_X509_NAME_pop_free XCRYPTO_PREFIX %+ _sk_X509_NAME_pop_free
%xdefine sk_X509_NAME_push XCRYPTO_PREFIX %+ _sk_X509_NAME_push
%xdefine sk_X509_NAME_set_cmp_func XCRYPTO_PREFIX %+ _sk_X509_NAME_set_cmp_func
%xdefine sk_X509_NAME_sort XCRYPTO_PREFIX %+ _sk_X509_NAME_sort
%xdefine sk_X509_call_free_func XCRYPTO_PREFIX %+ _sk_X509_call_free_func
%xdefine sk_X509_new_null XCRYPTO_PREFIX %+ _sk_X509_new_null
%xdefine sk_X509_num XCRYPTO_PREFIX %+ _sk_X509_num
%xdefine sk_X509_pop_free XCRYPTO_PREFIX %+ _sk_X509_pop_free
%xdefine sk_X509_shift XCRYPTO_PREFIX %+ _sk_X509_shift
%xdefine sk_X509_value XCRYPTO_PREFIX %+ _sk_X509_value
%xdefine sk_deep_copy XCRYPTO_PREFIX %+ _sk_deep_copy
%xdefine sk_delete XCRYPTO_PREFIX %+ _sk_delete
%xdefine sk_delete_ptr XCRYPTO_PREFIX %+ _sk_delete_ptr
%xdefine sk_dup XCRYPTO_PREFIX %+ _sk_dup
%xdefine sk_find XCRYPTO_PREFIX %+ _sk_find
%xdefine sk_free XCRYPTO_PREFIX %+ _sk_free
%xdefine sk_insert XCRYPTO_PREFIX %+ _sk_insert
%xdefine sk_is_sorted XCRYPTO_PREFIX %+ _sk_is_sorted
%xdefine sk_new XCRYPTO_PREFIX %+ _sk_new
%xdefine sk_new_null XCRYPTO_PREFIX %+ _sk_new_null
%xdefine sk_num XCRYPTO_PREFIX %+ _sk_num
%xdefine sk_pop XCRYPTO_PREFIX %+ _sk_pop
%xdefine sk_pop_free XCRYPTO_PREFIX %+ _sk_pop_free
%xdefine sk_pop_free_ex XCRYPTO_PREFIX %+ _sk_pop_free_ex
%xdefine sk_push XCRYPTO_PREFIX %+ _sk_push
%xdefine sk_set XCRYPTO_PREFIX %+ _sk_set
%xdefine sk_set_cmp_func XCRYPTO_PREFIX %+ _sk_set_cmp_func
%xdefine sk_shift XCRYPTO_PREFIX %+ _sk_shift
%xdefine sk_sort XCRYPTO_PREFIX %+ _sk_sort
%xdefine sk_value XCRYPTO_PREFIX %+ _sk_value
%xdefine sk_zero XCRYPTO_PREFIX %+ _sk_zero
%xdefine tree_find_sk XCRYPTO_PREFIX %+ _tree_find_sk
%xdefine v2i_ASN1_BIT_STRING XCRYPTO_PREFIX %+ _v2i_ASN1_BIT_STRING
%xdefine v2i_GENERAL_NAME XCRYPTO_PREFIX %+ _v2i_GENERAL_NAME
%xdefine v2i_GENERAL_NAMES XCRYPTO_PREFIX %+ _v2i_GENERAL_NAMES
%xdefine v2i_GENERAL_NAME_ex XCRYPTO_PREFIX %+ _v2i_GENERAL_NAME_ex
%xdefine v3_akey_id XCRYPTO_PREFIX %+ _v3_akey_id
%xdefine v3_alt XCRYPTO_PREFIX %+ _v3_alt
%xdefine v3_bcons XCRYPTO_PREFIX %+ _v3_bcons
%xdefine v3_cpols XCRYPTO_PREFIX %+ _v3_cpols
%xdefine v3_crl_invdate XCRYPTO_PREFIX %+ _v3_crl_invdate
%xdefine v3_crl_num XCRYPTO_PREFIX %+ _v3_crl_num
%xdefine v3_crl_reason XCRYPTO_PREFIX %+ _v3_crl_reason
%xdefine v3_crld XCRYPTO_PREFIX %+ _v3_crld
%xdefine v3_delta_crl XCRYPTO_PREFIX %+ _v3_delta_crl
%xdefine v3_ext_ku XCRYPTO_PREFIX %+ _v3_ext_ku
%xdefine v3_freshest_crl XCRYPTO_PREFIX %+ _v3_freshest_crl
%xdefine v3_idp XCRYPTO_PREFIX %+ _v3_idp
%xdefine v3_info XCRYPTO_PREFIX %+ _v3_info
%xdefine v3_inhibit_anyp XCRYPTO_PREFIX %+ _v3_inhibit_anyp
%xdefine v3_key_usage XCRYPTO_PREFIX %+ _v3_key_usage
%xdefine v3_name_constraints XCRYPTO_PREFIX %+ _v3_name_constraints
%xdefine v3_ns_ia5_list XCRYPTO_PREFIX %+ _v3_ns_ia5_list
%xdefine v3_nscert XCRYPTO_PREFIX %+ _v3_nscert
%xdefine v3_ocsp_accresp XCRYPTO_PREFIX %+ _v3_ocsp_accresp
%xdefine v3_ocsp_nocheck XCRYPTO_PREFIX %+ _v3_ocsp_nocheck
%xdefine v3_pci XCRYPTO_PREFIX %+ _v3_pci
%xdefine v3_pkey_usage_period XCRYPTO_PREFIX %+ _v3_pkey_usage_period
%xdefine v3_policy_constraints XCRYPTO_PREFIX %+ _v3_policy_constraints
%xdefine v3_policy_mappings XCRYPTO_PREFIX %+ _v3_policy_mappings
%xdefine v3_sinfo XCRYPTO_PREFIX %+ _v3_sinfo
%xdefine v3_skey_id XCRYPTO_PREFIX %+ _v3_skey_id
%xdefine v3_sxnet XCRYPTO_PREFIX %+ _v3_sxnet
%xdefine vpaes_cbc_encrypt XCRYPTO_PREFIX %+ _vpaes_cbc_encrypt
%xdefine vpaes_ctr32_encrypt_blocks XCRYPTO_PREFIX %+ _vpaes_ctr32_encrypt_blocks
%xdefine vpaes_decrypt XCRYPTO_PREFIX %+ _vpaes_decrypt
%xdefine vpaes_encrypt XCRYPTO_PREFIX %+ _vpaes_encrypt
%xdefine vpaes_set_decrypt_key XCRYPTO_PREFIX %+ _vpaes_set_decrypt_key
%xdefine vpaes_set_encrypt_key XCRYPTO_PREFIX %+ _vpaes_set_encrypt_key
%xdefine x25519_asn1_meth XCRYPTO_PREFIX %+ _x25519_asn1_meth
%xdefine x25519_ge_add XCRYPTO_PREFIX %+ _x25519_ge_add
%xdefine x25519_ge_frombytes_vartime XCRYPTO_PREFIX %+ _x25519_ge_frombytes_vartime
%xdefine x25519_ge_p1p1_to_p2 XCRYPTO_PREFIX %+ _x25519_ge_p1p1_to_p2
%xdefine x25519_ge_p1p1_to_p3 XCRYPTO_PREFIX %+ _x25519_ge_p1p1_to_p3
%xdefine x25519_ge_p3_to_cached XCRYPTO_PREFIX %+ _x25519_ge_p3_to_cached
%xdefine x25519_ge_scalarmult XCRYPTO_PREFIX %+ _x25519_ge_scalarmult
%xdefine x25519_ge_scalarmult_base XCRYPTO_PREFIX %+ _x25519_ge_scalarmult_base
%xdefine x25519_ge_scalarmult_small_precomp XCRYPTO_PREFIX %+ _x25519_ge_scalarmult_small_precomp
%xdefine x25519_ge_sub XCRYPTO_PREFIX %+ _x25519_ge_sub
%xdefine x25519_ge_tobytes XCRYPTO_PREFIX %+ _x25519_ge_tobytes
%xdefine x25519_pkey_meth XCRYPTO_PREFIX %+ _x25519_pkey_meth
%xdefine x25519_sc_reduce XCRYPTO_PREFIX %+ _x25519_sc_reduce
%xdefine x509_digest_sign_algorithm XCRYPTO_PREFIX %+ _x509_digest_sign_algorithm
%xdefine x509_digest_verify_init XCRYPTO_PREFIX %+ _x509_digest_verify_init
%xdefine x509_print_rsa_pss_params XCRYPTO_PREFIX %+ _x509_print_rsa_pss_params
%xdefine x509_rsa_ctx_to_pss XCRYPTO_PREFIX %+ _x509_rsa_ctx_to_pss
%xdefine x509_rsa_pss_to_ctx XCRYPTO_PREFIX %+ _x509_rsa_pss_to_ctx
%xdefine x509v3_bytes_to_hex XCRYPTO_PREFIX %+ _x509v3_bytes_to_hex
%xdefine x509v3_hex_to_bytes XCRYPTO_PREFIX %+ _x509v3_hex_to_bytes
%xdefine x509v3_looks_like_dns_name XCRYPTO_PREFIX %+ _x509v3_looks_like_dns_name
%xdefine x509v3_name_cmp XCRYPTO_PREFIX %+ _x509v3_name_cmp
%endif
