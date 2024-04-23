#include "Symbols.h"
using namespace symbols;

void SentenceAdding(string& OS, const char* word, bool space = true, bool double_space = false, string what="` ") {
	OS += word;
	if (space) OS += " ";
	else if (double_space) OS += what;
};

string Translate(string sentence, bool morzeToKirillica = false, bool eng = false) {
	string output_sentence;

	if (!morzeToKirillica) {
		std::transform(sentence.begin(), sentence.end(), sentence.begin(), ::toupper);
		for (int i = 0; i < sentence.length(); i++) {
			switch (sentence[i]) {
				case ' ': SentenceAdding(output_sentence, "", false, true); break;
				case 'ё':
				case 'Ё': sentence[i] = 'Е'; break;
				case 'я': sentence[i] = 'Я'; break;
			}
			if (eng) for (int j = 0; j < eAlphabet_CHAR.size(); j++) if (sentence[i] == eAlphabet_CHAR[j]) SentenceAdding(output_sentence, Morze_Alphabet_Eng[j]);
			if(!eng) for (int j = 0; j < Alphabet_CHAR.size(); j++) if (sentence[i] == Alphabet_CHAR[j]) SentenceAdding(output_sentence, Morze_Alphabet_Rus[j]);
			for (int j = 0; j < Punctuation_CHAR.size(); j++) if (sentence[i] == Punctuation_CHAR[j])SentenceAdding(output_sentence, Morze_Punctuation[j]);
			for (int j = 0; j < Numbers_CHAR.size(); j++) if (sentence[i] == Numbers_CHAR[j])SentenceAdding(output_sentence, Morze_Numbers[j]);
		}
	}
	else {
		char buff[512] = "";

		vector <string> result = {};
		std::transform(sentence.begin(), sentence.end(), sentence.begin(), ::toupper);
		for (int i = 0; i < sentence.size(); i++) {
			buff[i] += sentence[i];
		}

		
		char* context;
		char* tmp_char;
		tmp_char = strtok_s(buff, "  ", &context);

		for (int i = 0; tmp_char != NULL; i++) {
			result.push_back(tmp_char);
			tmp_char = strtok_s(nullptr, " ", &context);
		}


		for (int i = 0; i < result.size(); i++) {
			if (result[i] == "`") { result[i] = " "; SentenceAdding(output_sentence, " ", false); }
			if(eng)for (int j = 0; j < eAlphabet_pCONSTCHAR.size(); j++) if (result[i] == Morze_Alphabet_Eng[j]) SentenceAdding(output_sentence, eAlphabet_pCONSTCHAR[j], false);
			if(!eng)for (int j = 0; j < Alphabet_pCONSTCHAR.size(); j++) if (result[i] == Morze_Alphabet_Rus[j]) SentenceAdding(output_sentence, Alphabet_pCONSTCHAR[j], false);
			for (int j = 0; j < Punctuation_pCONSTCHAR.size(); j++) if (result[i] == Morze_Punctuation[j]) SentenceAdding(output_sentence, Punctuation_pCONSTCHAR[j], false);
			for (int j = 0; j < Numbers_pCONSTCHAR.size(); j++) if (result[i] == Morze_Numbers[j]) SentenceAdding(output_sentence, Numbers_pCONSTCHAR[j], false);
		}
		
		
	}
	return output_sentence;
};

void BeepMorze(string morze) {
	for (int i = 0; i < morze.size(); i++) {
		if (morze[i] == '.') Beep(500, 100);
		else if (morze[i] == '-') Beep(500, 500);
	}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");
	bool engl;
	string text = "Кириллица";
	while (true) {
		cout << "С какого языка переводить?[ru/en]: ";
		string lang;
		cin >> lang;
		if (lang[0] == 'r' && lang[1] == 'u') {
			text = "Кириллица";
			engl = false;
			cin.clear();
			break;
		}
		else if (lang[0] == 'e' && lang[1] == 'n') {
			text = "Латиница";
			engl = true;
			cin.clear();
			break;
		}
		else {
			cout << "Введен не корректный регион!" << endl;
		}
	}
	while (true) {
		for (int i = 0; i < 1; i++) {
			text[text.size()-1] = 'ы';
			cout << "1. С " << text << " на Морзе\n";
			text[text.size()-1] = 'у';
			cout << "2. С Морзе на "<< text <<"\nД: ";
		}
		char act;
		cin >> act;
		switch (act) {
		case '1': {
			cout << "Введите предложение:\n";
			string input_sentence;
			cin.ignore();
			getline(cin, input_sentence);
			auto output = Translate(input_sentence, false, engl);
			cout << output << endl;
			if (output != "") {
				while (true) {
					cout << "1. Назад\n2 - Воспроизвести результат\nД: ";
					cin >> act;
					if (act == '2') {
						for (int i = 0; i < output.size(); i++) {
							int long_dur = 250, short_dur = 100, freq = 700;
							if (output[i] == ' ') Sleep(120);
							else if (output[i] == '.') Beep(freq, short_dur);
							else if (output[i] == '-') Beep(freq, long_dur);
						}
					}
					else break;
				}
			}
		}break;
		case '2': {
			cout << "Введите предложение:\n";
			string input_sentence;
			cin.ignore();
			getline(cin, input_sentence);
			cout << Translate(input_sentence, true, engl) << endl;
		}break;
		}
	}
	system("pause");
	return 0;
}
