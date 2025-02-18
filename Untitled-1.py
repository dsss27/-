
import collections
import string

RUSSIAN_LETTER_FREQ = "оеаинтсрвлкмдпуяыьзбгчйхжюшцщэфё"

def analyze_frequency(text):
    """ Подсчет частоты символов в тексте. """
    text = text.lower()
    counter = collections.Counter(text)
    sorted_chars = [char for char, _ in counter.most_common() if char in string.ascii_letters or char in 'ёйцукенгшщзхъфывапролджэячсмитьбю']
    return sorted_chars


def build_decryption_map(cipher_text, letter_freq):
    """ Создает таблицу замен для расшифровки """
    sorted_chars = analyze_frequency(cipher_text)
    decryption_map = {cipher: plain for cipher, plain in zip(sorted_chars, letter_freq)}
    return decryption_map


def decrypt_text(cipher_text, decryption_map):
    """ Расшифровывает текст с помощью таблицы замен """
    return ''.join(decryption_map.get(char, char) for char in cipher_text)


cipher_emails = [
    "pmjmz.bzmutjig@nzqmamv.kwu",
    "giyh.lsxyl@pifeguh.vct",
    "enxbepbms.tkexgx@ykbxlxg.vhf"
]
cipher_addresses = [
    "ыу. Лпмшорхщтцкцл.6 тй.466",
    "Юдuebвудашэоют жя.ч.34 юх.102",
    "вг. Сээкэыатц.60 эф.107"
]

all_cipher_text = ' '.join(cipher_emails + cipher_addresses)
decryption_map = build_decryption_map(all_cipher_text, RUSSIAN_LETTER_FREQ)

decoded_emails = [decrypt_text(email, decryption_map) for email in cipher_emails]
decoded_addresses = [decrypt_text(address, decryption_map) for address in cipher_addresses]

print("Расшифрованные email:")
for email in decoded_emails:
    print(email)

print("\n Расшифрованные адреса:")
for address in decoded_addresses:
    print(address)

