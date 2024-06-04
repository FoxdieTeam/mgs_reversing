# mgs_reversing

This project aims to completely reverse engineer *Metal Gear Solid Integral* for PlayStation back to C source code which when compiled produces the same assembly code.

At this moment `SLPM_862.47`/`SLPM_862.48`/`SLPM_862.49` main executables are 100% decompiled. However, even though this is a substantial milestone, a significant amount of work
is still left to decompile [overlays](#Overlays) - making it possible to boot into every game level and clean up already decompiled code.

The repository builds or aims to build the following artifacts:

### Main executables

<table>
    <tbody>
        <tr>
            <td colspan=2 align=center><b><code>SLPM_862.47</code> (main executable)</b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td><b>✔️ 100% decompiled!</b> The next goals for this artifact are to clean up the decompiled code, find cleaner matches and make it shiftable.</td>
        </tr>
        <tr>
            <td><b>Size</b></td>
            <td>626 KB</td>
        </tr>
        <tr>
            <td><b>SHA256</b></td>
            <td><code>4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f</code></td>
        </tr>
        <tr>
            <td><b>Building</b></td>
            <td><code>python build.py</code></td>
        </tr>
        <tr>
            <td colspan=2 align=center><b><code>SLPM_862.48</code> (main executable)</b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td rowspan=4><b>✔️ 100% decompiled!</b> Identical to <code>SLPM_862.47</code> (main executable).</td>
        </tr>
        <tr>
            <td><b>Size</b></td>
        </tr>
        <tr>
            <td><b>SHA256</b></td>
        </tr>
        <tr>
            <td><b>Building</b></td>
        </tr>
        <tr>
            <td colspan=2 align=center><b><code>SLPM_862.49</code> (main executable)</b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td><b>✔️ 100% decompiled!</b> This executable is based on <code>SLPM_862.47</code> (main executable), but with many small changes, especially around <code>chara/snake_vr</code> (a variant of Snake actor).</td>
        </tr>
        <tr>
            <td><b>Size</b></td>
            <td>616 KB</td>
        </tr>
        <tr>
            <td><b>SHA256</b></td>
            <td><code>c370f8e41ec8fb78238bfe2ddbfc25a6d37ec8f0972c86ebfde075ecd4ee8dca</code></td>
        </tr>
        <tr>
            <td><b>Building</b></td>
            <td><code>python build.py --variant=vr_exe</code></td>
        </tr>
    </tbody>
</table>

### Overlays

*Metal Gear Solid Integral* dynamically loads additional per-stage executable code that is required to play a particular stage of the game. The main executable contains the game engine, as well as the most common actors used throughout the stages.

<table>
    <tbody>
        <tr>
            <td colspan=2 align=center><b>Overlays on <code>SLPM-86247</code></b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>🚧 Work in progress.
<br><br>
Individual overlay progress:
<details>
<summary>Click to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
            <td><b>abst</b></td>
            <td>46 KB</td>
            <td>Abstract (Save/Load Menu)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>brf</b></td>
            <td>125 KB</td>
            <td>Briefing</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>camera</b></td>
            <td>54 KB</td>
            <td>JPEG Photo Menu</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>change</b></td>
            <td>12 KB</td>
            <td>Disc Change</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d00a</b></td>
            <td>122 KB</td>
            <td>Loading Dock (Cutscene)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d01a</b></td>
            <td>57 KB</td>
            <td>Heliport (Cutscene)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d03a</b></td>
            <td>18 KB</td>
            <td>Holding Cell (Cutscene)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d11c</b></td>
            <td>14 KB</td>
            <td>Communication Tower B (Cutscene)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d16e</b></td>
            <td>65 KB</td>
            <td>Underground Base (Cutscene)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d18a</b></td>
            <td>96 KB</td>
            <td>Supply Route (Cutscene)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>d18ar</b></td>
            <td>96 KB</td>
            <td>Supply Route (Cutscene) (RED)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>demosel</b></td>
            <td>16 KB</td>
            <td>Demo Theater</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>ending</b></td>
            <td>40 KB</td>
            <td>Ending Demo (SCENE 28-1)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>endingr</b></td>
            <td>40 KB</td>
            <td>Ending Demo (SCENE 28-1) (RED)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>opening</b></td>
            <td>42 KB</td>
            <td>Opening Demo (SCENE 01-1)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>option</b></td>
            <td>26 KB</td>
            <td>Options Menu</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>preope</b></td>
            <td>25 KB</td>
            <td>Previous Operations</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>rank</b></td>
            <td>139 KB</td>
            <td>Ranking Screen</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>roll</b></td>
            <td>39 KB</td>
            <td>Staff Roll</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s00a</b></td>
            <td>120 KB</td>
            <td>Loading Dock</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s01a</b></td>
            <td>137 KB</td>
            <td>Heliport</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s02a</b></td>
            <td>130 KB</td>
            <td>Tank Hangar</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s02b</b></td>
            <td>129 KB</td>
            <td>Tank Hangar</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s02c</b></td>
            <td>132 KB</td>
            <td>Tank Hangar (Before Contacting Meryl)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s02d</b></td>
            <td>126 KB</td>
            <td>Tank Hangar (After Contacting Meryl)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s02e</b></td>
            <td>132 KB</td>
            <td>Tank Hangar (After Torture)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03a</b></td>
            <td>75 KB</td>
            <td>Holding Cell</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03ar</b></td>
            <td>75 KB</td>
            <td>Holding Cell (RED)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03b</b></td>
            <td>66 KB</td>
            <td>Medical Room</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03c</b></td>
            <td>84 KB</td>
            <td>Medical Room</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03d</b></td>
            <td>101 KB</td>
            <td>Holding Cell</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s03dr</b></td>
            <td>101 KB</td>
            <td>Holding Cell (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s03e</b></td>
            <td>38 KB</td>
            <td>Holding Cell (vs. Soldiers)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03er</b></td>
            <td>38 KB</td>
            <td>Holding Cell (vs. Soldiers) (RED)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s04a</b></td>
            <td>94 KB</td>
            <td>Armory</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s04b</b></td>
            <td>116 KB</td>
            <td>Armory South (vs. Ocelot)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s04br</b></td>
            <td>116 KB</td>
            <td>Armory South (vs. Ocelot) (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s04c</b></td>
            <td>100 KB</td>
            <td>Armory South</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s05a</b></td>
            <td>130 KB</td>
            <td>Canyon</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s06a</b></td>
            <td>127 KB</td>
            <td>Warhead Storage Building 1F</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s07a</b></td>
            <td>130 KB</td>
            <td>Warhead Storage Building B1</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s07b</b></td>
            <td>141 KB</td>
            <td>Commander's Room</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s07br</b></td>
            <td>141 KB</td>
            <td>Commander's Room (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s07c</b></td>
            <td>73 KB</td>
            <td>Warhead Storage Building B1</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s07cr</b></td>
            <td>73 KB</td>
            <td>Warhead Storage Building B1 (RED)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s08a</b></td>
            <td>86 KB</td>
            <td>Warhead Storage Building B2</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s08b</b></td>
            <td>133 KB</td>
            <td>Laboratory</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s08br</b></td>
            <td>133 KB</td>
            <td>Laboratory (RED)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s08c</b></td>
            <td>60 KB</td>
            <td>Corridor</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s08cr</b></td>
            <td>60 KB</td>
            <td>Corridor (RED)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s09a</b></td>
            <td>121 KB</td>
            <td>Caves</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s09ar</b></td>
            <td>121 KB</td>
            <td>Caves (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s10a</b></td>
            <td>135 KB</td>
            <td>Underground Passage</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s10ar</b></td>
            <td>135 KB</td>
            <td>Underground Passage (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11a</b></td>
            <td>87 KB</td>
            <td>Communication Tower A</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11b</b></td>
            <td>97 KB</td>
            <td>Communication Tower Roof</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11c</b></td>
            <td>65 KB</td>
            <td>Communication Tower B</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s11d</b></td>
            <td>60 KB</td>
            <td>Communication Tower A Wall</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s11e</b></td>
            <td>113 KB</td>
            <td>Communication Tower B Elevator</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s11g</b></td>
            <td>105 KB</td>
            <td>Communication Tower B Roof</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s11h</b></td>
            <td>97 KB</td>
            <td>Communication Tower B Roof (vs. Hind D)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11i</b></td>
            <td>75 KB</td>
            <td>Communication Tower Walkway</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s12a</b></td>
            <td>107 KB</td>
            <td>Snowfield</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s12b</b></td>
            <td>96 KB</td>
            <td>Snowfield (After vs. Sniper Wolf)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s12c</b></td>
            <td>95 KB</td>
            <td>Snowfield (After vs. Sniper Wolf)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s13a</b></td>
            <td>130 KB</td>
            <td>Blast Furnace</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s14e</b></td>
            <td>108 KB</td>
            <td>Cargo Elevator</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s15a</b></td>
            <td>89 KB</td>
            <td>Warehouse</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s15b</b></td>
            <td>38 KB</td>
            <td>Warehouse North</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s15c</b></td>
            <td>129 KB</td>
            <td>Warehouse</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s16a</b></td>
            <td>63 KB</td>
            <td>Underground Base (1F)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s16b</b></td>
            <td>10 KB</td>
            <td>Underground Base (2F)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s16c</b></td>
            <td>109 KB</td>
            <td>Underground Base (3F)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s16d</b></td>
            <td>121 KB</td>
            <td>Underground Base (Control Room)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s17a</b></td>
            <td>140 KB</td>
            <td>Supply Route (vs. REX)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s17ar</b></td>
            <td>140 KB</td>
            <td>Supply Route (vs. REX) (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s18a</b></td>
            <td>133 KB</td>
            <td>Supply Route (vs. Liquid)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s18ar</b></td>
            <td>133 KB</td>
            <td>Supply Route (vs. Liquid) (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19a</b></td>
            <td>120 KB</td>
            <td>Escape Route (Garage)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19ar</b></td>
            <td>120 KB</td>
            <td>Escape Route (Garage) (RED)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19b</b></td>
            <td>110 KB</td>
            <td>Escape Route (Tunnel)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s19br</b></td>
            <td>110 KB</td>
            <td>Escape Route (Tunnel) (RED)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s20a</b></td>
            <td>30 KB</td>
            <td>Ending Demo (SCENE 28-1)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s20ar</b></td>
            <td>30 KB</td>
            <td>Ending Demo (SCENE 28-1) (RED)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select</b></td>
            <td>8 KB</td>
            <td>Debug Menu</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select1</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select (s00a-s04c)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select2</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select (s05a-s09a)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select3</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select (s10a-s14e)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select4</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select (s15a-s20a)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>selectd</b></td>
            <td>721 B</td>
            <td>Debug Menu Demo Select</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>sound</b></td>
            <td>1 KB</td>
            <td>Debug Menu Sound Test</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>title</b></td>
            <td>89 KB</td>
            <td>Title Screen</td>
            <td>🚧 Work in progress</td>
        </tr>
        </tbody>
    </table>
</details>
Individual overlay SHA256:
<details>
<summary>Click to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
            <td><b>abst.bin</b></td>
            <td><code>aed6a6145201850156d251618561487456e1b02d7ce26a40cf1e492b6fa30ec0</code></td>
        </tr>
        <tr>
            <td><b>brf.bin</b></td>
            <td><code>95f948d72f4b2dd523c3f60b3e036db2971c5f00b3f69d7dc9b4744c48996286</code></td>
        </tr>
        <tr>
            <td><b>camera.bin</b></td>
            <td><code>7e1738af3c3987b5461773cf865da803bac48820000e0e916307f29fa836f388</code></td>
        </tr>
        <tr>
            <td><b>change.bin</b></td>
            <td><code>d2f0afa4861278774ecc818c19e31420e3b05e96da4313ea048451bfabf780e5</code></td>
        </tr>
        <tr>
            <td><b>d00a.bin</b></td>
            <td><code>3dd07b291d5bc6b58a028d012b744d9d2c8023f143474467b0259e5a5603ad0a</code></td>
        </tr>
        <tr>
            <td><b>d01a.bin</b></td>
            <td><code>3a8d292f250a80b708a06f3fd41ee0e6b74733390084ef5b163108ba5c8af4a1</code></td>
        </tr>
        <tr>
            <td><b>d03a.bin</b></td>
            <td><code>3f3b4350dc263a088c70fa7518844ba8e5ec95a3f705ffbc5a37e6b5ff18f8b1</code></td>
        </tr>
        <tr>
            <td><b>d11c.bin</b></td>
            <td><code>86edb16ecdb7319d0ad133687228a808170a50ce36f393c96678f8379c48c746</code></td>
        </tr>
        <tr>
            <td><b>d16e.bin</b></td>
            <td><code>bf5ab697b6d0415ba63b9aa3aaba28f387f324cd2f1b32eb46f5d3cb253e48ef</code></td>
        </tr>
        <tr>
            <td><b>d18a.bin</b></td>
            <td><code>c388e19be2811a05075a0da664b5b4264040ecd7e2f6eb6cd761d8e579c35103</code></td>
        </tr>
        <tr>
            <td><b>d18ar.bin</b></td>
            <td><code>df7d5353a7b3be3d6d0f2550179181de27538c41b65b900c7f4a90068ee9d18a</code></td>
        </tr>
        <tr>
            <td><b>demosel.bin</b></td>
            <td><code>bbf6a776efcc2631b982f920f2c9247c8b215dd7a1358b3b9f9d76484f7d43d9</code></td>
        </tr>
        <tr>
            <td><b>ending.bin</b></td>
            <td><code>321c325577bb05cf68bec689083cbc9f7fc4d0b634776c1e6cad1f464ffb1da3</code></td>
        </tr>
        <tr>
            <td><b>endingr.bin</b></td>
            <td><code>c8eabac0fa0bde6d7bbbdba97a4b8948c3e6a0c839d2b438705345c392b43c35</code></td>
        </tr>
        <tr>
            <td><b>opening.bin</b></td>
            <td><code>87a5e822f5b428376ad36fcd28ebc56f661cf340f0ea059f11489b5f24e85545</code></td>
        </tr>
        <tr>
            <td><b>option.bin</b></td>
            <td><code>19e897b855f2e197e62160a8a409d2ff57a6b8588b831722fab9c3aaca324ea0</code></td>
        </tr>
        <tr>
            <td><b>preope.bin</b></td>
            <td><code>3176b630b8a3f9d8cb01ed833d78fbe654054a576c1f2da0ed91007dd71bd136</code></td>
        </tr>
        <tr>
            <td><b>rank.bin</b></td>
            <td><code>6a5ed242f966a4c60bba7daf9a2ba1c37482825d0786e1d77476e135030753f5</code></td>
        </tr>
        <tr>
            <td><b>roll.bin</b></td>
            <td><code>dfe3ca728b6e409613ef7a3dc11b48ecaa236d8ba6cd0951ce4321329842beae</code></td>
        </tr>
        <tr>
            <td><b>s00a.bin</b></td>
            <td><code>533cb8e9b6ffdcc442c25ba51eb3d83e90cb1ad2831d3870395333398c8402bc</code></td>
        </tr>
        <tr>
            <td><b>s01a.bin</b></td>
            <td><code>534f8365ad37dbb5c4753bd1720517fa4d1a92e9008597064e6b30a23dc00a75</code></td>
        </tr>
        <tr>
            <td><b>s02a.bin</b></td>
            <td><code>ece10d39e1d5bafee5acb4dd970bf83801128b04e4fb24ad31756e5bb4ca754d</code></td>
        </tr>
        <tr>
            <td><b>s02b.bin</b></td>
            <td><code>57a66e93a2028e3fb805c97c585fb6cfb5fe76c93fc4b8495ccdb2c03a1de308</code></td>
        </tr>
        <tr>
            <td><b>s02c.bin</b></td>
            <td><code>7c0b12187840f60405970364a1f7c73ec96be32c1130b3f9a87ec58f6ea46915</code></td>
        </tr>
        <tr>
            <td><b>s02d.bin</b></td>
            <td><code>5fe851426faf64733c1077998f9463b5455c766d3e27c9cdceed38ac338e8542</code></td>
        </tr>
        <tr>
            <td><b>s02e.bin</b></td>
            <td><code>cd79cd79a00e18bd5d323b0b8e153b4e8fe5548b6e0ea68f36d13f190eca0477</code></td>
        </tr>
        <tr>
            <td><b>s03a.bin</b></td>
            <td><code>c42bba970bdc968ee48b572efb03c41f15869cfc00d6aa0d7c8106487534f580</code></td>
        </tr>
        <tr>
            <td><b>s03ar.bin</b></td>
            <td><code>f34b46313625005b6aef5006b184556c4dd8f13e97a3b0c346f0f4fc7b9fbf04</code></td>
        </tr>
        <tr>
            <td><b>s03b.bin</b></td>
            <td><code>cd728e144c960e7419d389c81802d3de73c00a2f31e9bfd7eea33ed3ed2be083</code></td>
        </tr>
        <tr>
            <td><b>s03c.bin</b></td>
            <td><code>cc3b95638684f6f0a6cbcf9b0436fbc7b545ca0eeb0e6e60d6c4d0646dbc7fb4</code></td>
        </tr>
        <tr>
            <td><b>s03d.bin</b></td>
            <td><code>f9fa0f39352d3305b5cb2bd6c292297d4f351387b0038a27ccec29f42150d903</code></td>
        </tr>
        <tr>
            <td><b>s03dr.bin</b></td>
            <td><code>fa785a857655809ccf984d8c8ada626addbadfd11db31b34ef496ddce225ade1</code></td>
        </tr>
        <tr>
            <td><b>s03e.bin</b></td>
            <td><code>af0e15b223431977c2ad233596c37a51c0367da6470c1b760d3f211eb82e894c</code></td>
        </tr>
        <tr>
            <td><b>s03er.bin</b></td>
            <td><code>b1e60c25c0ee92e8c347b7f6a51b2e3fdb10d9ea33a2a77e1acbd8bfc7367114</code></td>
        </tr>
        <tr>
            <td><b>s04a.bin</b></td>
            <td><code>59b541a13b987478d6717643c3c146018b070fe374ffae0eaaf3f9a8bdc2ffb6</code></td>
        </tr>
        <tr>
            <td><b>s04b.bin</b></td>
            <td><code>bca0c362260565051a8d41ffc49d3b9ae84d1bc9dc758164ea019cae82de7fa7</code></td>
        </tr>
        <tr>
            <td><b>s04br.bin</b></td>
            <td><code>3ceb35994af2c7da7955ab356cbbb7471c749ff6788ecdfbffab1c5679bb4f9b</code></td>
        </tr>
        <tr>
            <td><b>s04c.bin</b></td>
            <td><code>5e6bc0c9b13f009c69c2ebdfb401fe9d55a6cd6ee8610cbdd95ee9f3dd71f32a</code></td>
        </tr>
        <tr>
            <td><b>s05a.bin</b></td>
            <td><code>fd08923d1e1ad01b8638f7e8f4a101e270a5f399f3d1afed47abca7532a8c081</code></td>
        </tr>
        <tr>
            <td><b>s06a.bin</b></td>
            <td><code>766d25f927a1116d565f97479786a42b93a275398310f775304668ec191a47e7</code></td>
        </tr>
        <tr>
            <td><b>s07a.bin</b></td>
            <td><code>20cb960a5d97e0b60c030ed0c17eea78bf6d7e0f5dc50945828e8c2106612546</code></td>
        </tr>
        <tr>
            <td><b>s07b.bin</b></td>
            <td><code>bbe527b3883ad7c41e4999a8b1d49e64265100b7d8ff6a7724e3fce5d6fb7328</code></td>
        </tr>
        <tr>
            <td><b>s07br.bin</b></td>
            <td><code>04007a426525216049196b550e22fc0e922c75f78c6fcfc4b469f9d5defbbc47</code></td>
        </tr>
        <tr>
            <td><b>s07c.bin</b></td>
            <td><code>03904064a3d2d2bcd83f719cf7de0d780886ebeae5645dcc7e345acd7fe8cba1</code></td>
        </tr>
        <tr>
            <td><b>s07cr.bin</b></td>
            <td><code>e3c3503599693be3d3729e0bfc09d364de85b46520eff3909b822a14a7dadfbd</code></td>
        </tr>
        <tr>
            <td><b>s08a.bin</b></td>
            <td><code>56a0d3aa551dd6eefda902497c3f0a90c458b4ab0a54b9a63b7fe3298606d4c9</code></td>
        </tr>
        <tr>
            <td><b>s08b.bin</b></td>
            <td><code>21c5534dd17e5579404b2b0b2f3c47fb324b27a363a108669e3818a3dee15ded</code></td>
        </tr>
        <tr>
            <td><b>s08br.bin</b></td>
            <td><code>064e8dbb2af7589a7122f02a51e202d43fd3e9bf05aa18258c5cd88621a2d69c</code></td>
        </tr>
        <tr>
            <td><b>s08c.bin</b></td>
            <td><code>5badd1f304a57a3e55af6d5fe15694c51398c602779a31ee2b7276ad9f9aafbb</code></td>
        </tr>
        <tr>
            <td><b>s08cr.bin</b></td>
            <td><code>1521588d917c0558839f915191ed5b643fba37a7d1fa4dc228951b433e1070c9</code></td>
        </tr>
        <tr>
            <td><b>s09a.bin</b></td>
            <td><code>4c698b375890c793c3622d410bffab7db48c01cfff393f458cd5712e316a7177</code></td>
        </tr>
        <tr>
            <td><b>s09ar.bin</b></td>
            <td><code>362fbe4c139197907498e38a1f56e403fe39b4a0217d34bfcf49cf86e86cb76b</code></td>
        </tr>
        <tr>
            <td><b>s10a.bin</b></td>
            <td><code>95f9cb0d5def5f30bb2133c0452b3aa49438f56c95535178d61eb11a03bb2e6e</code></td>
        </tr>
        <tr>
            <td><b>s10ar.bin</b></td>
            <td><code>465959ab31568740a4bf30bf0958865e485e48538e449a6b3c696c5fd7d52f69</code></td>
        </tr>
        <tr>
            <td><b>s11a.bin</b></td>
            <td><code>70be6cf00267ed663e29ce6b9598396e8fb7c60024b76ff86508244c56d39bf6</code></td>
        </tr>
        <tr>
            <td><b>s11b.bin</b></td>
            <td><code>280920ec9559d0c836bab8995de902f227759bb7430025a650f7c20633889f51</code></td>
        </tr>
        <tr>
            <td><b>s11c.bin</b></td>
            <td><code>e49fbd3c76f8137fe4414699c7816143ea6c83c3dd1f8c44db9f1bd007e5ceec</code></td>
        </tr>
        <tr>
            <td><b>s11d.bin</b></td>
            <td><code>b7e8487718b1c3dd835b3b71b785acc367469f5c84e7834d2b91518dc17da21e</code></td>
        </tr>
        <tr>
            <td><b>s11e.bin</b></td>
            <td><code>8400e639567b380f28320ccfc5d624b6aa16f8dafa80fdc212976ab386014a9a</code></td>
        </tr>
        <tr>
            <td><b>s11g.bin</b></td>
            <td><code>60c1e1882b4d9df99478a117a9bfb0d20eb58f4f37305aa46bb1658cf2761eb7</code></td>
        </tr>
        <tr>
            <td><b>s11h.bin</b></td>
            <td><code>de8b36f6bdeb9871b28bf53c2fd13f3f53d836cadcf26fe735358e42151a478b</code></td>
        </tr>
        <tr>
            <td><b>s11i.bin</b></td>
            <td><code>706e9fa4b2b2288b6967cc0e519a109f0d2fd6da01dc190996f331b28e3f57e9</code></td>
        </tr>
        <tr>
            <td><b>s12a.bin</b></td>
            <td><code>e99681d93e10f8cb1fd9fa0ae694bb1f5a517b18a42f8791d0df58feccdd2e1d</code></td>
        </tr>
        <tr>
            <td><b>s12b.bin</b></td>
            <td><code>7f7e125ea50101399608c859611515df3fb6f04c87ccfdcb10521d86a5aff71a</code></td>
        </tr>
        <tr>
            <td><b>s12c.bin</b></td>
            <td><code>3e22cf0791fffbef348149ba97e65b9d147488cb45992a1dd84e343414948cf1</code></td>
        </tr>
        <tr>
            <td><b>s13a.bin</b></td>
            <td><code>3af85549577319540e53c789f8a20fd10d8b080f74b309a3c6e966b453b75544</code></td>
        </tr>
        <tr>
            <td><b>s14e.bin</b></td>
            <td><code>0ad69a93f9aadf2e7b0b254cf6d39ad16c118d0af9686609b9df8ebcbed8986a</code></td>
        </tr>
        <tr>
            <td><b>s15a.bin</b></td>
            <td><code>ab3bf00937e226119c4649e9aa5db7f24e4aab844cb550c752bc3ce1a06f735e</code></td>
        </tr>
        <tr>
            <td><b>s15b.bin</b></td>
            <td><code>5ab64d6c10801c11b0f672cbb4e68ab62ef1bf058944f5c3d32dbd073e3c8501</code></td>
        </tr>
        <tr>
            <td><b>s15c.bin</b></td>
            <td><code>7a6d398f600f359a04b8d9fcb7c006fdc888f4fcbdffd761e09ef4a932195483</code></td>
        </tr>
        <tr>
            <td><b>s16a.bin</b></td>
            <td><code>1bec05b1d61f2f5b6abffa1903abcea0ab9e5f4ddebb88ac64506c81548e6ccb</code></td>
        </tr>
        <tr>
            <td><b>s16b.bin</b></td>
            <td><code>811a2aa5d5cd7ba8673f3ca9cc3a89f07c8ac9e1f3f5843fed311557ebc0b9f6</code></td>
        </tr>
        <tr>
            <td><b>s16c.bin</b></td>
            <td><code>8217a2be487140af5bbded5f0dc37ab8cabedaf9af99d16256650ce27a8a5b50</code></td>
        </tr>
        <tr>
            <td><b>s16d.bin</b></td>
            <td><code>c37c642eb06d7ec39364e4a1fac17e606804eee229e047102d4a2e93346e773f</code></td>
        </tr>
        <tr>
            <td><b>s17a.bin</b></td>
            <td><code>a6b691ff0be4af526fb856847be0549dbe015b31b7fb137a1fbbe6027125d4d1</code></td>
        </tr>
        <tr>
            <td><b>s17ar.bin</b></td>
            <td><code>a6b691ff0be4af526fb856847be0549dbe015b31b7fb137a1fbbe6027125d4d1</code></td>
        </tr>
        <tr>
            <td><b>s18a.bin</b></td>
            <td><code>4f605b802aef5c69ce4cc875165d41139acde9af1e9fdf419d0e4cee2bc7087e</code></td>
        </tr>
        <tr>
            <td><b>s18ar.bin</b></td>
            <td><code>17d33d059f09a7470b2e6f44efc2469f52f7ff74093542ffb4cdf52a5aa6c79d</code></td>
        </tr>
        <tr>
            <td><b>s19a.bin</b></td>
            <td><code>48390084a9a716bef980627c57df1867763a6502ad5109d2a6b3712e652840d7</code></td>
        </tr>
        <tr>
            <td><b>s19ar.bin</b></td>
            <td><code>ef64d5fdb5e8285116ee2f8c693bc20f9af802dc6c16996f815d8823127352e6</code></td>
        </tr>
        <tr>
            <td><b>s19b.bin</b></td>
            <td><code>d757942aca5d36ab95741801de1f68526c3a8e128018814f25655b7d72a7c249</code></td>
        </tr>
        <tr>
            <td><b>s19br.bin</b></td>
            <td><code>3d2d7c04d13dd3f55a97348f74eaf891615cfa203812d15494b53f9e570fe2bd</code></td>
        </tr>
        <tr>
            <td><b>s20a.bin</b></td>
            <td><code>d14fdf0f3b5c98f72fd9f24fd119cdf88660528930ec784dc3d021b92e796925</code></td>
        </tr>
        <tr>
            <td><b>s20ar.bin</b></td>
            <td><code>4d6fee8a574d6b900eadff3925f2a38516c2d28784d6e38444ce6c9ece46e104</code></td>
        </tr>
        <tr>
            <td><b>select.bin</b></td>
            <td><code>10350d22ceb73b58224a2da9cc71a87380415e304b4c161a787b491162636bc9</code></td>
        </tr>
        <tr>
            <td><b>select1.bin</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>select2.bin</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>select3.bin</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>select4.bin</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>selectd.bin</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>sound.bin</b></td>
            <td><code>4173d0fcbc7bfcd477d2e0fa6810b509bf6392efb01fd58a7fa114f003849816</code></td>
        </tr>
        <tr>
            <td><b>title.bin</b></td>
            <td><code>fb97721e30fd55cf6251e446d6e7d38e951049ec4703301da7fef7fe9c1afa6b</code></td>
        </tr>
        </tbody>
    </table>
</details>
</td>
        </tr>
        <tr>
            <td colspan=2 align=center><b>Overlays on <code>SLPM-86248</code></b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>Identical to <code>SLPM-86247</code> overlays.</td>
        </tr>
        <tr>
            <td colspan=2 align=center><b>Overlays on <code>SLPM-86249</code></b></td>
        </tr>
        <tr>
            <td><b>Status</b></td>
            <td>❌ Work not yet started.
<br><br>
Individual overlay progress:
<details>
<summary>Click to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
            <td><b>camera</b></td>
            <td>54 KB</td>
            <td>JPEG Photo Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>movie</b></td>
            <td>120 KB</td>
            <td>Extras Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>opening</b></td>
            <td>26 KB</td>
            <td>Opening Movie</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>option</b></td>
            <td>24 KB</td>
            <td>Options Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>photo_m1</b></td>
            <td>77 KB</td>
            <td>Photo Mode: Mei-Ling (Unused)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>photo_m2</b></td>
            <td>77 KB</td>
            <td>Photo Mode: Mei-Ling</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>photo_n1</b></td>
            <td>65 KB</td>
            <td>Photo Mode: Naomi (Unused)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>photo_n2</b></td>
            <td>65 KB</td>
            <td>Photo Mode: Naomi 1</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>photo_n3</b></td>
            <td>63 KB</td>
            <td>Photo Mode: Naomi 2</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>select</b></td>
            <td>9 KB</td>
            <td>Debug Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>selectvr</b></td>
            <td>137 KB</td>
            <td>VR Missions Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>sound</b></td>
            <td>2 KB</td>
            <td>Debug Menu Sound Test</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_cfr</b></td>
            <td>132 KB</td>
            <td>1 Min. Battle vs. Target: C-4<br>1 Min. Battle vs. Enemy: C-4</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_clm</b></td>
            <td>132 KB</td>
            <td>1 Min. Battle vs. Target: Claymore<br>1 Min. Battle vs. Enemy: Claymore</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_fms</b></td>
            <td>132 KB</td>
            <td>1 Min. Battle vs. Target: FA-MAS<br>1 Min. Battle vs. Enemy: FA-MAS</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_grn</b></td>
            <td>139 KB</td>
            <td>1 Min. Battle vs. Target: Grenade<br>1 Min. Battle vs. Enemy: Grenade</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_nkt</b></td>
            <td>136 KB</td>
            <td>1 Min. Battle vs. Target: Nikita<br>1 Min. Battle vs. Enemy: Nikita</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_psg</b></td>
            <td>132 KB</td>
            <td>1 Min. Battle vs. Target: PSG-1<br>1 Min. Battle vs. Enemy: PSG-1</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_scm</b></td>
            <td>135 KB</td>
            <td>1 Min. Battle vs. Target: SOCOM<br>1 Min. Battle vs. Enemy: SOCOM</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_stg</b></td>
            <td>132 KB</td>
            <td>1 Min. Battle vs. Target: Stinger<br>1 Min. Battle vs. Enemy: Stinger</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vab_sud</b></td>
            <td>136 KB</td>
            <td>1 Min. Battle vs. Target: No Weapon<br>1 Min. Battle vs. Enemy: No Weapon</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vcd_n01</b></td>
            <td>151 KB</td>
            <td>Ninja Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vcd_n02</b></td>
            <td>148 KB</td>
            <td>Ninja Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vcd_n03</b></td>
            <td>149 KB</td>
            <td>Ninja Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vcd_n04</b></td>
            <td>79 KB</td>
            <td>Variety Level 11: "The Truth is Over There"</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vcd_n05</b></td>
            <td>122 KB</td>
            <td>Variety Level 12: "Genetic Monster Genola"<br>Variety Level 13: "The Revenge of Genola"</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vcd_n06</b></td>
            <td>74 KB</td>
            <td>Variety Level 09<br>Variety Level 10</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_01</b></td>
            <td>142 KB</td>
            <td>Puzzle Level 04<br>Mystery Level 01<br>Vs. 12 Battle Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_02</b></td>
            <td>139 KB</td>
            <td>Puzzle Level 05<br>Mystery Level 08<br>Vs. 12 Battle Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_03</b></td>
            <td>141 KB</td>
            <td>Variety Level 07<br>Mystery Level 05<br>Vs. 12 Battle Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_04</b></td>
            <td>149 KB</td>
            <td>Puzzle Level 06<br>Mystery Level 07<br>Vs. 12 Battle Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_05</b></td>
            <td>152 KB</td>
            <td>Puzzle Level 07<br>Mystery Level 03<br>Vs. 12 Battle Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_06</b></td>
            <td>146 KB</td>
            <td>Variety Level 08<br>Mystery Level 06<br>Vs. 12 Battle Level 06</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_07</b></td>
            <td>145 KB</td>
            <td>Puzzle Level 08<br>Mystery Level 09<br>Vs. 12 Battle Level 07</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_08</b></td>
            <td>146 KB</td>
            <td>Puzzle Level 09<br>Mystery Level 04<br>Vs. 12 Battle Level 08</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_09</b></td>
            <td>145 KB</td>
            <td>Puzzle Level 10<br>Mystery Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vefgh_10</b></td>
            <td>137 KB</td>
            <td>Mystery Level 10</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_01</b></td>
            <td>127 KB</td>
            <td>VR Mission Stage 01<br>Variety Level 04<br>NG Selection Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_02</b></td>
            <td>134 KB</td>
            <td>VR Mission Stage 04<br>Variety Level 02<br>NG Selection Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_03</b></td>
            <td>133 KB</td>
            <td>VR Mission Stage 02<br>Variety Level 06<br>NG Selection Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_04</b></td>
            <td>140 KB</td>
            <td>VR Mission Stage 03<br>Variety Level 03<br>Puzzle Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_05</b></td>
            <td>140 KB</td>
            <td>VR Mission Stage 05<br>Variety Level 05<br>NG Selection Level 06</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_06</b></td>
            <td>138 KB</td>
            <td>VR Mission Stage 06<br>Puzzle Level 01<br>NG Selection Level 07</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_07</b></td>
            <td>142 KB</td>
            <td>VR Mission Stage 07<br>Puzzle Level 02<br>NG Selection Level 08</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_08</b></td>
            <td>128 KB</td>
            <td>VR Mission Stage 08<br>Variety Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_09</b></td>
            <td>128 KB</td>
            <td>VR Mission Stage 09<br>NG Selection Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vijkl_10</b></td>
            <td>134 KB</td>
            <td>VR Mission Stage 10<br>NG Selection Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_cfr01</b></td>
            <td>130 KB</td>
            <td>Weapon Mode: C-4 Level 01<br>Advanced Mode: C-4 Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_cfr02</b></td>
            <td>143 KB</td>
            <td>Weapon Mode: C-4 Level 05<br>Advanced Mode: C-4 Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_cfr03</b></td>
            <td>130 KB</td>
            <td>Weapon Mode: C-4 Level 02<br>Advanced Mode: C-4 Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_cfr04</b></td>
            <td>139 KB</td>
            <td>Weapon Mode: C-4 Level 03<br>Advanced Mode: C-4 Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_cfr05</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: C-4 Level 04<br>Advanced Mode: C-4 Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_clm01</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Claymore Level 01<br>Advanced Mode: Claymore Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_clm02</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Claymore Level 02<br>Advanced Mode: Claymore Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_clm03</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Claymore Level 05<br>Advanced Mode: Claymore Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_clm04</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Claymore Level 03<br>Advanced Mode: Claymore Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_clm05</b></td>
            <td>146 KB</td>
            <td>Weapon Mode: Claymore Level 04<br>Advanced Mode: Claymore Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_fms01</b></td>
            <td>130 KB</td>
            <td>Weapon Mode: FA-MAS Level 01<br>Advanced Mode: FA-MAS Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_fms02</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: FA-MAS Level 02<br>Advanced Mode: FA-MAS Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_fms03</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: FA-MAS Level 05<br>Advanced Mode: FA-MAS Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vr_fms04</b></td>
            <td>139 KB</td>
            <td>Weapon Mode: FA-MAS Level 04<br>Advanced Mode: FA-MAS Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_fms05</b></td>
            <td>146 KB</td>
            <td>Weapon Mode: FA-MAS Level 03<br>Advanced Mode: FA-MAS Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_grn01</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Grenade Level 01<br>Advanced Mode: Grenade Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_grn02</b></td>
            <td>143 KB</td>
            <td>Weapon Mode: Grenade Level 02<br>Advanced Mode: Grenade Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_grn03</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Grenade Level 05<br>Advanced Mode: Grenade Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_grn04</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Grenade Level 04<br>Advanced Mode: Grenade Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_grn05</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Grenade Level 03<br>Advanced Mode: Grenade Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_nkt01</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Nikita Level 02<br>Advanced Mode: Nikita Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_nkt02</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Nikita Level 03<br>Advanced Mode: Nikita Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_nkt03</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Nikita Level 04<br>Advanced Mode: Nikita Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_nkt04</b></td>
            <td>150 KB</td>
            <td>Weapon Mode: Nikita Level 05<br>Advanced Mode: Nikita Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_nkt05</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: Nikita Level 01<br>Advanced Mode: Nikita Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_psg01</b></td>
            <td>130 KB</td>
            <td>Weapon Mode: PSG-1 Level 02<br>Advanced Mode: PSG-1 Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_psg02</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: PSG-1 Level 03<br>Advanced Mode: PSG-1 Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_psg03</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: PSG-1 Level 05<br>Advanced Mode: PSG-1 Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_psg04</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: PSG-1 Level 04<br>Advanced Mode: PSG-1 Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_psg05</b></td>
            <td>133 KB</td>
            <td>Weapon Mode: PSG-1 Level 01<br>Advanced Mode: PSG-1 Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_scm01</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: SOCOM Level 02<br>Advanced Mode: SOCOM Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_scm02</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: SOCOM Level 04<br>Advanced Mode: SOCOM Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_scm03</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: SOCOM Level 01<br>Advanced Mode: SOCOM Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_scm04</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: SOCOM Level 05<br>Advanced Mode: SOCOM Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_scm05</b></td>
            <td>137 KB</td>
            <td>Weapon Mode: SOCOM Level 03<br>Advanced Mode: SOCOM Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_stg01</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Stinger Level 01<br>Advanced Mode: Stinger Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_stg02</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Stinger Level 02<br>Advanced Mode: Stinger Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_stg03</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Stinger Level 03<br>Advanced Mode: Stinger Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_stg04</b></td>
            <td>132 KB</td>
            <td>Weapon Mode: Stinger Level 05<br>Advanced Mode: Stinger Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_stg05</b></td>
            <td>140 KB</td>
            <td>Weapon Mode: Stinger Level 04<br>Advanced Mode: Stinger Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud01</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 01<br>Sneaking Mode: SOCOM Level 01</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud02</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 02<br>Sneaking Mode: SOCOM Level 02</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud03</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 03<br>Sneaking Mode: SOCOM Level 03</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud04</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 04<br>Sneaking Mode: SOCOM Level 04</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud05</b></td>
            <td>126 KB</td>
            <td>Sneaking Mode: No Weapon Level 05<br>Sneaking Mode: SOCOM Level 05</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud06</b></td>
            <td>135 KB</td>
            <td>Sneaking Mode: No Weapon Level 06<br>Sneaking Mode: SOCOM Level 06</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud07</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 08<br>Sneaking Mode: SOCOM Level 08</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud08</b></td>
            <td>127 KB</td>
            <td>Sneaking Mode: No Weapon Level 10<br>Sneaking Mode: SOCOM Level 10</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud09</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 12<br>Sneaking Mode: SOCOM Level 12</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud10</b></td>
            <td>149 KB</td>
            <td>Sneaking Mode: No Weapon Level 15<br>Sneaking Mode: SOCOM Level 15</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud11</b></td>
            <td>130 KB</td>
            <td>Sneaking Mode: No Weapon Level 11<br>Sneaking Mode: SOCOM Level 11</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud12</b></td>
            <td>142 KB</td>
            <td>Sneaking Mode: No Weapon Level 07<br>Sneaking Mode: SOCOM Level 07</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud13</b></td>
            <td>149 KB</td>
            <td>Sneaking Mode: No Weapon Level 13<br>Sneaking Mode: SOCOM Level 13</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud14</b></td>
            <td>135 KB</td>
            <td>Sneaking Mode: No Weapon Level 09<br>Sneaking Mode: SOCOM Level 09</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vr_sud15</b></td>
            <td>124 KB</td>
            <td>Sneaking Mode: No Weapon Level 14<br>Sneaking Mode: SOCOM Level 14</td>
            <td>❌ Work not started</td>
        </tr>
        <tr><td><b>vrsave</b></td>
            <td>67 KB</td>
            <td>VR Save Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>vrtitle</b></td>
            <td>100 KB</td>
            <td>VR Title Menu</td>
            <td>❌ Work not started</td>
        </tr>
        </tbody>
    </table>
</details>
Individual overlay SHA256:
<details>
<summary>Click to expand</summary>
<!-- Github incorrectly parses it if it's indented... -->
<table>
    <tbody>
        <tr>
            <td><b>camera.bin</b></td>
            <td><code>33d5e225f34814ddc827e918a88e70535345c79cd77ec4ea5e9336c68cb00684</code></td>
        </tr>
        <tr>
            <td><b>movie.bin</b></td>
            <td><code>ddd1d8c812047388808d3210c871046b312f555333d175d93ad1440990735c70</code></td>
        </tr>
            <td><b>opening.bin</b></td>
            <td><code>a2a0751df48357df4bac6a73aa28da1450d8eff63ea83dfb6bbcdd81fa2ab344</code></td>
        </tr>
        <tr>
            <td><b>option.bin</b></td>
            <td><code>40e504e60c0e6857726f771c9df358481bd89f63d5c0892b0937a13d6d36fe9a</code></td>
        </tr>
        <tr>
            <td><b>photo_m1.bin</b></td>
            <td><code>4d09f9a89f5e6167de88f9e362619d83909d6ac1ed8b2985ea36b1af1a198a7f</code></td>
        </tr>
        <tr>
            <td><b>photo_m2.bin</b></td>
            <td><code>d7c3279543cc5fe309c214f4ea3c93046900ab162ead4a41bea3db5ee08632f5</code></td>
        </tr>
        <tr>
            <td><b>photo_n1.bin</b></td>
            <td><code>634b2486063085bb750584c7c5e54d7998ba2bc26bbdf1579eb6ae68b6a76a92</code></td>
        </tr>
        <tr>
            <td><b>photo_n2.bin</b></td>
            <td><code>2e4f3bbfe6df592b509d06758d23adf074cb381df8f8eee867bf391bdee56bef</code></td>
        </tr>
        <tr>
            <td><b>photo_n3.bin</b></td>
            <td><code>5c9242a42230ebcee099c57f64b3235d0474bbe7b9138e1834c073fe639c178e</code></td>
        </tr>
        <tr>
            <td><b>select.bin</b></td>
            <td><code>fa8eec2a95979ba4bf68755a454ec91d3e723ff1ac2e75fd2ceca00b22a50296</code></td>
        </tr>
        <tr>
            <td><b>selectvr.bin</b></td>
            <td><code>87ab9c17a99c65be6dfb59aad35006e58940c2b9f2dea70a0a1e50088b6685c0</code></td>
        </tr>
        <tr>
            <td><b>sound.bin</b></td>
            <td><code>bc0abafb4604a8fc1346a63e10a0587bc7df602a9fd4b90f9e6c5c0b847ac188</code></td>
        </tr>
        <tr>
            <td><b>vab_cfr.bin</b></td>
            <td><code>bba8bb118b6bdb277102093b722a065096dd2d209c294f1a3625a9448fbd3be5</code></td>
        </tr>
        <tr>
            <td><b>vab_clm.bin</b></td>
            <td><code>c18ea33776c7e7dbaa9e32bdc4cf511d21a538928c139099aaa530c5e53653db</code></td>
        </tr>
        <tr>
            <td><b>vab_fms.bin</b></td>
            <td><code>d08a363fd0dd5485d5464d4313cc80e3ca57604488a77fb1178f93a05b275a64</code></td>
        </tr>
        <tr>
            <td><b>vab_grn.bin</b></td>
            <td><code>5f73014818a27f171768ed15c4864898c0824d771c7377b2f2b6d8095b56e4cf</code></td>
        </tr>
        <tr>
            <td><b>vab_nkt.bin</b></td>
            <td><code>446ad3f771830407687b90c27d62a29697a9fc4b51e1af892fce1c331770ab10</code></td>
        </tr>
        <tr>
            <td><b>vab_psg.bin</b></td>
            <td><code>6db9f9ad67d483c9ed657334ce59d64fed44c05e5c52b0ace0f905bebf72689e</code></td>
        </tr>
        <tr>
            <td><b>vab_scm.bin</b></td>
            <td><code>2627939f2b8d7d47f9db14de3858d1241ba1afa3cc61ab73dbc7dc632d67906b</code></td>
        </tr>
        <tr>
            <td><b>vab_stg.bin</b></td>
            <td><code>554e33f490619c209100dae7569475981a102792ea276382219900af2106238d</code></td>
        </tr>
        <tr>
            <td><b>vab_sud.bin</b></td>
            <td><code>a620f6487a2d70006821dec85a98b1db47a6d1e4369bdd0046464284a6d785f8</code></td>
        </tr>
        <tr>
            <td><b>vcd_n01.bin</b></td>
            <td><code>be4b2de7ef90ce39c274b2ae76218c89b305e3aea89aea623dd91afad0089553</code></td>
        </tr>
        <tr>
            <td><b>vcd_n02.bin</b></td>
            <td><code>68bb72a036bd161e244b41b94f16b191651dc880dc76679ccc5a1c93af777077</code></td>
        </tr>
        <tr>
            <td><b>vcd_n03.bin</b></td>
            <td><code>7e008ade3a8581fd26932a9c2fe242f640ba690d1f98f322f720354ec0085ba4</code></td>
        </tr>
        <tr>
            <td><b>vcd_n04.bin</b></td>
            <td><code>c4bee50f02d34a8e33b96ff3adb16bdfadff452994e1e66c4eec8129543bf9e0</code></td>
        </tr>
        <tr>
            <td><b>vcd_n05.bin</b></td>
            <td><code>179de4726e44e0ad48d53110ff9e6ec90240cd7f8463ba8db0ed80ed29586c07</code></td>
        </tr>
        <tr>
            <td><b>vcd_n06.bin</b></td>
            <td><code>858009f054adde758cab468ba2f5e8300f769cdada6bd1edc96e3793d1ff9e8b</code></td>
        </tr>
        <tr>
            <td><b>vefgh_01.bin</b></td>
            <td><code>c7047e1f5ebfde0eac28f162513908089ceecfb75dcdded16a700a97c21f1585</code></td>
        </tr>
        <tr>
            <td><b>vefgh_02.bin</b></td>
            <td><code>9f5d966a1222959bab1dd407c5aff3c6da3add4fa5c322b12c0c40ba8ba3b4ce</code></td>
        </tr>
        <tr>
            <td><b>vefgh_03.bin</b></td>
            <td><code>0b37518d03ce54c1949704fe2da2c9b91b20c2c527e17721bc3974068786841b</code></td>
        </tr>
        <tr>
            <td><b>vefgh_04.bin</b></td>
            <td><code>4351fd981685d1091c3cc3b1823546a3712ea82ffc483094b657a16caeb3a2b8</code></td>
        </tr>
        <tr>
            <td><b>vefgh_05.bin</b></td>
            <td><code>c5830e751c1212f22642ca6bef1924820e6227c211e809650c662ef6cf0a3a2d</code></td>
        </tr>
        <tr>
            <td><b>vefgh_06.bin</b></td>
            <td><code>1d55f7f595ccd75ccfe6b90ebc609c19cb6d96433d49f989986a2d6429a2b69d</code></td>
        </tr>
        <tr>
            <td><b>vefgh_07.bin</b></td>
            <td><code>c98097a8c4eb3d2d80a71fbb1ad7d733df80325f05dd7ffa052f5c30ddf71037</code></td>
        </tr>
        <tr>
            <td><b>vefgh_08.bin</b></td>
            <td><code>82e5b69300536168746f5e2e0cb4ef19ee26da91b4ad5ddd404c82f06bf3e09f</code></td>
        </tr>
        <tr>
            <td><b>vefgh_09.bin</b></td>
            <td><code>b8f2e33ec4d276ecb1c8bf7d719fe84565c079b71c09a2f029f3cdfd32dc4869</code></td>
        </tr>
        <tr>
            <td><b>vefgh_10.bin</b></td>
            <td><code>eadc2f458b77b3f4e9781370cc98bdd328d83fd165ff858c1ce4cecb55c65bdd</code></td>
        </tr>
        <tr>
            <td><b>vijkl_01.bin</b></td>
            <td><code>dd17d6ba16892cd1449e71ad5a59ab70c9376c101bc8e997b9a8fead46c2aec0</code></td>
        </tr>
        <tr>
            <td><b>vijkl_02.bin</b></td>
            <td><code>7b19973b2065cc98e0cc2b869c1820edfc99487ea9e43898a4152dfcadd5a944</code></td>
        </tr>
        <tr>
            <td><b>vijkl_03.bin</b></td>
            <td><code>076c639788354d4f878b5eae5b3363658da2caa7b9397f07fc6c8a81bad9ba99</code></td>
        </tr>
        <tr>
            <td><b>vijkl_04.bin</b></td>
            <td><code>4cf844a8b046386e1644256b6fecc8b67d8561823d3783e506d97cdb2acdd4e5</code></td>
        </tr>
        <tr>
            <td><b>vijkl_05.bin</b></td>
            <td><code>f6be0ff2fb5a3388f6d3b397d5291f5ef1f7651f2ea0e05894f1cc86bdf3de70</code></td>
        </tr>
        <tr>
            <td><b>vijkl_06.bin</b></td>
            <td><code>a6ac21344d324ab30f7d16edbebeb48f1d060d7666b7fae8db65510b147781b3</code></td>
        </tr>
        <tr>
            <td><b>vijkl_07.bin</b></td>
            <td><code>758d1cf801ea0a31b1d82a57ae553d951e326eed6d49e7871dec0f4a5a20fd82</code></td>
        </tr>
        <tr>
            <td><b>vijkl_08.bin</b></td>
            <td><code>f48fcad8a8ffeb5ec00f98b43700d46fcfe073f0a1b459b48c392ede5b9930e2</code></td>
        </tr>
        <tr>
            <td><b>vijkl_09.bin</b></td>
            <td><code>64522c4d342bdb7ee149c14d5d30393bd78bb0ba93a3d40a9b718d4c0eda338f</code></td>
        </tr>
        <tr>
            <td><b>vijkl_10.bin</b></td>
            <td><code>d09418e47278fc5d2a96c791be97a0d231391b24d20972ce83a5775bc1d5eee7</code></td>
        </tr>
        <tr>
            <td><b>vr_cfr01.bin</b></td>
            <td><code>e3540697d18e36e02328d53779eb3c3c8adcd842615fcf9a9d69993b80e402a2</code></td>
        </tr>
        <tr>
            <td><b>vr_cfr02.bin</b></td>
            <td><code>9757d956ea9aad5a4cd7625ef23a36bab0d914526e0d9178eed13bd1ba2fe9e6</code></td>
        </tr>
        <tr>
            <td><b>vr_cfr03.bin</b></td>
            <td><code>c4c5f7dea2cf0409f3ae603e805a9c50628094091da7fc607e1188003ae5f181</code></td>
        </tr>
        <tr>
            <td><b>vr_cfr04.bin</b></td>
            <td><code>20f73d6c77a8ecf7585dcb1d13abab74887feaca20a7b720efb3e5cf1c2de9b1</code></td>
        </tr>
        <tr>
            <td><b>vr_cfr05.bin</b></td>
            <td><code>8d9a2c0bec8bd8e892ce8aa08e373ecd38a2e5c1351eb6fc517e2d72a82f92e8</code></td>
        </tr>
        <tr>
            <td><b>vr_clm01.bin</b></td>
            <td><code>0d06593a1ee1ae3f5b72de9c18b6f58fe3ecb0b00e8ac7c4f422d4eb91d6f308</code></td>
        </tr>
        <tr>
            <td><b>vr_clm02.bin</b></td>
            <td><code>8967cbc3c9c808a69a4b5654022209e008bfbf6e0bcfe8f6c41aecf58660ad8d</code></td>
        </tr>
        <tr>
            <td><b>vr_clm03.bin</b></td>
            <td><code>b1b340104058235bd3c25d2f3871bcd2eb026115c681c17d5cac357e6d3f7c22</code></td>
        </tr>
        <tr>
            <td><b>vr_clm04.bin</b></td>
            <td><code>78008b3820689056c81efb75eba63b4c6cdc0a710ec0f56af6a30f6995d4acde</code></td>
        </tr>
        <tr>
            <td><b>vr_clm05.bin</b></td>
            <td><code>4e87cb870e5111d855498c8ba84e97fb75bc850bb34facb454c2df758c60f37b</code></td>
        </tr>
        <tr>
            <td><b>vr_fms01.bin</b></td>
            <td><code>17cc7a8894cf642e1ca2c222bfbd1ae0f7617e7032876ccea6a680bf3a38c679</code></td>
        </tr>
        <tr>
            <td><b>vr_fms02.bin</b></td>
            <td><code>3e0a8f1164fe3b6a0ce62a07d190538bf7e790359694e16851c45371072b91fb</code></td>
        </tr>
        <tr>
            <td><b>vr_fms03.bin</b></td>
            <td><code>0a8d39c760b2799002b707eeed74db9a88ff20c199a8d37f5d9fa9a0e7191ec5</code></td>
        </tr>
        <tr>
            <td><b>vr_fms04.bin</b></td>
            <td><code>90094b757cfc00154a8b59d1f3b7fa06df7b21c734b06b662e962776a165bac1</code></td>
        </tr>
        <tr>
            <td><b>vr_fms05.bin</b></td>
            <td><code>07ffa2646c98dc261e399a2f9ebd05203d769bebf4a494688dba9caa6bbe94cc</code></td>
        </tr>
        <tr>
            <td><b>vr_grn01.bin</b></td>
            <td><code>2bf060f4a39e08fa5c28eed3b2b7419ea37d2f51890400c78fdb8635fa4de885</code></td>
        </tr>
        <tr>
            <td><b>vr_grn02.bin</b></td>
            <td><code>0f26c0f2e3b509b5fdc14f35df0d1eecb8cd364f315af4e832397b116572ee59</code></td>
        </tr>
        <tr>
            <td><b>vr_grn03.bin</b></td>
            <td><code>93cf09c7cb238eb7c9d44cb233acf234b3242b3e72fdd4aec254407091adab1e</code></td>
        </tr>
        <tr>
            <td><b>vr_grn04.bin</b></td>
            <td><code>b3189ddb34efa31166c8d33261bb7a1faf0ad402542026486b8c7dd1cc93664c</code></td>
        </tr>
        <tr>
            <td><b>vr_grn05.bin</b></td>
            <td><code>dbbb5eba5b191a009862568d5d17ec28e00152c383c15ce01aa07fd52da5e5a7</code></td>
        </tr>
        <tr>
            <td><b>vr_nkt01.bin</b></td>
            <td><code>07161fb79db67a6f4f08cd0d3db87825c1a1a55afad7c87001aed968bc92677e</code></td>
        </tr>
        <tr>
            <td><b>vr_nkt02.bin</b></td>
            <td><code>168a45e7ac9c3a9c4454a9048797a4b1efacfe17076038a5c27df191b7661112</code></td>
        </tr>
        <tr>
            <td><b>vr_nkt03.bin</b></td>
            <td><code>786ad1a792e27dfbe1b2ab71c28416a8287d85c046524a8986e99ac39b0b283b</code></td>
        </tr>
        <tr>
            <td><b>vr_nkt04.bin</b></td>
            <td><code>e39592adcd7cb51b321105330a013b43886101d19f6308f4c423724f5f523174</code></td>
        </tr>
        <tr>
            <td><b>vr_nkt05.bin</b></td>
            <td><code>0c58e1c20a614cc8dfb3411b05fb1879994e42374d0288699912d44ad3b1b5c2</code></td>
        </tr>
        <tr>
            <td><b>vr_psg01.bin</b></td>
            <td><code>8ff3058151426649df67d8cf7cb13e2e63eea5ccadbc1bfed1be6fbad5ae2d8d</code></td>
        </tr>
        <tr>
            <td><b>vr_psg02.bin</b></td>
            <td><code>f84421c4a52296e31af9625a35ac9e12007306c112906ddfec97286fc52fde63</code></td>
        </tr>
        <tr>
            <td><b>vr_psg03.bin</b></td>
            <td><code>2c80a4431576af6de08d0a64ef0763d8f4bfca4d4f3b7cc7d27ae9496f8af061</code></td>
        </tr>
        <tr>
            <td><b>vr_psg04.bin</b></td>
            <td><code>c7703abdfb59ca4d04a84a03fc2d42c26b14ff14fac001c3fbdf0a17228d8731</code></td>
        </tr>
        <tr>
            <td><b>vr_psg05.bin</b></td>
            <td><code>abcdac864c5c490bfb4e4c3da9756878222571a6b1a9bd63d481e5db47083d0c</code></td>
        </tr>
        <tr>
            <td><b>vr_scm01.bin</b></td>
            <td><code>869b72323703f398289c9e59937afc135d8dede4ced8dda635a4edf55338d1c5</code></td>
        </tr>
        <tr>
            <td><b>vr_scm02.bin</b></td>
            <td><code>922b222f5ad0058054ade591e0f43823230c744ccdf2bb088b7633cd698ff675</code></td>
        </tr>
        <tr>
            <td><b>vr_scm03.bin</b></td>
            <td><code>853c533374616189dcc4da5556f83c1a5b5ef86b445dd2694c9a2ad3a3ee646e</code></td>
        </tr>
        <tr>
            <td><b>vr_scm04.bin</b></td>
            <td><code>a1400556a5067d0fbd9c1e5609fa2120cfb276b31aca430250a30b25e88c3bef</code></td>
        </tr>
        <tr>
            <td><b>vr_scm05.bin</b></td>
            <td><code>ee5936380bb945cc0eae69ae907f57bffb22d90ecef1d5cfd237b5382ed47a1e</code></td>
        </tr>
        <tr>
            <td><b>vr_stg01.bin</b></td>
            <td><code>d3ca029f51ec4d6cdaa395c2a349d0e22583d031b89029c8ad1e9f8c2bf428cb</code></td>
        </tr>
        <tr>
            <td><b>vr_stg02.bin</b></td>
            <td><code>e8a03cb422e7e4e9950b5c1a5c18bb65b472f89169b7009c71ed13a9d6d3d02f</code></td>
        </tr>
        <tr>
            <td><b>vr_stg03.bin</b></td>
            <td><code>7ed01303c6a1878d28f3aaabb2cdc47ec86bc6fe1811fe5d27fc8cead3d75233</code></td>
        </tr>
        <tr>
            <td><b>vr_stg04.bin</b></td>
            <td><code>6fe653b113082081917ec3f52b6ebaf11083e092ad919e6c5a6e2496b3b93a6a</code></td>
        </tr>
        <tr>
            <td><b>vr_stg05.bin</b></td>
            <td><code>9b5964c6290b59ebd111b184cc4565b3781165edfd8ec93a8dc7b73368ab8bcb</code></td>
        </tr>
        <tr>
            <td><b>vr_sud01.bin</b></td>
            <td><code>41f4f0bd54b6ccd45877dd8b35d40106d4f5be97fadfe45ce10c7cd6e7788c99</code></td>
        </tr>
        <tr>
            <td><b>vr_sud02.bin</b></td>
            <td><code>8830cfab59f86056690b0f74cbeb51424b5776091b1bd52fd6dc84c7db0c5408</code></td>
        </tr>
        <tr>
            <td><b>vr_sud03.bin</b></td>
            <td><code>456126883baace557e8f4fcb32660dd071a9587b3299fe0602c99359da4c574b</code></td>
        </tr>
        <tr>
            <td><b>vr_sud04.bin</b></td>
            <td><code>286dae7ca61adb49ee84566c4188571c36ee7783874424dc2cdb52446e9cc630</code></td>
        </tr>
        <tr>
            <td><b>vr_sud05.bin</b></td>
            <td><code>461cc1ef0cfa858be270da83da736ad04557fa7e388839d8f786870c396957d1</code></td>
        </tr>
        <tr>
            <td><b>vr_sud06.bin</b></td>
            <td><code>2e84f6679c11a0cda69bb9d249a4d37378ce7e08685c7fa2d578b9d8f495c71c</code></td>
        </tr>
        <tr>
            <td><b>vr_sud07.bin</b></td>
            <td><code>b3b3c512b37b82d059a79ab4df47282fddef1a1c33bc1180f4dcbf292f69d8e7</code></td>
        </tr>
        <tr>
            <td><b>vr_sud08.bin</b></td>
            <td><code>84e4c6c25797d164cf56f91fec79734b6efff3750b97156aa054cdc89f130fa7</code></td>
        </tr>
        <tr>
            <td><b>vr_sud09.bin</b></td>
            <td><code>e77f4e558ec9e5fecbf3fc939958875b38b40b40a4a9403e5ca6757e60b16639</code></td>
        </tr>
        <tr>
            <td><b>vr_sud10.bin</b></td>
            <td><code>3b34df06259b8cb03d29ea9569dd9684090c713e44e1bfa4b84cc1f5c7311914</code></td>
        </tr>
        <tr>
            <td><b>vr_sud11.bin</b></td>
            <td><code>870ef98c534f7c8880b83bdeb52f175ae09a3c306a21a095bc009c709956163f</code></td>
        </tr>
        <tr>
            <td><b>vr_sud12.bin</b></td>
            <td><code>d980455e00d779c60abe21407dc312586d1a73a355ea57e6a469aff527460f36</code></td>
        </tr>
        <tr>
            <td><b>vr_sud13.bin</b></td>
            <td><code>2d3f45e3399d48b3cb328790176596d2c690e015c5054424aa131de33e936ab3</code></td>
        </tr>
        <tr>
            <td><b>vr_sud14.bin</b></td>
            <td><code>3b986c02aa7e6b69ac1a7f0aec4e66d7111f4a65afbced1e424ea39f6bdaa4b7</code></td>
        </tr>
        <tr>
            <td><b>vr_sud15.bin</b></td>
            <td><code>232040540e92f233c14c8e7da7d904b414c0381e07a0db9f496ab1d099f4cd49</code></td>
        </tr>
        <tr>
            <td><b>vrsave.bin</b></td>
            <td><code>ee1eeb23395a900bc9e36348db0a393e5a86e0ed4996180e16626e7d9156c674</code></td>
        </tr>
        <tr>
            <td><b>vrtitle.bin</b></td>
            <td><code>ade8ca6f7d0ca99d371abcfbca53987415b43e66f326f9ee77518f1b7a4aff39</code></td>
        </tr>
        </tbody>
    </table>
</details>
            </td>
        </tr>
    </tbody>
</table>

## How to build

### `dev` variant
`dev` variant is a build variant that makes it easy to run the built game from `mgs_reversing` and test your own changes. Most notably it embeds some [overlay files](#Overlays) into the main executable to make it easier to load the game into an emulator.

mgs_reversing also provides a helper script `run.py` that starts the built game in [PCSX-Redux emulator](https://github.com/grumpycoders/pcsx-redux). Whenever you rebuild a game, this script will relaunch the emulator and you'll be able to see the changes you made.

1. Install Python3 if you haven't and make sure it's in your PATH. If you are on Linux, install Wine.
2. `git clone https://github.com/FoxdieTeam/psyq_sdk.git`
3. `git clone https://github.com/FoxdieTeam/mgs_reversing.git`
4. `cd mgs_reversing/build/`
5. `pip3 install -r requirements.txt`
6. `python3 build.py --variant=dev_exe`
7. `python3 run.py --iso ISO --pcsx-redux PCSX-REDUX-PATH`
    1. `ISO` is a path to ISO/ECM/BIN file with the original game (SLPM-86247).
    2. `PCSX-REDUX-PATH` is a path to a directory with downloaded [PCSX-Redux emulator](https://github.com/grumpycoders/pcsx-redux).
        - Download a ZIP file with the emulator into `PCSX-REDUX-PATH` directory. [Click here for Windows builds](https://install.appcenter.ms/orgs/grumpycoders/apps/pcsx-redux-win64/distribution_groups/public). [Click here for Linux builds](https://install.appcenter.ms/orgs/grumpycoders/apps/pcsx-redux-linux64/distribution_groups/public). You don't have to unzip the file.
    3. You should run this command in a separate command prompt. While this command is running, you can rebuild the game (with `python3 build.py --variant=dev_exe`) and the tool will automatically relaunch the emulator with the latest build.


### Matching builds (main executable, VR executable)

1. Install Python3 if you haven't and make sure it's in your PATH. If you are on Linux, install Wine.
2. `git clone https://github.com/FoxdieTeam/psyq_sdk.git`
3. `git clone https://github.com/FoxdieTeam/mgs_reversing.git`
4. `cd mgs_reversing/build/`
5. `pip3 install -r requirements.txt`
6. `python3 build.py`
    - or `python3 build.py --variant=vr_exe` for VR executable
7. At the end you should see a message confirming that the built binary's hash matches the original game's binary's hash. If your code caused the compiler to emit warnings, try to fix them without breaking the match.

### How to use the built (matching) executables

Once you have successfully built the executables from the source code, you may want to play it to debug or test the changes you have made. Please keep in mind that if the size of the main executable changes or addresses shift, the original [overlays](#Overlays) won't work properly. This guide does not describe how to repackage overlays (a packer tool is planned for the future).
For how to use the `dev` variant, please see the build instructions above.

#### PCSX-Redux

[PCSX-Redux](https://github.com/grumpycoders/pcsx-redux) emulator provides a convenient way to load a modified main executable. Once you have loaded the original image of *Metal Gear Solid: Integral* you can load a modified executable in "File > Load binary" menu. This repository contains some helper Lua scripts that can be used with PCSX-Redux in `build/pcsx-redux_scripts` folder.

#### Other emulators - rebuilding ISO

To rebuild an ISO with your modified executable, you need a tool called [mkpsxiso](https://github.com/Lameguy64/mkpsxiso): download and extract it to a folder of your choice.

Next, you need the original files of *Metal Gear Solid: Integral* from the CD-ROMs. If you have dumped the discs into .bin/.cue pairs, you need to unpack them into a folder using mkpsxiso. The following commands show how to do this for the first disc, but the same applies to the other two.

Open a terminal, `cd` into a folder of your choice and run the following command:
```
<mkpsxiso_folder_path>\bin\dumpsxiso.exe <path\to\mgsi_d1.bin> -x MGSI_D1 -s mgsi_d1.xml
```

This will create a folder named `MGSI_D1` (containing the files of the first disc of the game), and an additional file, `mgsi_d1.xml`.

Open `mgsi_d1.xml` and replace
```xml
<file name="SLPM_862.47" source="MGSI_D1/MGS/SLPM_862.47" type="data"/>
```

with
```xml
<file name="SLPM_862.47" source="<path/to/_mgsi.exe>" type="data"/>
```

where `_mgsi.exe` is the output of the build process.

Optionally, you can also edit the attributes `image_name` and `cue_sheet` of the `iso_project` element to give them more appropriate values, like `mgsi_d1.bin` and `mgsi_d1.cue`, which are the output files of the next step.

Finally, run
```
<mkpsxiso_folder_path>\bin\mkpsxiso.exe mgsi_d1.xml
```

to re-pack the `MGSI_D1` folder into a .bin/.cue pair that now contains the new executable instead of the original one. From now on, this is the only command to be executed every time you want to test a different version of the executable.

Now you are ready to play the game with your favorite emulator by starting the file `mgsi_d1.cue`.

## How to decompile a function

The `asm/overlays` directory contains functions that are not yet decompiled. As a starting point you could try finding a small function (small .s file) and try to decompile that function.

We make extensive use of [decomp.me](https://decomp.me/), which has a *Metal Gear Solid (overlays)* preset, to help match functions.

Before decompiling a new function, we highly recommend playing around with some functions already decompiled - see recent scratches [here](https://decomp.me/preset/19).

Before working on a function, search for it on the website and if you don't find it, go to the `build` folder and run `python decompme_asm.py [path to .s file]` to have the assembly instructions in your clipboard ready to paste into a new decomp.me scratch. Since there is a lot of duplication in overlays, make sure that this function was not already decompiled in some other overlay (for example make sure that there is no `blastoff.c` file for a function called `s11g_blastoff_800D4744`).

When you create a new decomp.me scratch you'll be asked for a context - you can use a context from one of the scratches [here](https://decomp.me/preset/19). decomp.me will decompile the function into C. Now comes the hard part: make the scratch compile without any errors and implement the function such that it matches the original assembly. This is a highly iterative process.

## Help, I am totally stuck?

Join [our Discord](https://discord.gg/tTvhQ8w) and ask for help in `#metal_gear_dev`.
