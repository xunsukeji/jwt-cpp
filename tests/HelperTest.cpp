#include "jwt-cpp/jwt.h"
#include <gtest/gtest.h>

namespace {
	extern std::string google_cert;
	extern std::string google_cert_base64_der;
	extern std::string google_public_key;
} // namespace

TEST(HelperTest, Cert2Pubkey) {
	auto key = jwt::helper::extract_pubkey_from_cert(google_cert);
	ASSERT_EQ(google_public_key, key);
}

TEST(HelperTest, Base64DER2PemCert) {
	auto cert_pem = jwt::helper::convert_base64_der_to_pem(google_cert_base64_der);
	ASSERT_EQ(google_cert, cert_pem);
}

TEST(HelperTest, ErrorCodeMessages) {
	ASSERT_EQ(std::error_code(jwt::error::rsa_error::ok).message(), "no error");
	ASSERT_EQ(std::error_code(static_cast<jwt::error::rsa_error>(-1)).message(), "unknown RSA error");
	ASSERT_EQ(std::error_code(jwt::error::rsa_error::ok).category().name(), std::string("rsa_error"));

	ASSERT_EQ(std::error_code(jwt::error::ecdsa_error::ok).message(), "no error");
	ASSERT_EQ(std::error_code(static_cast<jwt::error::ecdsa_error>(-1)).message(), "unknown ECDSA error");
	ASSERT_EQ(std::error_code(jwt::error::ecdsa_error::ok).category().name(), std::string("ecdsa_error"));

	ASSERT_EQ(std::error_code(jwt::error::signature_verification_error::ok).message(), "no error");
	ASSERT_EQ(std::error_code(static_cast<jwt::error::signature_verification_error>(-1)).message(),
			  "unknown signature verification error");
	ASSERT_EQ(std::error_code(jwt::error::signature_verification_error::ok).category().name(),
			  std::string("signature_verification_error"));

	ASSERT_EQ(std::error_code(jwt::error::signature_generation_error::ok).message(), "no error");
	ASSERT_EQ(std::error_code(static_cast<jwt::error::signature_generation_error>(-1)).message(),
			  "unknown signature generation error");
	ASSERT_EQ(std::error_code(jwt::error::signature_generation_error::ok).category().name(),
			  std::string("signature_generation_error"));

	ASSERT_EQ(std::error_code(jwt::error::token_verification_error::ok).message(), "no error");
	ASSERT_EQ(std::error_code(static_cast<jwt::error::token_verification_error>(-1)).message(),
			  "unknown token verification error");
	ASSERT_EQ(std::error_code(jwt::error::token_verification_error::ok).category().name(),
			  std::string("token_verification_error"));

	int i = 10;
	for (i = 10; i < 19; i++) {
		ASSERT_NE(std::error_code(static_cast<jwt::error::rsa_error>(i)).message(),
				  std::error_code(static_cast<jwt::error::rsa_error>(-1)).message());
	}
	ASSERT_EQ(std::error_code(static_cast<jwt::error::rsa_error>(i)).message(),
			  std::error_code(static_cast<jwt::error::rsa_error>(-1)).message());

	for (i = 10; i < 16; i++) {
		ASSERT_NE(std::error_code(static_cast<jwt::error::ecdsa_error>(i)).message(),
				  std::error_code(static_cast<jwt::error::ecdsa_error>(-1)).message());
	}
	ASSERT_EQ(std::error_code(static_cast<jwt::error::ecdsa_error>(i)).message(),
			  std::error_code(static_cast<jwt::error::ecdsa_error>(-1)).message());

	for (i = 10; i < 16; i++) {
		ASSERT_NE(std::error_code(static_cast<jwt::error::signature_verification_error>(i)).message(),
				  std::error_code(static_cast<jwt::error::signature_verification_error>(-1)).message());
	}
	ASSERT_EQ(std::error_code(static_cast<jwt::error::signature_verification_error>(i)).message(),
			  std::error_code(static_cast<jwt::error::signature_verification_error>(-1)).message());

	for (i = 10; i < 22; i++) {
		ASSERT_NE(std::error_code(static_cast<jwt::error::signature_generation_error>(i)).message(),
				  std::error_code(static_cast<jwt::error::signature_generation_error>(-1)).message());
	}
	ASSERT_EQ(std::error_code(static_cast<jwt::error::signature_generation_error>(i)).message(),
			  std::error_code(static_cast<jwt::error::signature_generation_error>(-1)).message());

	for (i = 10; i < 16; i++) {
		ASSERT_NE(std::error_code(static_cast<jwt::error::token_verification_error>(i)).message(),
				  std::error_code(static_cast<jwt::error::token_verification_error>(-1)).message());
	}
	ASSERT_EQ(std::error_code(static_cast<jwt::error::token_verification_error>(i)).message(),
			  std::error_code(static_cast<jwt::error::token_verification_error>(-1)).message());
}

namespace {
	std::string google_cert =
// This is to handle the different subject alternate name ordering
// see https://github.com/wolfSSL/wolfssl/issues/4397
#ifdef LIBWOLFSSL_VERSION_HEX
		R"(-----BEGIN CERTIFICATE-----
MIIFATCCBGqgAwIBAgIKYFOB9QABAACIvTANBgkqhkiG9w0BAQUFADBGMQswCQYD
VQQGEwJVUzETMBEGA1UEChMKR29vZ2xlIEluYzEiMCAGA1UEAxMZR29vZ2xlIElu
dGVybmV0IEF1dGhvcml0eTAeFw0xMzA1MjIxNTQ5MDRaFw0xMzEwMzEyMzU5NTla
MGYxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpDYWxpZm9ybmlhMRYwFAYDVQQHEw1N
b3VudGFpbiBWaWV3MRMwEQYDVQQKEwpHb29nbGUgSW5jMRUwEwYDVQQDDAwqLmdv
b2dsZS5jb20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARmSpIUbCqhUBq1UwnR
Ai7/TNSk6W8JmasR+I0r/NLDYv5yApbAz8HXXN8hDdurMRP6Jy1Q0UIKmyls8HPH
exoCo4IDGzCCAxcwggLDBgNVHREEggK6MIICtoIUeW91dHViZWVkdWNhdGlvbi5j
b22CC3lvdXR1YmUuY29tggh5b3V0dS5iZYIKdXJjaGluLmNvbYISZ29vZ2xlY29t
bWVyY2UuY29tggpnb29nbGUuY29tghRnb29nbGUtYW5hbHl0aWNzLmNvbYIGZ29v
LmdsggRnLmNvggthbmRyb2lkLmNvbYILKi55dGltZy5jb22CFioueW91dHViZWVk
dWNhdGlvbi5jb22CDSoueW91dHViZS5jb22CFioueW91dHViZS1ub2Nvb2tpZS5j
b22CECoudXJsLmdvb2dsZS5jb22CDCoudXJjaGluLmNvbYINKi5nc3RhdGljLmNv
bYIUKi5nb29nbGVjb21tZXJjZS5jb22CDyouZ29vZ2xlYXBpcy5jboILKi5nb29n
bGUucHSCCyouZ29vZ2xlLnBsggsqLmdvb2dsZS5ubIILKi5nb29nbGUuaXSCCyou
Z29vZ2xlLmh1ggsqLmdvb2dsZS5mcoILKi5nb29nbGUuZXOCCyouZ29vZ2xlLmRl
gg8qLmdvb2dsZS5jb20udm6CDyouZ29vZ2xlLmNvbS50coIPKi5nb29nbGUuY29t
Lm14gg8qLmdvb2dsZS5jb20uY2+CDyouZ29vZ2xlLmNvbS5icoIPKi5nb29nbGUu
Y29tLmF1gg8qLmdvb2dsZS5jb20uYXKCDiouZ29vZ2xlLmNvLnVrgg4qLmdvb2ds
ZS5jby5qcIIOKi5nb29nbGUuY28uaW6CCyouZ29vZ2xlLmNsggsqLmdvb2dsZS5j
YYIWKi5nb29nbGUtYW5hbHl0aWNzLmNvbYISKi5jbG91ZC5nb29nbGUuY29tghYq
LmFwcGVuZ2luZS5nb29nbGUuY29tgg0qLmFuZHJvaWQuY29tggwqLmdvb2dsZS5j
b20wHQYDVR0OBBYEFFN409DVTUYFOWYp0Rxq5cqBhJ6GMB8GA1UdIwQYMBaAFL/A
MOv1QxE+Z7qekfv8atrjaxIkMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0BAQUF
AAOBgQADJ9Ct498oQvl/rsoengAWthKu8YmOf5lAfPOiK9fb8ZbkjDSg+p/4mPLx
47a59AYblvP75icrnRZCHBA1GBOIr0DJbHyC+0jhsOjnr1S5ptNmokR1o+U9tA7P
kjqbnmFBtzQXBz/+SM4VGCECWxs5UGlGmQTGkHgvGbJTDS1iNg==
-----END CERTIFICATE-----
)";
#else
		R"(-----BEGIN CERTIFICATE-----
MIIF8DCCBVmgAwIBAgIKYFOB9QABAACIvTANBgkqhkiG9w0BAQUFADBGMQswCQYD
VQQGEwJVUzETMBEGA1UEChMKR29vZ2xlIEluYzEiMCAGA1UEAxMZR29vZ2xlIElu
dGVybmV0IEF1dGhvcml0eTAeFw0xMzA1MjIxNTQ5MDRaFw0xMzEwMzEyMzU5NTla
MGYxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpDYWxpZm9ybmlhMRYwFAYDVQQHEw1N
b3VudGFpbiBWaWV3MRMwEQYDVQQKEwpHb29nbGUgSW5jMRUwEwYDVQQDFAwqLmdv
b2dsZS5jb20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARmSpIUbCqhUBq1UwnR
Ai7/TNSk6W8JmasR+I0r/NLDYv5yApbAz8HXXN8hDdurMRP6Jy1Q0UIKmyls8HPH
exoCo4IECjCCBAYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMAsGA1Ud
DwQEAwIHgDAdBgNVHQ4EFgQUU3jT0NVNRgU5ZinRHGrlyoGEnoYwHwYDVR0jBBgw
FoAUv8Aw6/VDET5nup6R+/xq2uNrEiQwWwYDVR0fBFQwUjBQoE6gTIZKaHR0cDov
L3d3dy5nc3RhdGljLmNvbS9Hb29nbGVJbnRlcm5ldEF1dGhvcml0eS9Hb29nbGVJ
bnRlcm5ldEF1dGhvcml0eS5jcmwwZgYIKwYBBQUHAQEEWjBYMFYGCCsGAQUFBzAC
hkpodHRwOi8vd3d3LmdzdGF0aWMuY29tL0dvb2dsZUludGVybmV0QXV0aG9yaXR5
L0dvb2dsZUludGVybmV0QXV0aG9yaXR5LmNydDAMBgNVHRMBAf8EAjAAMIICwwYD
VR0RBIICujCCAraCDCouZ29vZ2xlLmNvbYINKi5hbmRyb2lkLmNvbYIWKi5hcHBl
bmdpbmUuZ29vZ2xlLmNvbYISKi5jbG91ZC5nb29nbGUuY29tghYqLmdvb2dsZS1h
bmFseXRpY3MuY29tggsqLmdvb2dsZS5jYYILKi5nb29nbGUuY2yCDiouZ29vZ2xl
LmNvLmlugg4qLmdvb2dsZS5jby5qcIIOKi5nb29nbGUuY28udWuCDyouZ29vZ2xl
LmNvbS5hcoIPKi5nb29nbGUuY29tLmF1gg8qLmdvb2dsZS5jb20uYnKCDyouZ29v
Z2xlLmNvbS5jb4IPKi5nb29nbGUuY29tLm14gg8qLmdvb2dsZS5jb20udHKCDyou
Z29vZ2xlLmNvbS52boILKi5nb29nbGUuZGWCCyouZ29vZ2xlLmVzggsqLmdvb2ds
ZS5mcoILKi5nb29nbGUuaHWCCyouZ29vZ2xlLml0ggsqLmdvb2dsZS5ubIILKi5n
b29nbGUucGyCCyouZ29vZ2xlLnB0gg8qLmdvb2dsZWFwaXMuY26CFCouZ29vZ2xl
Y29tbWVyY2UuY29tgg0qLmdzdGF0aWMuY29tggwqLnVyY2hpbi5jb22CECoudXJs
Lmdvb2dsZS5jb22CFioueW91dHViZS1ub2Nvb2tpZS5jb22CDSoueW91dHViZS5j
b22CFioueW91dHViZWVkdWNhdGlvbi5jb22CCyoueXRpbWcuY29tggthbmRyb2lk
LmNvbYIEZy5jb4IGZ29vLmdsghRnb29nbGUtYW5hbHl0aWNzLmNvbYIKZ29vZ2xl
LmNvbYISZ29vZ2xlY29tbWVyY2UuY29tggp1cmNoaW4uY29tggh5b3V0dS5iZYIL
eW91dHViZS5jb22CFHlvdXR1YmVlZHVjYXRpb24uY29tMA0GCSqGSIb3DQEBBQUA
A4GBAAMn0K3j3yhC+X+uyh6eABa2Eq7xiY5/mUB886Ir19vxluSMNKD6n/iY8vHj
trn0BhuW8/vmJyudFkIcEDUYE4ivQMlsfIL7SOGw6OevVLmm02aiRHWj5T20Ds+S
OpueYUG3NBcHP/5IzhUYIQJbGzlQaUaZBMaQeC8ZslMNLWI2
-----END CERTIFICATE-----
)";
#endif

	std::string google_cert_base64_der = "MIIF8DCCBVmgAwIBAgIKYFOB9QABAACIvTANBgkqhkiG9w0BAQUFADBGMQswCQYD"
										 "VQQGEwJVUzETMBEGA1UEChMKR29vZ2xlIEluYzEiMCAGA1UEAxMZR29vZ2xlIElu"
										 "dGVybmV0IEF1dGhvcml0eTAeFw0xMzA1MjIxNTQ5MDRaFw0xMzEwMzEyMzU5NTla"
										 "MGYxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpDYWxpZm9ybmlhMRYwFAYDVQQHEw1N"
										 "b3VudGFpbiBWaWV3MRMwEQYDVQQKEwpHb29nbGUgSW5jMRUwEwYDVQQDFAwqLmdv"
										 "b2dsZS5jb20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARmSpIUbCqhUBq1UwnR"
										 "Ai7/TNSk6W8JmasR+I0r/NLDYv5yApbAz8HXXN8hDdurMRP6Jy1Q0UIKmyls8HPH"
										 "exoCo4IECjCCBAYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMAsGA1Ud"
										 "DwQEAwIHgDAdBgNVHQ4EFgQUU3jT0NVNRgU5ZinRHGrlyoGEnoYwHwYDVR0jBBgw"
										 "FoAUv8Aw6/VDET5nup6R+/xq2uNrEiQwWwYDVR0fBFQwUjBQoE6gTIZKaHR0cDov"
										 "L3d3dy5nc3RhdGljLmNvbS9Hb29nbGVJbnRlcm5ldEF1dGhvcml0eS9Hb29nbGVJ"
										 "bnRlcm5ldEF1dGhvcml0eS5jcmwwZgYIKwYBBQUHAQEEWjBYMFYGCCsGAQUFBzAC"
										 "hkpodHRwOi8vd3d3LmdzdGF0aWMuY29tL0dvb2dsZUludGVybmV0QXV0aG9yaXR5"
										 "L0dvb2dsZUludGVybmV0QXV0aG9yaXR5LmNydDAMBgNVHRMBAf8EAjAAMIICwwYD"
										 "VR0RBIICujCCAraCDCouZ29vZ2xlLmNvbYINKi5hbmRyb2lkLmNvbYIWKi5hcHBl"
										 "bmdpbmUuZ29vZ2xlLmNvbYISKi5jbG91ZC5nb29nbGUuY29tghYqLmdvb2dsZS1h"
										 "bmFseXRpY3MuY29tggsqLmdvb2dsZS5jYYILKi5nb29nbGUuY2yCDiouZ29vZ2xl"
										 "LmNvLmlugg4qLmdvb2dsZS5jby5qcIIOKi5nb29nbGUuY28udWuCDyouZ29vZ2xl"
										 "LmNvbS5hcoIPKi5nb29nbGUuY29tLmF1gg8qLmdvb2dsZS5jb20uYnKCDyouZ29v"
										 "Z2xlLmNvbS5jb4IPKi5nb29nbGUuY29tLm14gg8qLmdvb2dsZS5jb20udHKCDyou"
										 "Z29vZ2xlLmNvbS52boILKi5nb29nbGUuZGWCCyouZ29vZ2xlLmVzggsqLmdvb2ds"
										 "ZS5mcoILKi5nb29nbGUuaHWCCyouZ29vZ2xlLml0ggsqLmdvb2dsZS5ubIILKi5n"
										 "b29nbGUucGyCCyouZ29vZ2xlLnB0gg8qLmdvb2dsZWFwaXMuY26CFCouZ29vZ2xl"
										 "Y29tbWVyY2UuY29tgg0qLmdzdGF0aWMuY29tggwqLnVyY2hpbi5jb22CECoudXJs"
										 "Lmdvb2dsZS5jb22CFioueW91dHViZS1ub2Nvb2tpZS5jb22CDSoueW91dHViZS5j"
										 "b22CFioueW91dHViZWVkdWNhdGlvbi5jb22CCyoueXRpbWcuY29tggthbmRyb2lk"
										 "LmNvbYIEZy5jb4IGZ29vLmdsghRnb29nbGUtYW5hbHl0aWNzLmNvbYIKZ29vZ2xl"
										 "LmNvbYISZ29vZ2xlY29tbWVyY2UuY29tggp1cmNoaW4uY29tggh5b3V0dS5iZYIL"
										 "eW91dHViZS5jb22CFHlvdXR1YmVlZHVjYXRpb24uY29tMA0GCSqGSIb3DQEBBQUA"
										 "A4GBAAMn0K3j3yhC+X+uyh6eABa2Eq7xiY5/mUB886Ir19vxluSMNKD6n/iY8vHj"
										 "trn0BhuW8/vmJyudFkIcEDUYE4ivQMlsfIL7SOGw6OevVLmm02aiRHWj5T20Ds+S"
										 "OpueYUG3NBcHP/5IzhUYIQJbGzlQaUaZBMaQeC8ZslMNLWI2";

	std::string google_public_key = R"(-----BEGIN PUBLIC KEY-----
MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEZkqSFGwqoVAatVMJ0QIu/0zUpOlv
CZmrEfiNK/zSw2L+cgKWwM/B11zfIQ3bqzET+ictUNFCCpspbPBzx3saAg==
-----END PUBLIC KEY-----
)";
} // namespace
