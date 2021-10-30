<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="SK6805-1515">
<packages>
<package name="1515">
<smd name="DIN" x="-0.48" y="-0.48" dx="0.55" dy="0.55" layer="1"/>
<smd name="5V" x="0.48" y="-0.48" dx="0.55" dy="0.55" layer="1"/>
<smd name="DOUT" x="0.48" y="0.48" dx="0.55" dy="0.55" layer="1"/>
<smd name="GND" x="-0.48" y="0.48" dx="0.55" dy="0.55" layer="1"/>
<wire x1="-0.8" y1="0.8" x2="0.8" y2="0.8" width="0.0762" layer="21"/>
<wire x1="0.8" y1="0.8" x2="0.8" y2="-0.8" width="0.0762" layer="21"/>
<wire x1="-0.8" y1="0.8" x2="-0.8" y2="-0.2" width="0.0762" layer="21"/>
<wire x1="-0.2" y1="-0.8" x2="0.8" y2="-0.8" width="0.0762" layer="21"/>
<wire x1="-0.8" y1="-0.4" x2="-0.8" y2="-0.8" width="0.0762" layer="21"/>
<wire x1="-0.8" y1="-0.8" x2="-0.4" y2="-0.8" width="0.0762" layer="21"/>
<text x="-0.835" y="0.9525" size="0.254" layer="25">&gt;NAME</text>
<wire x1="0.7" y1="0.9" x2="0.9" y2="0.9" width="0.1016" layer="21"/>
<wire x1="0.9" y1="0.9" x2="0.9" y2="0.7" width="0.1016" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="SK6805-1515">
<wire x1="0" y1="0" x2="0" y2="10.16" width="0.254" layer="94"/>
<wire x1="0" y1="10.16" x2="10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="10.16" x2="10.16" y2="0" width="0.254" layer="94"/>
<wire x1="10.16" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<pin name="GND" x="5.08" y="-2.54" visible="pad" length="short" direction="pwr" rot="R90"/>
<pin name="DIN" x="-2.54" y="5.08" visible="off" length="short"/>
<pin name="DOUT" x="12.7" y="5.08" visible="off" length="short" rot="R180"/>
<pin name="5V" x="8.89" y="12.7" visible="pad" length="short" direction="pwr" rot="R270"/>
<text x="1.27" y="8.89" size="0.635" layer="94">SK6805-1515</text>
<text x="0" y="11.43" size="1.27" layer="95">&gt;NAME</text>
<text x="0.635" y="5.08" size="0.635" layer="94">DIN</text>
<text x="6.985" y="5.08" size="0.635" layer="94">DOUT</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="SK6805-1515" prefix="LED" uservalue="yes">
<gates>
<gate name="G$1" symbol="SK6805-1515" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1515">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="DIN" pad="DIN"/>
<connect gate="G$1" pin="DOUT" pad="DOUT"/>
<connect gate="G$1" pin="GND" pad="GND"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1X03" urn="urn:adsk.eagle:footprint:22340/1" locally_modified="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<pad name="1" x="-2.54" y="0" drill="1.016" diameter="1.778" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" diameter="1.778" rot="R90"/>
<pad name="3" x="2.54" y="0" drill="1.016" diameter="1.778" rot="R90"/>
<text x="-3.8862" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.81" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
</package>
<package name="1X03/90" urn="urn:adsk.eagle:footprint:22341/1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-3.81" y1="-1.905" x2="-1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.905" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="6.985" x2="-2.54" y2="1.27" width="0.762" layer="21"/>
<wire x1="-1.27" y1="-1.905" x2="1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-1.905" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="6.985" x2="0" y2="1.27" width="0.762" layer="21"/>
<wire x1="1.27" y1="-1.905" x2="3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-1.905" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="6.985" x2="2.54" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-2.54" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-4.445" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="5.715" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-2.921" y1="0.635" x2="-2.159" y2="1.143" layer="21"/>
<rectangle x1="-0.381" y1="0.635" x2="0.381" y2="1.143" layer="21"/>
<rectangle x1="2.159" y1="0.635" x2="2.921" y2="1.143" layer="21"/>
<rectangle x1="-2.921" y1="-2.921" x2="-2.159" y2="-1.905" layer="21"/>
<rectangle x1="-0.381" y1="-2.921" x2="0.381" y2="-1.905" layer="21"/>
<rectangle x1="2.159" y1="-2.921" x2="2.921" y2="-1.905" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="1X03" urn="urn:adsk.eagle:package:22458/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X03"/>
</packageinstances>
</package3d>
<package3d name="1X03/90" urn="urn:adsk.eagle:package:22459/2" type="model">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X03/90"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PINHD3">
<wire x1="-6.35" y1="-5.08" x2="1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="1.27" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="5.08" x2="-6.35" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="5.08" x2="-6.35" y2="-5.08" width="0.4064" layer="94"/>
<text x="-6.35" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-1X3" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINHD3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X03">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22458/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="92" constant="no"/>
</technology>
</technologies>
</device>
<device name="/90" package="1X03/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22459/2"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="17" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="LED1" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED2" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED3" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED4" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED5" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="JP1" library="pinhead" deviceset="PINHD-1X3" device="" package3d_urn="urn:adsk.eagle:package:22458/2"/>
<part name="JP2" library="pinhead" deviceset="PINHD-1X3" device="" package3d_urn="urn:adsk.eagle:package:22458/2"/>
<part name="LED6" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED7" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED8" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED9" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED10" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED11" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED12" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED13" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED14" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED15" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED16" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED17" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED18" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED19" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED20" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED21" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED22" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED23" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED24" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED25" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED26" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED27" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED28" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED29" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED30" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED31" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED32" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED33" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED34" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED35" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED36" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED37" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED38" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED39" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED40" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED41" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED42" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED43" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED44" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED45" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED46" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED47" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED48" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED49" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED50" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED51" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED52" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED53" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED54" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED55" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED56" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED57" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED58" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED59" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED60" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED61" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED62" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED63" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED64" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED65" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED66" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED67" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED68" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED69" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
<part name="LED70" library="SK6805-1515" deviceset="SK6805-1515" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="LED1" gate="G$1" x="7.62" y="12.7" smashed="yes">
<attribute name="NAME" x="7.62" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED2" gate="G$1" x="25.4" y="12.7" smashed="yes">
<attribute name="NAME" x="25.4" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED3" gate="G$1" x="43.18" y="12.7" smashed="yes">
<attribute name="NAME" x="43.18" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED4" gate="G$1" x="60.96" y="12.7" smashed="yes">
<attribute name="NAME" x="60.96" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED5" gate="G$1" x="78.74" y="12.7" smashed="yes">
<attribute name="NAME" x="78.74" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="JP1" gate="A" x="12.7" y="38.1" smashed="yes">
<attribute name="NAME" x="6.35" y="43.815" size="1.778" layer="95"/>
<attribute name="VALUE" x="6.35" y="30.48" size="1.778" layer="96"/>
</instance>
<instance part="JP2" gate="A" x="198.12" y="-157.48" smashed="yes" rot="R180">
<attribute name="NAME" x="204.47" y="-163.195" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="204.47" y="-149.86" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="LED6" gate="G$1" x="7.62" y="-12.7" smashed="yes">
<attribute name="NAME" x="7.62" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED7" gate="G$1" x="25.4" y="-12.7" smashed="yes">
<attribute name="NAME" x="25.4" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED8" gate="G$1" x="43.18" y="-12.7" smashed="yes">
<attribute name="NAME" x="43.18" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED9" gate="G$1" x="60.96" y="-12.7" smashed="yes">
<attribute name="NAME" x="60.96" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED10" gate="G$1" x="78.74" y="-12.7" smashed="yes">
<attribute name="NAME" x="78.74" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED11" gate="G$1" x="7.62" y="-38.1" smashed="yes">
<attribute name="NAME" x="7.62" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED12" gate="G$1" x="25.4" y="-38.1" smashed="yes">
<attribute name="NAME" x="25.4" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED13" gate="G$1" x="43.18" y="-38.1" smashed="yes">
<attribute name="NAME" x="43.18" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED14" gate="G$1" x="60.96" y="-38.1" smashed="yes">
<attribute name="NAME" x="60.96" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED15" gate="G$1" x="78.74" y="-38.1" smashed="yes">
<attribute name="NAME" x="78.74" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED16" gate="G$1" x="7.62" y="-63.5" smashed="yes">
<attribute name="NAME" x="7.62" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED17" gate="G$1" x="25.4" y="-63.5" smashed="yes">
<attribute name="NAME" x="25.4" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED18" gate="G$1" x="43.18" y="-63.5" smashed="yes">
<attribute name="NAME" x="43.18" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED19" gate="G$1" x="60.96" y="-63.5" smashed="yes">
<attribute name="NAME" x="60.96" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED20" gate="G$1" x="78.74" y="-63.5" smashed="yes">
<attribute name="NAME" x="78.74" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED21" gate="G$1" x="7.62" y="-88.9" smashed="yes">
<attribute name="NAME" x="7.62" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED22" gate="G$1" x="25.4" y="-88.9" smashed="yes">
<attribute name="NAME" x="25.4" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED23" gate="G$1" x="43.18" y="-88.9" smashed="yes">
<attribute name="NAME" x="43.18" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED24" gate="G$1" x="60.96" y="-88.9" smashed="yes">
<attribute name="NAME" x="60.96" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED25" gate="G$1" x="78.74" y="-88.9" smashed="yes">
<attribute name="NAME" x="78.74" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED26" gate="G$1" x="7.62" y="-114.3" smashed="yes">
<attribute name="NAME" x="7.62" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED27" gate="G$1" x="25.4" y="-114.3" smashed="yes">
<attribute name="NAME" x="25.4" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED28" gate="G$1" x="43.18" y="-114.3" smashed="yes">
<attribute name="NAME" x="43.18" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED29" gate="G$1" x="60.96" y="-114.3" smashed="yes">
<attribute name="NAME" x="60.96" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED30" gate="G$1" x="78.74" y="-114.3" smashed="yes">
<attribute name="NAME" x="78.74" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED31" gate="G$1" x="7.62" y="-139.7" smashed="yes">
<attribute name="NAME" x="7.62" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED32" gate="G$1" x="25.4" y="-139.7" smashed="yes">
<attribute name="NAME" x="25.4" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED33" gate="G$1" x="43.18" y="-139.7" smashed="yes">
<attribute name="NAME" x="43.18" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED34" gate="G$1" x="60.96" y="-139.7" smashed="yes">
<attribute name="NAME" x="60.96" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED35" gate="G$1" x="78.74" y="-139.7" smashed="yes">
<attribute name="NAME" x="78.74" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED36" gate="G$1" x="121.92" y="12.7" smashed="yes">
<attribute name="NAME" x="121.92" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED37" gate="G$1" x="139.7" y="12.7" smashed="yes">
<attribute name="NAME" x="139.7" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED38" gate="G$1" x="157.48" y="12.7" smashed="yes">
<attribute name="NAME" x="157.48" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED39" gate="G$1" x="175.26" y="12.7" smashed="yes">
<attribute name="NAME" x="175.26" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED40" gate="G$1" x="193.04" y="12.7" smashed="yes">
<attribute name="NAME" x="193.04" y="24.13" size="1.27" layer="95"/>
</instance>
<instance part="LED41" gate="G$1" x="121.92" y="-12.7" smashed="yes">
<attribute name="NAME" x="121.92" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED42" gate="G$1" x="139.7" y="-12.7" smashed="yes">
<attribute name="NAME" x="139.7" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED43" gate="G$1" x="157.48" y="-12.7" smashed="yes">
<attribute name="NAME" x="157.48" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED44" gate="G$1" x="175.26" y="-12.7" smashed="yes">
<attribute name="NAME" x="175.26" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED45" gate="G$1" x="193.04" y="-12.7" smashed="yes">
<attribute name="NAME" x="193.04" y="-1.27" size="1.27" layer="95"/>
</instance>
<instance part="LED46" gate="G$1" x="121.92" y="-38.1" smashed="yes">
<attribute name="NAME" x="121.92" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED47" gate="G$1" x="139.7" y="-38.1" smashed="yes">
<attribute name="NAME" x="139.7" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED48" gate="G$1" x="157.48" y="-38.1" smashed="yes">
<attribute name="NAME" x="157.48" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED49" gate="G$1" x="175.26" y="-38.1" smashed="yes">
<attribute name="NAME" x="175.26" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED50" gate="G$1" x="193.04" y="-38.1" smashed="yes">
<attribute name="NAME" x="193.04" y="-26.67" size="1.27" layer="95"/>
</instance>
<instance part="LED51" gate="G$1" x="121.92" y="-63.5" smashed="yes">
<attribute name="NAME" x="121.92" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED52" gate="G$1" x="139.7" y="-63.5" smashed="yes">
<attribute name="NAME" x="139.7" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED53" gate="G$1" x="157.48" y="-63.5" smashed="yes">
<attribute name="NAME" x="157.48" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED54" gate="G$1" x="175.26" y="-63.5" smashed="yes">
<attribute name="NAME" x="175.26" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED55" gate="G$1" x="193.04" y="-63.5" smashed="yes">
<attribute name="NAME" x="193.04" y="-52.07" size="1.27" layer="95"/>
</instance>
<instance part="LED56" gate="G$1" x="121.92" y="-88.9" smashed="yes">
<attribute name="NAME" x="121.92" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED57" gate="G$1" x="139.7" y="-88.9" smashed="yes">
<attribute name="NAME" x="139.7" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED58" gate="G$1" x="157.48" y="-88.9" smashed="yes">
<attribute name="NAME" x="157.48" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED59" gate="G$1" x="175.26" y="-88.9" smashed="yes">
<attribute name="NAME" x="175.26" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED60" gate="G$1" x="193.04" y="-88.9" smashed="yes">
<attribute name="NAME" x="193.04" y="-77.47" size="1.27" layer="95"/>
</instance>
<instance part="LED61" gate="G$1" x="121.92" y="-114.3" smashed="yes">
<attribute name="NAME" x="121.92" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED62" gate="G$1" x="139.7" y="-114.3" smashed="yes">
<attribute name="NAME" x="139.7" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED63" gate="G$1" x="157.48" y="-114.3" smashed="yes">
<attribute name="NAME" x="157.48" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED64" gate="G$1" x="175.26" y="-114.3" smashed="yes">
<attribute name="NAME" x="175.26" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED65" gate="G$1" x="193.04" y="-114.3" smashed="yes">
<attribute name="NAME" x="193.04" y="-102.87" size="1.27" layer="95"/>
</instance>
<instance part="LED66" gate="G$1" x="121.92" y="-139.7" smashed="yes">
<attribute name="NAME" x="121.92" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED67" gate="G$1" x="139.7" y="-139.7" smashed="yes">
<attribute name="NAME" x="139.7" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED68" gate="G$1" x="157.48" y="-139.7" smashed="yes">
<attribute name="NAME" x="157.48" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED69" gate="G$1" x="175.26" y="-139.7" smashed="yes">
<attribute name="NAME" x="175.26" y="-128.27" size="1.27" layer="95"/>
</instance>
<instance part="LED70" gate="G$1" x="193.04" y="-139.7" smashed="yes">
<attribute name="NAME" x="193.04" y="-128.27" size="1.27" layer="95"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="LED3" gate="G$1" pin="DOUT"/>
<pinref part="LED4" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="17.78" x2="55.88" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="LED3" gate="G$1" pin="DIN"/>
<pinref part="LED2" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="17.78" x2="40.64" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="LED2" gate="G$1" pin="DIN"/>
<pinref part="LED1" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="17.78" x2="22.86" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="LED4" gate="G$1" pin="DOUT"/>
<pinref part="LED5" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="17.78" x2="73.66" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DIN" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="40.64" x2="2.54" y2="17.78" width="0.1524" layer="91"/>
<wire x1="2.54" y1="17.78" x2="5.08" y2="17.78" width="0.1524" layer="91"/>
<pinref part="JP1" gate="A" pin="1"/>
<wire x1="10.16" y1="40.64" x2="2.54" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="LED8" gate="G$1" pin="DOUT"/>
<pinref part="LED9" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="-7.62" x2="55.88" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="LED8" gate="G$1" pin="DIN"/>
<pinref part="LED7" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="-7.62" x2="40.64" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="LED7" gate="G$1" pin="DIN"/>
<pinref part="LED6" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="-7.62" x2="22.86" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="LED9" gate="G$1" pin="DOUT"/>
<pinref part="LED10" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="-7.62" x2="73.66" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="LED6" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="-7.62" x2="5.08" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="LED5" gate="G$1" pin="DOUT"/>
<wire x1="91.44" y1="17.78" x2="93.98" y2="17.78" width="0.1524" layer="91"/>
<wire x1="93.98" y1="17.78" x2="93.98" y2="5.08" width="0.1524" layer="91"/>
<wire x1="93.98" y1="5.08" x2="2.54" y2="5.08" width="0.1524" layer="91"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="LED13" gate="G$1" pin="DOUT"/>
<pinref part="LED14" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="-33.02" x2="55.88" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="LED13" gate="G$1" pin="DIN"/>
<pinref part="LED12" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="-33.02" x2="40.64" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="LED12" gate="G$1" pin="DIN"/>
<pinref part="LED11" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="-33.02" x2="22.86" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="LED14" gate="G$1" pin="DOUT"/>
<pinref part="LED15" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="-33.02" x2="73.66" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="LED11" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="-33.02" x2="5.08" y2="-33.02" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-7.62" x2="93.98" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-20.32" x2="2.54" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-20.32" x2="2.54" y2="-33.02" width="0.1524" layer="91"/>
<pinref part="LED10" gate="G$1" pin="DOUT"/>
<wire x1="93.98" y1="-7.62" x2="91.44" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="JP1" gate="A" pin="3"/>
<wire x1="119.38" y1="27.94" x2="119.38" y2="2.54" width="0.1524" layer="91"/>
<wire x1="119.38" y1="2.54" x2="119.38" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="119.38" y1="-22.86" x2="119.38" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="119.38" y1="-48.26" x2="119.38" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="119.38" y1="-73.66" x2="119.38" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="119.38" y1="-99.06" x2="119.38" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="10.16" y1="35.56" x2="0" y2="35.56" width="0.1524" layer="91"/>
<wire x1="0" y1="35.56" x2="0" y2="27.94" width="0.1524" layer="91"/>
<pinref part="LED1" gate="G$1" pin="5V"/>
<wire x1="0" y1="27.94" x2="0" y2="2.54" width="0.1524" layer="91"/>
<wire x1="0" y1="2.54" x2="0" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="0" y1="-22.86" x2="0" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="0" y1="-48.26" x2="0" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="0" y1="-73.66" x2="0" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="0" y1="-99.06" x2="0" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="16.51" y1="25.4" x2="16.51" y2="27.94" width="0.1524" layer="91"/>
<wire x1="0" y1="27.94" x2="16.51" y2="27.94" width="0.1524" layer="91"/>
<junction x="0" y="27.94"/>
<pinref part="LED2" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="25.4" x2="34.29" y2="27.94" width="0.1524" layer="91"/>
<label x="38.1" y="27.94" size="1.778" layer="95"/>
<wire x1="16.51" y1="27.94" x2="34.29" y2="27.94" width="0.1524" layer="91"/>
<junction x="16.51" y="27.94"/>
<pinref part="LED3" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="25.4" x2="52.07" y2="27.94" width="0.1524" layer="91"/>
<wire x1="34.29" y1="27.94" x2="52.07" y2="27.94" width="0.1524" layer="91"/>
<junction x="34.29" y="27.94"/>
<pinref part="LED4" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="25.4" x2="69.85" y2="27.94" width="0.1524" layer="91"/>
<wire x1="52.07" y1="27.94" x2="69.85" y2="27.94" width="0.1524" layer="91"/>
<junction x="52.07" y="27.94"/>
<pinref part="LED5" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="27.94" x2="87.63" y2="25.4" width="0.1524" layer="91"/>
<wire x1="69.85" y1="27.94" x2="87.63" y2="27.94" width="0.1524" layer="91"/>
<junction x="69.85" y="27.94"/>
<wire x1="87.63" y1="27.94" x2="119.38" y2="27.94" width="0.1524" layer="91"/>
<junction x="87.63" y="27.94"/>
<pinref part="LED36" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="25.4" x2="130.81" y2="27.94" width="0.1524" layer="91"/>
<wire x1="119.38" y1="27.94" x2="130.81" y2="27.94" width="0.1524" layer="91"/>
<junction x="119.38" y="27.94"/>
<pinref part="LED37" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="25.4" x2="148.59" y2="27.94" width="0.1524" layer="91"/>
<wire x1="130.81" y1="27.94" x2="148.59" y2="27.94" width="0.1524" layer="91"/>
<junction x="130.81" y="27.94"/>
<pinref part="LED38" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="25.4" x2="166.37" y2="27.94" width="0.1524" layer="91"/>
<wire x1="148.59" y1="27.94" x2="166.37" y2="27.94" width="0.1524" layer="91"/>
<junction x="148.59" y="27.94"/>
<pinref part="LED39" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="25.4" x2="184.15" y2="27.94" width="0.1524" layer="91"/>
<wire x1="166.37" y1="27.94" x2="184.15" y2="27.94" width="0.1524" layer="91"/>
<junction x="166.37" y="27.94"/>
<pinref part="LED40" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="27.94" x2="201.93" y2="25.4" width="0.1524" layer="91"/>
<wire x1="184.15" y1="27.94" x2="201.93" y2="27.94" width="0.1524" layer="91"/>
<junction x="184.15" y="27.94"/>
<pinref part="LED10" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="2.54" x2="87.63" y2="0" width="0.1524" layer="91"/>
<pinref part="LED9" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="0" x2="69.85" y2="2.54" width="0.1524" layer="91"/>
<wire x1="87.63" y1="2.54" x2="69.85" y2="2.54" width="0.1524" layer="91"/>
<pinref part="LED8" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="0" x2="52.07" y2="2.54" width="0.1524" layer="91"/>
<wire x1="69.85" y1="2.54" x2="52.07" y2="2.54" width="0.1524" layer="91"/>
<junction x="69.85" y="2.54"/>
<pinref part="LED7" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="0" x2="34.29" y2="2.54" width="0.1524" layer="91"/>
<wire x1="52.07" y1="2.54" x2="34.29" y2="2.54" width="0.1524" layer="91"/>
<junction x="52.07" y="2.54"/>
<pinref part="LED6" gate="G$1" pin="5V"/>
<wire x1="16.51" y1="0" x2="16.51" y2="2.54" width="0.1524" layer="91"/>
<wire x1="34.29" y1="2.54" x2="16.51" y2="2.54" width="0.1524" layer="91"/>
<junction x="34.29" y="2.54"/>
<wire x1="16.51" y1="2.54" x2="0" y2="2.54" width="0.1524" layer="91"/>
<junction x="16.51" y="2.54"/>
<junction x="0" y="2.54"/>
<pinref part="LED15" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="-22.86" x2="87.63" y2="-25.4" width="0.1524" layer="91"/>
<pinref part="LED14" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="-25.4" x2="69.85" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="87.63" y1="-22.86" x2="69.85" y2="-22.86" width="0.1524" layer="91"/>
<pinref part="LED13" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="-25.4" x2="52.07" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="69.85" y1="-22.86" x2="52.07" y2="-22.86" width="0.1524" layer="91"/>
<junction x="69.85" y="-22.86"/>
<pinref part="LED12" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="-25.4" x2="34.29" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="52.07" y1="-22.86" x2="34.29" y2="-22.86" width="0.1524" layer="91"/>
<junction x="52.07" y="-22.86"/>
<pinref part="LED11" gate="G$1" pin="5V"/>
<wire x1="16.51" y1="-25.4" x2="16.51" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="34.29" y1="-22.86" x2="16.51" y2="-22.86" width="0.1524" layer="91"/>
<junction x="34.29" y="-22.86"/>
<wire x1="16.51" y1="-22.86" x2="0" y2="-22.86" width="0.1524" layer="91"/>
<junction x="16.51" y="-22.86"/>
<junction x="0" y="-22.86"/>
<pinref part="LED20" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="-48.26" x2="87.63" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="LED19" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="-50.8" x2="69.85" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="87.63" y1="-48.26" x2="69.85" y2="-48.26" width="0.1524" layer="91"/>
<pinref part="LED18" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="-50.8" x2="52.07" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="69.85" y1="-48.26" x2="52.07" y2="-48.26" width="0.1524" layer="91"/>
<junction x="69.85" y="-48.26"/>
<pinref part="LED17" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="-50.8" x2="34.29" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="52.07" y1="-48.26" x2="34.29" y2="-48.26" width="0.1524" layer="91"/>
<junction x="52.07" y="-48.26"/>
<pinref part="LED16" gate="G$1" pin="5V"/>
<wire x1="16.51" y1="-50.8" x2="16.51" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="34.29" y1="-48.26" x2="16.51" y2="-48.26" width="0.1524" layer="91"/>
<junction x="34.29" y="-48.26"/>
<wire x1="16.51" y1="-48.26" x2="0" y2="-48.26" width="0.1524" layer="91"/>
<junction x="16.51" y="-48.26"/>
<junction x="0" y="-48.26"/>
<pinref part="LED25" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="-73.66" x2="87.63" y2="-76.2" width="0.1524" layer="91"/>
<pinref part="LED24" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="-76.2" x2="69.85" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="87.63" y1="-73.66" x2="69.85" y2="-73.66" width="0.1524" layer="91"/>
<pinref part="LED23" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="-76.2" x2="52.07" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="69.85" y1="-73.66" x2="52.07" y2="-73.66" width="0.1524" layer="91"/>
<junction x="69.85" y="-73.66"/>
<pinref part="LED22" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="-76.2" x2="34.29" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="52.07" y1="-73.66" x2="34.29" y2="-73.66" width="0.1524" layer="91"/>
<junction x="52.07" y="-73.66"/>
<pinref part="LED21" gate="G$1" pin="5V"/>
<wire x1="16.51" y1="-76.2" x2="16.51" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="34.29" y1="-73.66" x2="16.51" y2="-73.66" width="0.1524" layer="91"/>
<junction x="34.29" y="-73.66"/>
<wire x1="16.51" y1="-73.66" x2="0" y2="-73.66" width="0.1524" layer="91"/>
<junction x="16.51" y="-73.66"/>
<junction x="0" y="-73.66"/>
<pinref part="LED30" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="-99.06" x2="87.63" y2="-101.6" width="0.1524" layer="91"/>
<pinref part="LED29" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="-101.6" x2="69.85" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="87.63" y1="-99.06" x2="69.85" y2="-99.06" width="0.1524" layer="91"/>
<pinref part="LED28" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="-101.6" x2="52.07" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="69.85" y1="-99.06" x2="52.07" y2="-99.06" width="0.1524" layer="91"/>
<junction x="69.85" y="-99.06"/>
<pinref part="LED27" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="-101.6" x2="34.29" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="52.07" y1="-99.06" x2="34.29" y2="-99.06" width="0.1524" layer="91"/>
<junction x="52.07" y="-99.06"/>
<pinref part="LED26" gate="G$1" pin="5V"/>
<wire x1="16.51" y1="-101.6" x2="16.51" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="34.29" y1="-99.06" x2="16.51" y2="-99.06" width="0.1524" layer="91"/>
<junction x="34.29" y="-99.06"/>
<wire x1="16.51" y1="-99.06" x2="0" y2="-99.06" width="0.1524" layer="91"/>
<junction x="16.51" y="-99.06"/>
<junction x="0" y="-99.06"/>
<pinref part="LED35" gate="G$1" pin="5V"/>
<wire x1="87.63" y1="-124.46" x2="87.63" y2="-127" width="0.1524" layer="91"/>
<pinref part="LED34" gate="G$1" pin="5V"/>
<wire x1="69.85" y1="-127" x2="69.85" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="87.63" y1="-124.46" x2="69.85" y2="-124.46" width="0.1524" layer="91"/>
<pinref part="LED33" gate="G$1" pin="5V"/>
<wire x1="52.07" y1="-127" x2="52.07" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="69.85" y1="-124.46" x2="52.07" y2="-124.46" width="0.1524" layer="91"/>
<junction x="69.85" y="-124.46"/>
<pinref part="LED32" gate="G$1" pin="5V"/>
<wire x1="34.29" y1="-127" x2="34.29" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="52.07" y1="-124.46" x2="34.29" y2="-124.46" width="0.1524" layer="91"/>
<junction x="52.07" y="-124.46"/>
<pinref part="LED31" gate="G$1" pin="5V"/>
<wire x1="16.51" y1="-127" x2="16.51" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="34.29" y1="-124.46" x2="16.51" y2="-124.46" width="0.1524" layer="91"/>
<junction x="34.29" y="-124.46"/>
<wire x1="16.51" y1="-124.46" x2="0" y2="-124.46" width="0.1524" layer="91"/>
<junction x="16.51" y="-124.46"/>
<pinref part="LED45" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="2.54" x2="201.93" y2="0" width="0.1524" layer="91"/>
<pinref part="LED44" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="0" x2="184.15" y2="2.54" width="0.1524" layer="91"/>
<wire x1="184.15" y1="2.54" x2="201.93" y2="2.54" width="0.1524" layer="91"/>
<junction x="184.15" y="2.54"/>
<pinref part="LED43" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="0" x2="166.37" y2="2.54" width="0.1524" layer="91"/>
<wire x1="166.37" y1="2.54" x2="184.15" y2="2.54" width="0.1524" layer="91"/>
<junction x="166.37" y="2.54"/>
<pinref part="LED42" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="0" x2="148.59" y2="2.54" width="0.1524" layer="91"/>
<wire x1="148.59" y1="2.54" x2="166.37" y2="2.54" width="0.1524" layer="91"/>
<junction x="148.59" y="2.54"/>
<wire x1="130.81" y1="2.54" x2="148.59" y2="2.54" width="0.1524" layer="91"/>
<pinref part="LED41" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="0" x2="130.81" y2="2.54" width="0.1524" layer="91"/>
<wire x1="130.81" y1="2.54" x2="119.38" y2="2.54" width="0.1524" layer="91"/>
<junction x="130.81" y="2.54"/>
<junction x="119.38" y="2.54"/>
<pinref part="LED50" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="-22.86" x2="201.93" y2="-25.4" width="0.1524" layer="91"/>
<pinref part="LED49" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="-25.4" x2="184.15" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="201.93" y1="-22.86" x2="184.15" y2="-22.86" width="0.1524" layer="91"/>
<pinref part="LED48" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="-25.4" x2="166.37" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="184.15" y1="-22.86" x2="166.37" y2="-22.86" width="0.1524" layer="91"/>
<junction x="184.15" y="-22.86"/>
<pinref part="LED47" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="-25.4" x2="148.59" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="166.37" y1="-22.86" x2="148.59" y2="-22.86" width="0.1524" layer="91"/>
<junction x="166.37" y="-22.86"/>
<pinref part="LED46" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="-25.4" x2="130.81" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="148.59" y1="-22.86" x2="130.81" y2="-22.86" width="0.1524" layer="91"/>
<junction x="148.59" y="-22.86"/>
<wire x1="130.81" y1="-22.86" x2="119.38" y2="-22.86" width="0.1524" layer="91"/>
<junction x="130.81" y="-22.86"/>
<junction x="119.38" y="-22.86"/>
<pinref part="LED55" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="-48.26" x2="201.93" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="LED54" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="-50.8" x2="184.15" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="201.93" y1="-48.26" x2="184.15" y2="-48.26" width="0.1524" layer="91"/>
<pinref part="LED53" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="-50.8" x2="166.37" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="184.15" y1="-48.26" x2="166.37" y2="-48.26" width="0.1524" layer="91"/>
<junction x="184.15" y="-48.26"/>
<pinref part="LED52" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="-50.8" x2="148.59" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="166.37" y1="-48.26" x2="148.59" y2="-48.26" width="0.1524" layer="91"/>
<junction x="166.37" y="-48.26"/>
<pinref part="LED51" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="-50.8" x2="130.81" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="148.59" y1="-48.26" x2="130.81" y2="-48.26" width="0.1524" layer="91"/>
<junction x="148.59" y="-48.26"/>
<wire x1="130.81" y1="-48.26" x2="119.38" y2="-48.26" width="0.1524" layer="91"/>
<junction x="130.81" y="-48.26"/>
<junction x="119.38" y="-48.26"/>
<pinref part="LED60" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="-73.66" x2="201.93" y2="-76.2" width="0.1524" layer="91"/>
<pinref part="LED59" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="-76.2" x2="184.15" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="201.93" y1="-73.66" x2="184.15" y2="-73.66" width="0.1524" layer="91"/>
<pinref part="LED58" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="-76.2" x2="166.37" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="184.15" y1="-73.66" x2="166.37" y2="-73.66" width="0.1524" layer="91"/>
<junction x="184.15" y="-73.66"/>
<pinref part="LED57" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="-76.2" x2="148.59" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="166.37" y1="-73.66" x2="148.59" y2="-73.66" width="0.1524" layer="91"/>
<junction x="166.37" y="-73.66"/>
<pinref part="LED56" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="-76.2" x2="130.81" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="148.59" y1="-73.66" x2="130.81" y2="-73.66" width="0.1524" layer="91"/>
<junction x="148.59" y="-73.66"/>
<wire x1="130.81" y1="-73.66" x2="119.38" y2="-73.66" width="0.1524" layer="91"/>
<junction x="130.81" y="-73.66"/>
<junction x="119.38" y="-73.66"/>
<pinref part="LED65" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="-99.06" x2="201.93" y2="-101.6" width="0.1524" layer="91"/>
<pinref part="LED64" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="-101.6" x2="184.15" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="201.93" y1="-99.06" x2="184.15" y2="-99.06" width="0.1524" layer="91"/>
<pinref part="LED63" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="-101.6" x2="166.37" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="184.15" y1="-99.06" x2="166.37" y2="-99.06" width="0.1524" layer="91"/>
<junction x="184.15" y="-99.06"/>
<pinref part="LED62" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="-101.6" x2="148.59" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="166.37" y1="-99.06" x2="148.59" y2="-99.06" width="0.1524" layer="91"/>
<junction x="166.37" y="-99.06"/>
<pinref part="LED61" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="-101.6" x2="130.81" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="148.59" y1="-99.06" x2="130.81" y2="-99.06" width="0.1524" layer="91"/>
<junction x="148.59" y="-99.06"/>
<wire x1="130.81" y1="-99.06" x2="119.38" y2="-99.06" width="0.1524" layer="91"/>
<junction x="130.81" y="-99.06"/>
<junction x="119.38" y="-99.06"/>
<wire x1="215.9" y1="-154.94" x2="215.9" y2="-124.46" width="0.1524" layer="91"/>
<pinref part="JP2" gate="A" pin="3"/>
<wire x1="200.66" y1="-154.94" x2="215.9" y2="-154.94" width="0.1524" layer="91"/>
<pinref part="LED70" gate="G$1" pin="5V"/>
<wire x1="201.93" y1="-124.46" x2="201.93" y2="-127" width="0.1524" layer="91"/>
<wire x1="215.9" y1="-124.46" x2="201.93" y2="-124.46" width="0.1524" layer="91"/>
<pinref part="LED69" gate="G$1" pin="5V"/>
<wire x1="184.15" y1="-127" x2="184.15" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="201.93" y1="-124.46" x2="184.15" y2="-124.46" width="0.1524" layer="91"/>
<junction x="201.93" y="-124.46"/>
<pinref part="LED68" gate="G$1" pin="5V"/>
<wire x1="166.37" y1="-127" x2="166.37" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="184.15" y1="-124.46" x2="166.37" y2="-124.46" width="0.1524" layer="91"/>
<junction x="184.15" y="-124.46"/>
<pinref part="LED67" gate="G$1" pin="5V"/>
<wire x1="148.59" y1="-127" x2="148.59" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="166.37" y1="-124.46" x2="148.59" y2="-124.46" width="0.1524" layer="91"/>
<junction x="166.37" y="-124.46"/>
<pinref part="LED66" gate="G$1" pin="5V"/>
<wire x1="130.81" y1="-127" x2="130.81" y2="-124.46" width="0.1524" layer="91"/>
<wire x1="148.59" y1="-124.46" x2="130.81" y2="-124.46" width="0.1524" layer="91"/>
<junction x="148.59" y="-124.46"/>
<wire x1="130.81" y1="-124.46" x2="119.38" y2="-124.46" width="0.1524" layer="91"/>
<junction x="130.81" y="-124.46"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="LED18" gate="G$1" pin="DOUT"/>
<pinref part="LED19" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="-58.42" x2="55.88" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="LED18" gate="G$1" pin="DIN"/>
<pinref part="LED17" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="-58.42" x2="40.64" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="LED17" gate="G$1" pin="DIN"/>
<pinref part="LED16" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="-58.42" x2="22.86" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="LED19" gate="G$1" pin="DOUT"/>
<pinref part="LED20" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="-58.42" x2="73.66" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="LED16" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="-58.42" x2="5.08" y2="-58.42" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-33.02" x2="93.98" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-45.72" x2="2.54" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-45.72" x2="2.54" y2="-58.42" width="0.1524" layer="91"/>
<pinref part="LED15" gate="G$1" pin="DOUT"/>
<wire x1="91.44" y1="-33.02" x2="93.98" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="LED23" gate="G$1" pin="DOUT"/>
<pinref part="LED24" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="-83.82" x2="55.88" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="LED23" gate="G$1" pin="DIN"/>
<pinref part="LED22" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="-83.82" x2="40.64" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="LED22" gate="G$1" pin="DIN"/>
<pinref part="LED21" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="-83.82" x2="22.86" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="LED24" gate="G$1" pin="DOUT"/>
<pinref part="LED25" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="-83.82" x2="73.66" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="LED21" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="-83.82" x2="5.08" y2="-83.82" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-58.42" x2="93.98" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-71.12" x2="2.54" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-71.12" x2="2.54" y2="-83.82" width="0.1524" layer="91"/>
<pinref part="LED20" gate="G$1" pin="DOUT"/>
<wire x1="91.44" y1="-58.42" x2="93.98" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<wire x1="-2.54" y1="38.1" x2="-2.54" y2="7.62" width="0.1524" layer="91"/>
<pinref part="LED1" gate="G$1" pin="GND"/>
<wire x1="-2.54" y1="7.62" x2="12.7" y2="7.62" width="0.1524" layer="91"/>
<wire x1="12.7" y1="7.62" x2="12.7" y2="10.16" width="0.1524" layer="91"/>
<pinref part="LED2" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="10.16" x2="30.48" y2="7.62" width="0.1524" layer="91"/>
<wire x1="30.48" y1="7.62" x2="12.7" y2="7.62" width="0.1524" layer="91"/>
<junction x="12.7" y="7.62"/>
<pinref part="LED3" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="10.16" x2="48.26" y2="7.62" width="0.1524" layer="91"/>
<wire x1="48.26" y1="7.62" x2="30.48" y2="7.62" width="0.1524" layer="91"/>
<junction x="30.48" y="7.62"/>
<pinref part="LED4" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="10.16" x2="66.04" y2="7.62" width="0.1524" layer="91"/>
<wire x1="66.04" y1="7.62" x2="48.26" y2="7.62" width="0.1524" layer="91"/>
<junction x="48.26" y="7.62"/>
<pinref part="LED5" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="10.16" x2="83.82" y2="7.62" width="0.1524" layer="91"/>
<wire x1="83.82" y1="7.62" x2="66.04" y2="7.62" width="0.1524" layer="91"/>
<junction x="66.04" y="7.62"/>
<pinref part="JP1" gate="A" pin="2"/>
<wire x1="10.16" y1="38.1" x2="-2.54" y2="38.1" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-144.78" x2="-2.54" y2="-119.38" width="0.1524" layer="91"/>
<junction x="-2.54" y="7.62"/>
<label x="38.1" y="7.62" size="1.778" layer="95"/>
<pinref part="LED31" gate="G$1" pin="GND"/>
<wire x1="-2.54" y1="-119.38" x2="-2.54" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-93.98" x2="-2.54" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-68.58" x2="-2.54" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-43.18" x2="-2.54" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-17.78" x2="-2.54" y2="7.62" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="-144.78" x2="12.7" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="12.7" y1="-144.78" x2="12.7" y2="-142.24" width="0.1524" layer="91"/>
<pinref part="LED32" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-142.24" x2="30.48" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-144.78" x2="12.7" y2="-144.78" width="0.1524" layer="91"/>
<junction x="12.7" y="-144.78"/>
<pinref part="LED33" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="-142.24" x2="48.26" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-144.78" x2="30.48" y2="-144.78" width="0.1524" layer="91"/>
<junction x="30.48" y="-144.78"/>
<pinref part="LED34" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="-142.24" x2="66.04" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-144.78" x2="48.26" y2="-144.78" width="0.1524" layer="91"/>
<junction x="48.26" y="-144.78"/>
<pinref part="LED35" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="-142.24" x2="83.82" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="83.82" y1="-144.78" x2="66.04" y2="-144.78" width="0.1524" layer="91"/>
<junction x="66.04" y="-144.78"/>
<pinref part="LED66" gate="G$1" pin="GND"/>
<wire x1="114.3" y1="-144.78" x2="127" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="127" y1="-144.78" x2="127" y2="-142.24" width="0.1524" layer="91"/>
<pinref part="LED67" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="-142.24" x2="144.78" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="144.78" y1="-144.78" x2="127" y2="-144.78" width="0.1524" layer="91"/>
<junction x="127" y="-144.78"/>
<pinref part="LED68" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="-142.24" x2="162.56" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="162.56" y1="-144.78" x2="144.78" y2="-144.78" width="0.1524" layer="91"/>
<junction x="144.78" y="-144.78"/>
<pinref part="LED69" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="-142.24" x2="180.34" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="180.34" y1="-144.78" x2="162.56" y2="-144.78" width="0.1524" layer="91"/>
<junction x="162.56" y="-144.78"/>
<pinref part="LED70" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-142.24" x2="198.12" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="198.12" y1="-144.78" x2="180.34" y2="-144.78" width="0.1524" layer="91"/>
<junction x="180.34" y="-144.78"/>
<wire x1="114.3" y1="-144.78" x2="114.3" y2="-119.38" width="0.1524" layer="91"/>
<pinref part="JP2" gate="A" pin="2"/>
<wire x1="114.3" y1="-119.38" x2="114.3" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="114.3" y1="-93.98" x2="114.3" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="114.3" y1="-68.58" x2="114.3" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="114.3" y1="-43.18" x2="114.3" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="114.3" y1="-17.78" x2="114.3" y2="7.62" width="0.1524" layer="91"/>
<wire x1="200.66" y1="-157.48" x2="210.82" y2="-157.48" width="0.1524" layer="91"/>
<wire x1="210.82" y1="-157.48" x2="210.82" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="210.82" y1="-144.78" x2="198.12" y2="-144.78" width="0.1524" layer="91"/>
<junction x="198.12" y="-144.78"/>
<pinref part="LED36" gate="G$1" pin="GND"/>
<wire x1="127" y1="7.62" x2="127" y2="10.16" width="0.1524" layer="91"/>
<pinref part="LED37" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="10.16" x2="144.78" y2="7.62" width="0.1524" layer="91"/>
<pinref part="LED38" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="10.16" x2="162.56" y2="7.62" width="0.1524" layer="91"/>
<pinref part="LED39" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="10.16" x2="180.34" y2="7.62" width="0.1524" layer="91"/>
<pinref part="LED40" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="10.16" x2="198.12" y2="7.62" width="0.1524" layer="91"/>
<wire x1="198.12" y1="7.62" x2="180.34" y2="7.62" width="0.1524" layer="91"/>
<junction x="180.34" y="7.62"/>
<wire x1="180.34" y1="7.62" x2="162.56" y2="7.62" width="0.1524" layer="91"/>
<junction x="162.56" y="7.62"/>
<wire x1="162.56" y1="7.62" x2="144.78" y2="7.62" width="0.1524" layer="91"/>
<junction x="144.78" y="7.62"/>
<wire x1="144.78" y1="7.62" x2="127" y2="7.62" width="0.1524" layer="91"/>
<wire x1="127" y1="7.62" x2="114.3" y2="7.62" width="0.1524" layer="91"/>
<junction x="127" y="7.62"/>
<wire x1="114.3" y1="7.62" x2="83.82" y2="7.62" width="0.1524" layer="91"/>
<junction x="114.3" y="7.62"/>
<junction x="83.82" y="7.62"/>
<pinref part="LED61" gate="G$1" pin="GND"/>
<wire x1="127" y1="-119.38" x2="127" y2="-116.84" width="0.1524" layer="91"/>
<pinref part="LED62" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="-116.84" x2="144.78" y2="-119.38" width="0.1524" layer="91"/>
<pinref part="LED63" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="-116.84" x2="162.56" y2="-119.38" width="0.1524" layer="91"/>
<pinref part="LED64" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="-116.84" x2="180.34" y2="-119.38" width="0.1524" layer="91"/>
<pinref part="LED65" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-116.84" x2="198.12" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="198.12" y1="-119.38" x2="180.34" y2="-119.38" width="0.1524" layer="91"/>
<junction x="180.34" y="-119.38"/>
<wire x1="180.34" y1="-119.38" x2="162.56" y2="-119.38" width="0.1524" layer="91"/>
<junction x="162.56" y="-119.38"/>
<wire x1="162.56" y1="-119.38" x2="144.78" y2="-119.38" width="0.1524" layer="91"/>
<junction x="144.78" y="-119.38"/>
<wire x1="144.78" y1="-119.38" x2="127" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="127" y1="-119.38" x2="114.3" y2="-119.38" width="0.1524" layer="91"/>
<junction x="127" y="-119.38"/>
<junction x="114.3" y="-119.38"/>
<pinref part="LED41" gate="G$1" pin="GND"/>
<wire x1="127" y1="-17.78" x2="127" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="LED42" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="-15.24" x2="144.78" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="LED43" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="-15.24" x2="162.56" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="LED44" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="-15.24" x2="180.34" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="LED45" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-15.24" x2="198.12" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="198.12" y1="-17.78" x2="180.34" y2="-17.78" width="0.1524" layer="91"/>
<junction x="180.34" y="-17.78"/>
<wire x1="180.34" y1="-17.78" x2="162.56" y2="-17.78" width="0.1524" layer="91"/>
<junction x="162.56" y="-17.78"/>
<wire x1="162.56" y1="-17.78" x2="144.78" y2="-17.78" width="0.1524" layer="91"/>
<junction x="144.78" y="-17.78"/>
<wire x1="144.78" y1="-17.78" x2="127" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="127" y1="-17.78" x2="114.3" y2="-17.78" width="0.1524" layer="91"/>
<junction x="127" y="-17.78"/>
<junction x="114.3" y="-17.78"/>
<pinref part="LED46" gate="G$1" pin="GND"/>
<wire x1="127" y1="-43.18" x2="127" y2="-40.64" width="0.1524" layer="91"/>
<pinref part="LED47" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="-40.64" x2="144.78" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="LED48" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="-40.64" x2="162.56" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="LED49" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="-40.64" x2="180.34" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="LED50" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-40.64" x2="198.12" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="198.12" y1="-43.18" x2="180.34" y2="-43.18" width="0.1524" layer="91"/>
<junction x="180.34" y="-43.18"/>
<wire x1="180.34" y1="-43.18" x2="162.56" y2="-43.18" width="0.1524" layer="91"/>
<junction x="162.56" y="-43.18"/>
<wire x1="162.56" y1="-43.18" x2="144.78" y2="-43.18" width="0.1524" layer="91"/>
<junction x="144.78" y="-43.18"/>
<wire x1="144.78" y1="-43.18" x2="127" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="127" y1="-43.18" x2="114.3" y2="-43.18" width="0.1524" layer="91"/>
<junction x="127" y="-43.18"/>
<junction x="114.3" y="-43.18"/>
<pinref part="LED51" gate="G$1" pin="GND"/>
<wire x1="127" y1="-68.58" x2="127" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="LED52" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="-66.04" x2="144.78" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="LED53" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="-66.04" x2="162.56" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="LED54" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="-66.04" x2="180.34" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="LED55" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-66.04" x2="198.12" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="198.12" y1="-68.58" x2="180.34" y2="-68.58" width="0.1524" layer="91"/>
<junction x="180.34" y="-68.58"/>
<wire x1="180.34" y1="-68.58" x2="162.56" y2="-68.58" width="0.1524" layer="91"/>
<junction x="162.56" y="-68.58"/>
<wire x1="162.56" y1="-68.58" x2="144.78" y2="-68.58" width="0.1524" layer="91"/>
<junction x="144.78" y="-68.58"/>
<wire x1="144.78" y1="-68.58" x2="127" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="127" y1="-68.58" x2="114.3" y2="-68.58" width="0.1524" layer="91"/>
<junction x="127" y="-68.58"/>
<junction x="114.3" y="-68.58"/>
<pinref part="LED56" gate="G$1" pin="GND"/>
<wire x1="127" y1="-93.98" x2="127" y2="-91.44" width="0.1524" layer="91"/>
<pinref part="LED57" gate="G$1" pin="GND"/>
<wire x1="144.78" y1="-91.44" x2="144.78" y2="-93.98" width="0.1524" layer="91"/>
<pinref part="LED58" gate="G$1" pin="GND"/>
<wire x1="162.56" y1="-91.44" x2="162.56" y2="-93.98" width="0.1524" layer="91"/>
<pinref part="LED59" gate="G$1" pin="GND"/>
<wire x1="180.34" y1="-91.44" x2="180.34" y2="-93.98" width="0.1524" layer="91"/>
<pinref part="LED60" gate="G$1" pin="GND"/>
<wire x1="198.12" y1="-91.44" x2="198.12" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="198.12" y1="-93.98" x2="180.34" y2="-93.98" width="0.1524" layer="91"/>
<junction x="180.34" y="-93.98"/>
<wire x1="180.34" y1="-93.98" x2="162.56" y2="-93.98" width="0.1524" layer="91"/>
<junction x="162.56" y="-93.98"/>
<wire x1="162.56" y1="-93.98" x2="144.78" y2="-93.98" width="0.1524" layer="91"/>
<junction x="144.78" y="-93.98"/>
<wire x1="144.78" y1="-93.98" x2="127" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="127" y1="-93.98" x2="114.3" y2="-93.98" width="0.1524" layer="91"/>
<junction x="127" y="-93.98"/>
<junction x="114.3" y="-93.98"/>
<pinref part="LED26" gate="G$1" pin="GND"/>
<wire x1="12.7" y1="-119.38" x2="12.7" y2="-116.84" width="0.1524" layer="91"/>
<pinref part="LED27" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-116.84" x2="30.48" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-119.38" x2="12.7" y2="-119.38" width="0.1524" layer="91"/>
<junction x="30.48" y="-119.38"/>
<pinref part="LED28" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="-116.84" x2="48.26" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-119.38" x2="30.48" y2="-119.38" width="0.1524" layer="91"/>
<junction x="48.26" y="-119.38"/>
<pinref part="LED29" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="-116.84" x2="66.04" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-119.38" x2="48.26" y2="-119.38" width="0.1524" layer="91"/>
<junction x="66.04" y="-119.38"/>
<wire x1="83.82" y1="-119.38" x2="66.04" y2="-119.38" width="0.1524" layer="91"/>
<pinref part="LED30" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="-116.84" x2="83.82" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="12.7" y1="-119.38" x2="-2.54" y2="-119.38" width="0.1524" layer="91"/>
<junction x="12.7" y="-119.38"/>
<junction x="-2.54" y="-119.38"/>
<pinref part="LED21" gate="G$1" pin="GND"/>
<wire x1="12.7" y1="-93.98" x2="12.7" y2="-91.44" width="0.1524" layer="91"/>
<pinref part="LED22" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-91.44" x2="30.48" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-93.98" x2="12.7" y2="-93.98" width="0.1524" layer="91"/>
<junction x="30.48" y="-93.98"/>
<pinref part="LED23" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="-91.44" x2="48.26" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-93.98" x2="30.48" y2="-93.98" width="0.1524" layer="91"/>
<junction x="48.26" y="-93.98"/>
<pinref part="LED24" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="-91.44" x2="66.04" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="66.04" y1="-93.98" x2="48.26" y2="-93.98" width="0.1524" layer="91"/>
<junction x="66.04" y="-93.98"/>
<wire x1="83.82" y1="-93.98" x2="66.04" y2="-93.98" width="0.1524" layer="91"/>
<pinref part="LED25" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="-91.44" x2="83.82" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="12.7" y1="-93.98" x2="-2.54" y2="-93.98" width="0.1524" layer="91"/>
<junction x="12.7" y="-93.98"/>
<junction x="-2.54" y="-93.98"/>
<pinref part="LED16" gate="G$1" pin="GND"/>
<wire x1="12.7" y1="-68.58" x2="12.7" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="LED17" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-66.04" x2="30.48" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-68.58" x2="12.7" y2="-68.58" width="0.1524" layer="91"/>
<junction x="30.48" y="-68.58"/>
<pinref part="LED18" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="-66.04" x2="48.26" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-68.58" x2="30.48" y2="-68.58" width="0.1524" layer="91"/>
<junction x="48.26" y="-68.58"/>
<wire x1="66.04" y1="-68.58" x2="48.26" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="LED20" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="-66.04" x2="83.82" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="83.82" y1="-68.58" x2="66.04" y2="-68.58" width="0.1524" layer="91"/>
<junction x="66.04" y="-68.58"/>
<pinref part="LED19" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="-66.04" x2="66.04" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="12.7" y1="-68.58" x2="-2.54" y2="-68.58" width="0.1524" layer="91"/>
<junction x="12.7" y="-68.58"/>
<junction x="-2.54" y="-68.58"/>
<pinref part="LED11" gate="G$1" pin="GND"/>
<wire x1="12.7" y1="-43.18" x2="12.7" y2="-40.64" width="0.1524" layer="91"/>
<pinref part="LED12" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-40.64" x2="30.48" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-43.18" x2="12.7" y2="-43.18" width="0.1524" layer="91"/>
<junction x="30.48" y="-43.18"/>
<pinref part="LED13" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="-40.64" x2="48.26" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="48.26" y1="-43.18" x2="30.48" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="LED14" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="-40.64" x2="66.04" y2="-43.18" width="0.1524" layer="91"/>
<pinref part="LED15" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="-40.64" x2="83.82" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="83.82" y1="-43.18" x2="66.04" y2="-43.18" width="0.1524" layer="91"/>
<junction x="66.04" y="-43.18"/>
<wire x1="66.04" y1="-43.18" x2="48.26" y2="-43.18" width="0.1524" layer="91"/>
<junction x="48.26" y="-43.18"/>
<wire x1="12.7" y1="-43.18" x2="-2.54" y2="-43.18" width="0.1524" layer="91"/>
<junction x="12.7" y="-43.18"/>
<junction x="-2.54" y="-43.18"/>
<pinref part="LED6" gate="G$1" pin="GND"/>
<pinref part="LED7" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="-15.24" x2="30.48" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="LED8" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="-15.24" x2="48.26" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="LED9" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="-15.24" x2="66.04" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="LED10" gate="G$1" pin="GND"/>
<wire x1="83.82" y1="-15.24" x2="83.82" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="83.82" y1="-17.78" x2="66.04" y2="-17.78" width="0.1524" layer="91"/>
<junction x="66.04" y="-17.78"/>
<wire x1="66.04" y1="-17.78" x2="48.26" y2="-17.78" width="0.1524" layer="91"/>
<junction x="48.26" y="-17.78"/>
<wire x1="48.26" y1="-17.78" x2="30.48" y2="-17.78" width="0.1524" layer="91"/>
<junction x="30.48" y="-17.78"/>
<wire x1="30.48" y1="-17.78" x2="12.7" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="12.7" y1="-17.78" x2="12.7" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="12.7" y1="-17.78" x2="-2.54" y2="-17.78" width="0.1524" layer="91"/>
<junction x="12.7" y="-17.78"/>
<junction x="-2.54" y="-17.78"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="LED28" gate="G$1" pin="DOUT"/>
<pinref part="LED29" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="-109.22" x2="55.88" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="LED28" gate="G$1" pin="DIN"/>
<pinref part="LED27" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="-109.22" x2="40.64" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="LED27" gate="G$1" pin="DIN"/>
<pinref part="LED26" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="-109.22" x2="22.86" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="LED29" gate="G$1" pin="DOUT"/>
<pinref part="LED30" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="-109.22" x2="73.66" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$36" class="0">
<segment>
<pinref part="LED26" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="-109.22" x2="5.08" y2="-109.22" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-83.82" x2="93.98" y2="-96.52" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-96.52" x2="2.54" y2="-96.52" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-96.52" x2="2.54" y2="-109.22" width="0.1524" layer="91"/>
<pinref part="LED25" gate="G$1" pin="DOUT"/>
<wire x1="93.98" y1="-83.82" x2="91.44" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="LED33" gate="G$1" pin="DOUT"/>
<pinref part="LED34" gate="G$1" pin="DIN"/>
<wire x1="58.42" y1="-134.62" x2="55.88" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="LED33" gate="G$1" pin="DIN"/>
<pinref part="LED32" gate="G$1" pin="DOUT"/>
<wire x1="38.1" y1="-134.62" x2="40.64" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="LED32" gate="G$1" pin="DIN"/>
<pinref part="LED31" gate="G$1" pin="DOUT"/>
<wire x1="20.32" y1="-134.62" x2="22.86" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="LED34" gate="G$1" pin="DOUT"/>
<pinref part="LED35" gate="G$1" pin="DIN"/>
<wire x1="76.2" y1="-134.62" x2="73.66" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$43" class="0">
<segment>
<pinref part="LED31" gate="G$1" pin="DIN"/>
<wire x1="2.54" y1="-134.62" x2="5.08" y2="-134.62" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-109.22" x2="93.98" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="93.98" y1="-121.92" x2="2.54" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-121.92" x2="2.54" y2="-134.62" width="0.1524" layer="91"/>
<pinref part="LED30" gate="G$1" pin="DOUT"/>
<wire x1="91.44" y1="-109.22" x2="93.98" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$45" class="0">
<segment>
<pinref part="LED38" gate="G$1" pin="DOUT"/>
<pinref part="LED39" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="17.78" x2="170.18" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="LED38" gate="G$1" pin="DIN"/>
<pinref part="LED37" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="17.78" x2="154.94" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<pinref part="LED37" gate="G$1" pin="DIN"/>
<pinref part="LED36" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="17.78" x2="137.16" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$48" class="0">
<segment>
<pinref part="LED39" gate="G$1" pin="DOUT"/>
<pinref part="LED40" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="17.78" x2="187.96" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$49" class="0">
<segment>
<pinref part="LED36" gate="G$1" pin="DIN"/>
<pinref part="LED35" gate="G$1" pin="DOUT"/>
<wire x1="91.44" y1="-134.62" x2="99.06" y2="-134.62" width="0.1524" layer="91"/>
<wire x1="99.06" y1="-134.62" x2="99.06" y2="17.78" width="0.1524" layer="91"/>
<wire x1="99.06" y1="17.78" x2="119.38" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$51" class="0">
<segment>
<pinref part="LED43" gate="G$1" pin="DOUT"/>
<pinref part="LED44" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="-7.62" x2="170.18" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$52" class="0">
<segment>
<pinref part="LED43" gate="G$1" pin="DIN"/>
<pinref part="LED42" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="-7.62" x2="154.94" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$53" class="0">
<segment>
<pinref part="LED42" gate="G$1" pin="DIN"/>
<pinref part="LED41" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="-7.62" x2="137.16" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$54" class="0">
<segment>
<pinref part="LED44" gate="G$1" pin="DOUT"/>
<pinref part="LED45" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="-7.62" x2="187.96" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$55" class="0">
<segment>
<pinref part="LED41" gate="G$1" pin="DIN"/>
<wire x1="116.84" y1="-7.62" x2="119.38" y2="-7.62" width="0.1524" layer="91"/>
<wire x1="208.28" y1="17.78" x2="208.28" y2="5.08" width="0.1524" layer="91"/>
<wire x1="208.28" y1="5.08" x2="116.84" y2="5.08" width="0.1524" layer="91"/>
<wire x1="116.84" y1="5.08" x2="116.84" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="LED40" gate="G$1" pin="DOUT"/>
<wire x1="208.28" y1="17.78" x2="205.74" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$58" class="0">
<segment>
<pinref part="LED48" gate="G$1" pin="DOUT"/>
<pinref part="LED49" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="-33.02" x2="170.18" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$59" class="0">
<segment>
<pinref part="LED48" gate="G$1" pin="DIN"/>
<pinref part="LED47" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="-33.02" x2="154.94" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$60" class="0">
<segment>
<pinref part="LED47" gate="G$1" pin="DIN"/>
<pinref part="LED46" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="-33.02" x2="137.16" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$61" class="0">
<segment>
<pinref part="LED49" gate="G$1" pin="DOUT"/>
<pinref part="LED50" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="-33.02" x2="187.96" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$62" class="0">
<segment>
<pinref part="LED46" gate="G$1" pin="DIN"/>
<wire x1="116.84" y1="-33.02" x2="119.38" y2="-33.02" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-7.62" x2="208.28" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-20.32" x2="116.84" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-20.32" x2="116.84" y2="-33.02" width="0.1524" layer="91"/>
<pinref part="LED45" gate="G$1" pin="DOUT"/>
<wire x1="205.74" y1="-7.62" x2="208.28" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$65" class="0">
<segment>
<pinref part="LED53" gate="G$1" pin="DOUT"/>
<pinref part="LED54" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="-58.42" x2="170.18" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$66" class="0">
<segment>
<pinref part="LED53" gate="G$1" pin="DIN"/>
<pinref part="LED52" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="-58.42" x2="154.94" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$67" class="0">
<segment>
<pinref part="LED52" gate="G$1" pin="DIN"/>
<pinref part="LED51" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="-58.42" x2="137.16" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$68" class="0">
<segment>
<pinref part="LED54" gate="G$1" pin="DOUT"/>
<pinref part="LED55" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="-58.42" x2="187.96" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$69" class="0">
<segment>
<pinref part="LED51" gate="G$1" pin="DIN"/>
<wire x1="116.84" y1="-58.42" x2="119.38" y2="-58.42" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-33.02" x2="208.28" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-45.72" x2="116.84" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-45.72" x2="116.84" y2="-58.42" width="0.1524" layer="91"/>
<pinref part="LED50" gate="G$1" pin="DOUT"/>
<wire x1="205.74" y1="-33.02" x2="208.28" y2="-33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$72" class="0">
<segment>
<pinref part="LED58" gate="G$1" pin="DOUT"/>
<pinref part="LED59" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="-83.82" x2="170.18" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$73" class="0">
<segment>
<pinref part="LED58" gate="G$1" pin="DIN"/>
<pinref part="LED57" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="-83.82" x2="154.94" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$74" class="0">
<segment>
<pinref part="LED57" gate="G$1" pin="DIN"/>
<pinref part="LED56" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="-83.82" x2="137.16" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$75" class="0">
<segment>
<pinref part="LED59" gate="G$1" pin="DOUT"/>
<pinref part="LED60" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="-83.82" x2="187.96" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$76" class="0">
<segment>
<pinref part="LED56" gate="G$1" pin="DIN"/>
<wire x1="116.84" y1="-83.82" x2="119.38" y2="-83.82" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-58.42" x2="208.28" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-71.12" x2="116.84" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-71.12" x2="116.84" y2="-83.82" width="0.1524" layer="91"/>
<pinref part="LED55" gate="G$1" pin="DOUT"/>
<wire x1="208.28" y1="-58.42" x2="205.74" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$79" class="0">
<segment>
<pinref part="LED63" gate="G$1" pin="DOUT"/>
<pinref part="LED64" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="-109.22" x2="170.18" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$80" class="0">
<segment>
<pinref part="LED63" gate="G$1" pin="DIN"/>
<pinref part="LED62" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="-109.22" x2="154.94" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$81" class="0">
<segment>
<pinref part="LED62" gate="G$1" pin="DIN"/>
<pinref part="LED61" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="-109.22" x2="137.16" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$82" class="0">
<segment>
<pinref part="LED64" gate="G$1" pin="DOUT"/>
<pinref part="LED65" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="-109.22" x2="187.96" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$83" class="0">
<segment>
<pinref part="LED61" gate="G$1" pin="DIN"/>
<wire x1="116.84" y1="-109.22" x2="119.38" y2="-109.22" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-83.82" x2="208.28" y2="-96.52" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-96.52" x2="116.84" y2="-96.52" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-96.52" x2="116.84" y2="-109.22" width="0.1524" layer="91"/>
<pinref part="LED60" gate="G$1" pin="DOUT"/>
<wire x1="205.74" y1="-83.82" x2="208.28" y2="-83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$86" class="0">
<segment>
<pinref part="LED68" gate="G$1" pin="DOUT"/>
<pinref part="LED69" gate="G$1" pin="DIN"/>
<wire x1="172.72" y1="-134.62" x2="170.18" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$87" class="0">
<segment>
<pinref part="LED68" gate="G$1" pin="DIN"/>
<pinref part="LED67" gate="G$1" pin="DOUT"/>
<wire x1="152.4" y1="-134.62" x2="154.94" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$88" class="0">
<segment>
<pinref part="LED67" gate="G$1" pin="DIN"/>
<pinref part="LED66" gate="G$1" pin="DOUT"/>
<wire x1="134.62" y1="-134.62" x2="137.16" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$89" class="0">
<segment>
<pinref part="LED69" gate="G$1" pin="DOUT"/>
<pinref part="LED70" gate="G$1" pin="DIN"/>
<wire x1="190.5" y1="-134.62" x2="187.96" y2="-134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$90" class="0">
<segment>
<pinref part="LED66" gate="G$1" pin="DIN"/>
<wire x1="116.84" y1="-134.62" x2="119.38" y2="-134.62" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-109.22" x2="208.28" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="208.28" y1="-121.92" x2="116.84" y2="-121.92" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-121.92" x2="116.84" y2="-134.62" width="0.1524" layer="91"/>
<pinref part="LED65" gate="G$1" pin="DOUT"/>
<wire x1="208.28" y1="-109.22" x2="205.74" y2="-109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DOUT" class="0">
<segment>
<pinref part="LED70" gate="G$1" pin="DOUT"/>
<wire x1="205.74" y1="-134.62" x2="213.36" y2="-134.62" width="0.1524" layer="91"/>
<wire x1="213.36" y1="-134.62" x2="213.36" y2="-160.02" width="0.1524" layer="91"/>
<pinref part="JP2" gate="A" pin="1"/>
<wire x1="213.36" y1="-160.02" x2="200.66" y2="-160.02" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
