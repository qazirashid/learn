
# Notes on SVG Specifications
These are notes on SVG specification. They are distributed over multiple markdown files.

Written down as part of reading [second editio of SVG 1.1 specification] (w3.org/TR/SV11)

## Basics of SVG

###  What is SVG?
SVG is a language for describing 2-D grphics in XML. 

### What are they types of SVG graphical objects?
SVG has three types of graphic objects: 1) shapes, 2) Text, and 3) image (raster)

### What can be done to SVG graphical objects? 

SVG objects cand be:
* a) grouped,
* b) styled, 
* c) transformed, 
* d) composited into previously rendered objects. 

### What are some of SVG feature sets?
The feature sets of SVG include 
* nested transformations
* clipping path
* alpa masks
* filter effects
* template objects


### What types of SVG drawings are there?
SVG drawings can be 1) Interactive, and 2) dynamic. 

### Can SVG do animations?
SVG animations be 1)defined and 2) triggered, using a) declaratively using SVG animation elements or 2) scripting. 

### How can we manipulate SVG prgrammatically?
SVG can be manipulated using a supplemental scripting language which accesses SVG Document Object Model (SVG DOM). 
SVG DOM provides complete access to all elements, attributes and properties. 
Event handlers can be assigned to any SVG graphical object.
SVG Document is very similar to HTML document and hence scripting of SVG is very similar to scripting of HTML.


### How is SVG 1.1 different from SVG 1.0?
SVG 1.1 is a modularization of SVG 1.0. A DTD is structured to allow profiling and composition of SVG with other SML languages.


### What is SVG MimeType?
SVG MIME type is "image/svg+xml". 
SVG files should have ".svg" extension for uncompressed files and "svgz" for gzip-compressed files.


### What are SVG Namespace, Public Identifier and System Identifier
#### SVG Name space 
http://www.w3.org/2000/svg
#### Public Identifier for SVG 1.1:
PUBLIC "-//W3C//DTD SVG 1.1//EN"
#### System Identifier for the SVG 1.1 Recommendation
http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd

A DOCTYPE declaration should not be provided in a SVG document.






