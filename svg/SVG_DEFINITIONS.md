# SVG Definitions
## Animation Element
An **animation element** is an **element** that can be used to animate the **attribute** or **property value** of another **element**. 

**Elements** have **"attributes"** and **"properties"**.

Animation Elements:    
* "animateColor"
* "animateMotion"
* "animateTransform"
* "animate" and
* "set"

## Animation Event Attribute
An **animation event attribute** is an **event attribute** that specifies the script to run for a particular animation-related **event**. 
Animation attribute events"
* "onbegin"
* "onend"
* "onload"
* "onrepeat"

## Basic Shapes
A set of predefined convenience shapes. 
Basis shapes:
* "circle"
* " ellipse"
* "line"
* "polygon"
* "polyline"
* "rect"


## canvas
A surface onto which graphical objects are drawn. A canvas can be real media or abstract surface such as computer memory. 

## Clipping path
A combination of  **1) path, 2) Text, and 3) Basic Shapes** which serve as an **outline** of a mask. Anything in the outline is allowed to be painted. No paint can be applied outside the outline.

## Container Element
An **element** that can have **graphics elements** and other **container elements** as child elements. 
Container Elements:
* "a"
* "defs"
* "glyph"
* "g"
* "marker"
* "mask"
* "missing-glyph"
* "pattern"
* "svg"
* "switch"
* "symbol"


## Conditional Processing Attribute
A conditional processing attribute appears on an **element** and will control whether or not the element will be processed. 
Conditional Processing Attributes:
* "requiredExtension"
* "requiredFeature"
* "systemLanguage"

## Core Attributes
Core attributes are the attributes that can be applied to an **SVG element**.
Core Attributes:
* "id"
* "xml:base"
* "xml:lang"
* "xml:space"


## Current Transformation Matrix (CTM)
A trasformation matrix defines the mathematical mapping from one coordinate system into another using 3x3 matrix. 
The CTM defines the mapping from the **user coordinate system** to the **viewport coordinate system**. 


## Descriptive Element
An element that provides supplementary information about its parent element. 
Descriptive elements:
* "desc"
* "metadata"
* "title"


## Document Event Attribute
A document event attribute is an attribute that specifies a script to be run for document level events.
Document Event Attributes:
* "onabort"
* "onerror"
* "onresize"
* "onscroll"
* "onunload"
* "onzoom"


## fill 
the operation of painting the interrior of an outline defined by a shape or text glyph.

## font
A font is a **collection of glyphs**, where the glyphs share a common look and styling.
A font specifies the character glyphs, the spacing between characters and character alignement for rendering strings of characters.

## Glyph
A glyph is a **unit of rendered content**. A collection of glyphs consititues a font. 
Often a glyph has a one-to-one correspondance with a character to be drawn. 
A glyph is defined by *one or more shapes* along with additional information used by font engines to place glyphs on canvas.

## Gradient Element
A gradient element is one that defines a gradient paint server.
* "linearGradient"
* "radialGradient"

 
  
## Graphical Event Attribute
A graphical event attribute is an event attribute that specifies a script to run for a particular user interaction. 
Graphical Event Attributes:
* "onactivate"
* "onclick"
* "onfocusin"
* "onfocusout"
* "onload"
* "onmousedown"
* "onmouseover"
* "onmouseout"
* "onmouseup"

## Graphics Element

## Hit-testing
The process of determining whether a pointer intersects a given **graphics element**.
Hit-testing is used to dispatch mouse events to graphics elemtns. 
AKA "hit detection" or "picking".

## IRI reference
An IRI reference is an **Internationalized Resources Identifier** with an optional **framgement identifier**.
The IRI serves a reference to a resoruce and framgment identifier references the sub-resource within the resource. 


## Light Source Element
specifies the light source information.
* "feDistantLight"
* "fePointLight"
* "feSpotLight"

## Local IRI reference
An IRI that references to resources contained in the current document. 

## Mask
A **container Element** that contains **Graphics elments** or other **container elements** defining a set of graphics objects that is to be used as a semi-transperant mask for compositing foreground objects into the current background object. 

## Paint
A paint is a way of putting color onto the canvas.
A paint consists of color values and associated alpha values. 
Paint types:
** "color" -- a smooth consistent color
** "gradient" -- A smoothly varying color
** "pattern"  -- A pattern of color

## Presentation Attributes
An **XML attribute** on an **SVG element** which specifies a values for a given **property** for that element. The properties affect the rendering of element on the canvas. 

## Property
A parameter that specifies how a document should be rendered. 
A complete list of SVG properties is listed at [SVG Property Index](https://www.w3.org/TR/SVG11/propidx.html)
**Properties** are assigned to **SVG elements**  by either 1) using **presentation attributes** on SVG elements or 2) by using a **styling language** such as CSS.


## Shape
A shape is a **graphics element** that is defined by a combination of straight lines and curves.


## stroke 
The operation of painting the outline of a shape.

## SVG Context
An SVG context is a **document fragment** where all **SVG elements within the fragment**  must be subject to processing by an **SVG user agent** according to rules of SVG specification.

SVG context only contains SVG elments and any forigen elements in the document fragment are not part of SVG context.

## SVG Document Fragement
The XML document sub-tree which starts with an "<svg>" element and ends with "</svg>".

## SVG User Agent
An SVG user agent is a **user agent** that is able to retrieve and render SVG content. 

## SVG viewport
The viewport defines a rectangular region on the SVG canvas for which SVG content is rendered. 

## text content element
* "altGlyph"
* "textPath"
* "tref"
* "tspan"

 




 
 
 

  
