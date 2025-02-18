
import collections
import string

RUSSIAN_LETTER_FREQ = "��������������������������������"

def analyze_frequency(text):
    """ ������� ������� �������� � ������. """
    text = text.lower()
    counter = collections.Counter(text)
    sorted_chars = [char for char, _ in counter.most_common() if char in string.ascii_letters or char in '���������������������������������']
    return sorted_chars


def build_decryption_map(cipher_text, letter_freq):
    """ ������� ������� ����� ��� ����������� """
    sorted_chars = analyze_frequency(cipher_text)
    decryption_map = {cipher: plain for cipher, plain in zip(sorted_chars, letter_freq)}
    return decryption_map


def decrypt_text(cipher_text, decryption_map):
    """ �������������� ����� � ������� ������� ����� """
    return ''.join(decryption_map.get(char, char) for char in cipher_text)


cipher_emails = [
    "pmjmz.bzmutjig@nzqmamv.kwu",
    "giyh.lsxyl@pifeguh.vct",
    "enxbepbms.tkexgx@ykbxlxg.vhf"
]
cipher_addresses = [
    "��. �������������.6 ��.466",
    "��ueb��������� ��.�.34 ��.102",
    "��. ���������.60 ��.107"
]

all_cipher_text = ' '.join(cipher_emails + cipher_addresses)
decryption_map = build_decryption_map(all_cipher_text, RUSSIAN_LETTER_FREQ)

decoded_emails = [decrypt_text(email, decryption_map) for email in cipher_emails]
decoded_addresses = [decrypt_text(address, decryption_map) for address in cipher_addresses]

print("�������������� email:")
for email in decoded_emails:
    print(email)

print("\n �������������� ������:")
for address in decoded_addresses:
    print(address)

