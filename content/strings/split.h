/**
 * Author: Linny
 * Date: 2023-09-06
 * Source: https://codereview.stackexchange.com/questions/260457/efficiently-splitting-a-string-in-c
 * Description: splits a string by a delimiter
 * Status: Works but not stress-tested
 */
#pragma once

vector<string> split(string input, char delimiter) {
	vector<string> elements;
    stringstream stream(input);
    string element;

    while (getline(stream, element, delimiter)) {
        elements.push_back(element);
    }

    return elements;
}
