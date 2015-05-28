This is the readme file for the cot-translator application.

The goal of this tool is to allow translations extraction from a json file into a given folder using the 'export' mode.
The generated ts files can then be opened using Qt Linguist to be translated by translators.
Once done, just import the translations into the json file using the 'import' mode.

You can get all the applications options using -h / --help parameter on the command line.
At the time of writing, this is the available options:

Usage: ./cot-translator [options] json translations
A command line tool to extract and import translations for the cot application.

Options:
  -h, --help         Displays this help.
  -v, --version      Displays version information.
  -m, --mode <mode>  The execution mode of the translator: 'import' or 'export'
                     (default).

Arguments:
  json               Json file to read or write.
  translations       The folder to read or write the translations files.
