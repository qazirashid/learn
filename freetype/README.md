# Font Glyph to SVG
I was trying to Render a font glyphs from a font to SVG.
Freetype font engine has this example for converting font glyp outlines to SVG.
I compiled it on ubuntu and named it 'font2svg'.
It is a dynamically linked executable so it will require installation of freetype2 to work on Linux. 

## fi2svg usage
I have made some additions to the example provided by freetype.org.
The provided example required a character.
I have changed it so that user can specify a font index as an unsigned int, instead of entering a character from keyboard.
'''bash
./fi2svg /usr/share/texmf/fonts/opentype/public/tex-gyre-math/texgyrepagella-math.otf 12 > index12.svg
'''

## font2svg usage
'''bash
./font2svg 'pathToFontFile' 'char_for_glyph'
./font2svg /usr/share/texmf/fonts/opentype/public/tex-gyre-math/texgyrepagella-math.otf B > B.svg
'''



