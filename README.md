# mgs_reversing

This project aims to completely reverse engineer *Metal Gear Solid Integral* for PlayStation back to C source code which when compiled produces the same assembly code.

At this moment `SLPM_862.47`/`SLPM_862.48`/`SLPM_862.49` main executables are 100% decompiled. However, even though this is a substantial milestone, a significant amount of work
is still left to decompile [overlays](#Overlays), clean up already decompiled code and make it all shiftable.

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
            <td><code>python build.py && python build.py --variant=vr_exe</code></td>
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
            <td>Load Save From Memcard</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>brf</b></td>
            <td>125 KB</td>
            <td>Briefing Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>camera</b></td>
            <td>54 KB</td>
            <td>Load JPEG From Memcard</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>change</b></td>
            <td>12 KB</td>
            <td>Disc Change</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>d00a</b></td>
            <td>122 KB</td>
            <td>Docks Cutscene</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d01a</b></td>
            <td>57 KB</td>
            <td>Heliport Cutscene</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d03a</b></td>
            <td>18 KB</td>
            <td>Cell Cutscene</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d11c</b></td>
            <td>14 KB</td>
            <td>Communication Tower B Cutscene</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d16e</b></td>
            <td>65 KB</td>
            <td>Rex Hangar Cutscene</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>d18a</b></td>
            <td>96 KB</td>
            <td>Liquid Fight Cutscene</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>d18ar</b></td>
            <td>96 KB</td>
            <td>Liquid Fight Cutscene</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>demosel</b></td>
            <td>16 KB</td>
            <td>Demo Theater</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>ending</b></td>
            <td>40 KB</td>
            <td>Ending</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>endingr</b></td>
            <td>40 KB</td>
            <td>Ending</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>opening</b></td>
            <td>42 KB</td>
            <td>Intro FMV</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>option</b></td>
            <td>26 KB</td>
            <td>Options Menu</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>preope</b></td>
            <td>25 KB</td>
            <td>Previous Operations</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>rank</b></td>
            <td>139 KB</td>
            <td>Rank Screen</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>roll</b></td>
            <td>39 KB</td>
            <td>Credits</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s00a</b></td>
            <td>120 KB</td>
            <td>Docks</td>
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
            <td>Cell</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03ar</b></td>
            <td>75 KB</td>
            <td>Cell</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03b</b></td>
            <td>66 KB</td>
            <td>Torture Room</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s03c</b></td>
            <td>84 KB</td>
            <td>Torture Room Cell</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s03d</b></td>
            <td>101 KB</td>
            <td>Torture Room Cell</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s03dr</b></td>
            <td>101 KB</td>
            <td>Torture Room Cell</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s03e</b></td>
            <td>38 KB</td>
            <td>Cell (Fight)</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s03er</b></td>
            <td>38 KB</td>
            <td>Cell (Fight)</td>
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
            <td>Armory Ocelot Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s04br</b></td>
            <td>116 KB</td>
            <td>Armory Ocelot Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s04c</b></td>
            <td>100 KB</td>
            <td>Armory Ocelot Fight</td>
            <td>❌ Work not started</td>
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
            <td>Nuke Building 1</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s07a</b></td>
            <td>130 KB</td>
            <td>Nuke Building B1</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s07b</b></td>
            <td>141 KB</td>
            <td>Commanders Room</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s07br</b></td>
            <td>141 KB</td>
            <td>Commanders Room</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s07c</b></td>
            <td>73 KB</td>
            <td>Commanders Room</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s07cr</b></td>
            <td>73 KB</td>
            <td>Commanders Room</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s08a</b></td>
            <td>86 KB</td>
            <td>Nuke Building 2</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s08b</b></td>
            <td>133 KB</td>
            <td>Lab Gray Fox Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s08br</b></td>
            <td>133 KB</td>
            <td>Lab Gray Fox Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s08c</b></td>
            <td>60 KB</td>
            <td>Nuke Building B2</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s08cr</b></td>
            <td>60 KB</td>
            <td>Nuke Building B2</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s09a</b></td>
            <td>121 KB</td>
            <td>Cave</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s09ar</b></td>
            <td>121 KB</td>
            <td>Cave</td>
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
            <td>Underground Passage</td>
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
            <td>Roof</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11c</b></td>
            <td>65 KB</td>
            <td>Communication Tower B</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11d</b></td>
            <td>60 KB</td>
            <td>Tower Wall A</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11e</b></td>
            <td>113 KB</td>
            <td>Communication Tower B Elevator Fight</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s11g</b></td>
            <td>105 KB</td>
            <td>Roof Communication Tower</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11h</b></td>
            <td>97 KB</td>
            <td>Roof Communication Tower Hind D Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s11i</b></td>
            <td>75 KB</td>
            <td>Walkway</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s12a</b></td>
            <td>107 KB</td>
            <td>Snow Field</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s12b</b></td>
            <td>96 KB</td>
            <td>Snow Field (After Sniper Wolf Battle)</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s12c</b></td>
            <td>95 KB</td>
            <td>Snow Field (After Sniper Wolf Battle)</td>
            <td>🚧 Work in progress</td>
        </tr>
        <tr>
            <td><b>s13a</b></td>
            <td>130 KB</td>
            <td>Blast Furnace</td>
            <td>❌ Work not started</td>
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
            <td>Warehouse</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s15c</b></td>
            <td>129 KB</td>
            <td>Warehouse</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s16a</b></td>
            <td>63 KB</td>
            <td>Rex Hangar 1st Floor</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s16b</b></td>
            <td>10 KB</td>
            <td>Rex Hangar 2nd Floor</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s16c</b></td>
            <td>109 KB</td>
            <td>Rex Hangar 3rd Floor</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s16d</b></td>
            <td>121 KB</td>
            <td>Command Room</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s17a</b></td>
            <td>140 KB</td>
            <td>Rex Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s17ar</b></td>
            <td>140 KB</td>
            <td>Rex Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s18a</b></td>
            <td>133 KB</td>
            <td>Liquid Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s18ar</b></td>
            <td>133 KB</td>
            <td>Liquid Fight</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19a</b></td>
            <td>120 KB</td>
            <td>Escape Route Meryl</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19ar</b></td>
            <td>120 KB</td>
            <td>Escape Route Meryl</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19b</b></td>
            <td>110 KB</td>
            <td>Escape Route Otacon</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s19br</b></td>
            <td>110 KB</td>
            <td>Escape Route Otacon</td>
            <td>❌ Work not started</td>
        </tr>
        <tr>
            <td><b>s20a</b></td>
            <td>30 KB</td>
            <td>Ending</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>s20ar</b></td>
            <td>30 KB</td>
            <td>Ending</td>
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
            <td>Debug Menu Stage Select</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select2</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select s05a-s09a</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select3</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select s10a-s14e</td>
            <td><b>✔️ 100% decompiled!</b></td>
        </tr>
        <tr>
            <td><b>select4</b></td>
            <td>721 B</td>
            <td>Debug Menu Stage Select s15a-s20a</td>
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
            <td><b>abst</b></td>
            <td><code>aed6a6145201850156d251618561487456e1b02d7ce26a40cf1e492b6fa30ec0</code></td>
        </tr>
        <tr>
            <td><b>brf</b></td>
            <td><code>95f948d72f4b2dd523c3f60b3e036db2971c5f00b3f69d7dc9b4744c48996286</code></td>
        </tr>
        <tr>
            <td><b>camera</b></td>
            <td><code>7e1738af3c3987b5461773cf865da803bac48820000e0e916307f29fa836f388</code></td>
        </tr>
        <tr>
            <td><b>change</b></td>
            <td><code>d2f0afa4861278774ecc818c19e31420e3b05e96da4313ea048451bfabf780e5</code></td>
        </tr>
        <tr>
            <td><b>d00a</b></td>
            <td><code>3dd07b291d5bc6b58a028d012b744d9d2c8023f143474467b0259e5a5603ad0a</code></td>
        </tr>
        <tr>
            <td><b>d01a</b></td>
            <td><code>3a8d292f250a80b708a06f3fd41ee0e6b74733390084ef5b163108ba5c8af4a1</code></td>
        </tr>
        <tr>
            <td><b>d03a</b></td>
            <td><code>3f3b4350dc263a088c70fa7518844ba8e5ec95a3f705ffbc5a37e6b5ff18f8b1</code></td>
        </tr>
        <tr>
            <td><b>d11c</b></td>
            <td><code>86edb16ecdb7319d0ad133687228a808170a50ce36f393c96678f8379c48c746</code></td>
        </tr>
        <tr>
            <td><b>d16e</b></td>
            <td><code>bf5ab697b6d0415ba63b9aa3aaba28f387f324cd2f1b32eb46f5d3cb253e48ef</code></td>
        </tr>
        <tr>
            <td><b>d18a</b></td>
            <td><code>c388e19be2811a05075a0da664b5b4264040ecd7e2f6eb6cd761d8e579c35103</code></td>
        </tr>
        <tr>
            <td><b>d18ar</b></td>
            <td><code>df7d5353a7b3be3d6d0f2550179181de27538c41b65b900c7f4a90068ee9d18a</code></td>
        </tr>
        <tr>
            <td><b>demosel</b></td>
            <td><code>bbf6a776efcc2631b982f920f2c9247c8b215dd7a1358b3b9f9d76484f7d43d9</code></td>
        </tr>
        <tr>
            <td><b>ending</b></td>
            <td><code>321c325577bb05cf68bec689083cbc9f7fc4d0b634776c1e6cad1f464ffb1da3</code></td>
        </tr>
        <tr>
            <td><b>endingr</b></td>
            <td><code>c8eabac0fa0bde6d7bbbdba97a4b8948c3e6a0c839d2b438705345c392b43c35</code></td>
        </tr>
        <tr>
            <td><b>opening</b></td>
            <td><code>87a5e822f5b428376ad36fcd28ebc56f661cf340f0ea059f11489b5f24e85545</code></td>
        </tr>
        <tr>
            <td><b>option</b></td>
            <td><code>19e897b855f2e197e62160a8a409d2ff57a6b8588b831722fab9c3aaca324ea0</code></td>
        </tr>
        <tr>
            <td><b>preope</b></td>
            <td><code>3176b630b8a3f9d8cb01ed833d78fbe654054a576c1f2da0ed91007dd71bd136</code></td>
        </tr>
        <tr>
            <td><b>rank</b></td>
            <td><code>6a5ed242f966a4c60bba7daf9a2ba1c37482825d0786e1d77476e135030753f5</code></td>
        </tr>
        <tr>
            <td><b>roll</b></td>
            <td><code>dfe3ca728b6e409613ef7a3dc11b48ecaa236d8ba6cd0951ce4321329842beae</code></td>
        </tr>
        <tr>
            <td><b>s00a</b></td>
            <td><code>533cb8e9b6ffdcc442c25ba51eb3d83e90cb1ad2831d3870395333398c8402bc</code></td>
        </tr>
        <tr>
            <td><b>s01a</b></td>
            <td><code>534f8365ad37dbb5c4753bd1720517fa4d1a92e9008597064e6b30a23dc00a75</code></td>
        </tr>
        <tr>
            <td><b>s02a</b></td>
            <td><code>ece10d39e1d5bafee5acb4dd970bf83801128b04e4fb24ad31756e5bb4ca754d</code></td>
        </tr>
        <tr>
            <td><b>s02b</b></td>
            <td><code>57a66e93a2028e3fb805c97c585fb6cfb5fe76c93fc4b8495ccdb2c03a1de308</code></td>
        </tr>
        <tr>
            <td><b>s02c</b></td>
            <td><code>7c0b12187840f60405970364a1f7c73ec96be32c1130b3f9a87ec58f6ea46915</code></td>
        </tr>
        <tr>
            <td><b>s02d</b></td>
            <td><code>5fe851426faf64733c1077998f9463b5455c766d3e27c9cdceed38ac338e8542</code></td>
        </tr>
        <tr>
            <td><b>s02e</b></td>
            <td><code>cd79cd79a00e18bd5d323b0b8e153b4e8fe5548b6e0ea68f36d13f190eca0477</code></td>
        </tr>
        <tr>
            <td><b>s03a</b></td>
            <td><code>c42bba970bdc968ee48b572efb03c41f15869cfc00d6aa0d7c8106487534f580</code></td>
        </tr>
        <tr>
            <td><b>s03ar</b></td>
            <td><code>f34b46313625005b6aef5006b184556c4dd8f13e97a3b0c346f0f4fc7b9fbf04</code></td>
        </tr>
        <tr>
            <td><b>s03b</b></td>
            <td><code>cd728e144c960e7419d389c81802d3de73c00a2f31e9bfd7eea33ed3ed2be083</code></td>
        </tr>
        <tr>
            <td><b>s03c</b></td>
            <td><code>cc3b95638684f6f0a6cbcf9b0436fbc7b545ca0eeb0e6e60d6c4d0646dbc7fb4</code></td>
        </tr>
        <tr>
            <td><b>s03d</b></td>
            <td><code>f9fa0f39352d3305b5cb2bd6c292297d4f351387b0038a27ccec29f42150d903</code></td>
        </tr>
        <tr>
            <td><b>s03dr</b></td>
            <td><code>fa785a857655809ccf984d8c8ada626addbadfd11db31b34ef496ddce225ade1</code></td>
        </tr>
        <tr>
            <td><b>s03e</b></td>
            <td><code>af0e15b223431977c2ad233596c37a51c0367da6470c1b760d3f211eb82e894c</code></td>
        </tr>
        <tr>
            <td><b>s03er</b></td>
            <td><code>b1e60c25c0ee92e8c347b7f6a51b2e3fdb10d9ea33a2a77e1acbd8bfc7367114</code></td>
        </tr>
        <tr>
            <td><b>s04a</b></td>
            <td><code>59b541a13b987478d6717643c3c146018b070fe374ffae0eaaf3f9a8bdc2ffb6</code></td>
        </tr>
        <tr>
            <td><b>s04b</b></td>
            <td><code>bca0c362260565051a8d41ffc49d3b9ae84d1bc9dc758164ea019cae82de7fa7</code></td>
        </tr>
        <tr>
            <td><b>s04br</b></td>
            <td><code>3ceb35994af2c7da7955ab356cbbb7471c749ff6788ecdfbffab1c5679bb4f9b</code></td>
        </tr>
        <tr>
            <td><b>s04c</b></td>
            <td><code>5e6bc0c9b13f009c69c2ebdfb401fe9d55a6cd6ee8610cbdd95ee9f3dd71f32a</code></td>
        </tr>
        <tr>
            <td><b>s05a</b></td>
            <td><code>fd08923d1e1ad01b8638f7e8f4a101e270a5f399f3d1afed47abca7532a8c081</code></td>
        </tr>
        <tr>
            <td><b>s06a</b></td>
            <td><code>766d25f927a1116d565f97479786a42b93a275398310f775304668ec191a47e7</code></td>
        </tr>
        <tr>
            <td><b>s07a</b></td>
            <td><code>20cb960a5d97e0b60c030ed0c17eea78bf6d7e0f5dc50945828e8c2106612546</code></td>
        </tr>
        <tr>
            <td><b>s07b</b></td>
            <td><code>bbe527b3883ad7c41e4999a8b1d49e64265100b7d8ff6a7724e3fce5d6fb7328</code></td>
        </tr>
        <tr>
            <td><b>s07br</b></td>
            <td><code>04007a426525216049196b550e22fc0e922c75f78c6fcfc4b469f9d5defbbc47</code></td>
        </tr>
        <tr>
            <td><b>s07c</b></td>
            <td><code>03904064a3d2d2bcd83f719cf7de0d780886ebeae5645dcc7e345acd7fe8cba1</code></td>
        </tr>
        <tr>
            <td><b>s07cr</b></td>
            <td><code>e3c3503599693be3d3729e0bfc09d364de85b46520eff3909b822a14a7dadfbd</code></td>
        </tr>
        <tr>
            <td><b>s08a</b></td>
            <td><code>56a0d3aa551dd6eefda902497c3f0a90c458b4ab0a54b9a63b7fe3298606d4c9</code></td>
        </tr>
        <tr>
            <td><b>s08b</b></td>
            <td><code>21c5534dd17e5579404b2b0b2f3c47fb324b27a363a108669e3818a3dee15ded</code></td>
        </tr>
        <tr>
            <td><b>s08br</b></td>
            <td><code>064e8dbb2af7589a7122f02a51e202d43fd3e9bf05aa18258c5cd88621a2d69c</code></td>
        </tr>
        <tr>
            <td><b>s08c</b></td>
            <td><code>5badd1f304a57a3e55af6d5fe15694c51398c602779a31ee2b7276ad9f9aafbb</code></td>
        </tr>
        <tr>
            <td><b>s08cr</b></td>
            <td><code>1521588d917c0558839f915191ed5b643fba37a7d1fa4dc228951b433e1070c9</code></td>
        </tr>
        <tr>
            <td><b>s09a</b></td>
            <td><code>4c698b375890c793c3622d410bffab7db48c01cfff393f458cd5712e316a7177</code></td>
        </tr>
        <tr>
            <td><b>s09ar</b></td>
            <td><code>362fbe4c139197907498e38a1f56e403fe39b4a0217d34bfcf49cf86e86cb76b</code></td>
        </tr>
        <tr>
            <td><b>s10a</b></td>
            <td><code>95f9cb0d5def5f30bb2133c0452b3aa49438f56c95535178d61eb11a03bb2e6e</code></td>
        </tr>
        <tr>
            <td><b>s10ar</b></td>
            <td><code>465959ab31568740a4bf30bf0958865e485e48538e449a6b3c696c5fd7d52f69</code></td>
        </tr>
        <tr>
            <td><b>s11a</b></td>
            <td><code>70be6cf00267ed663e29ce6b9598396e8fb7c60024b76ff86508244c56d39bf6</code></td>
        </tr>
        <tr>
            <td><b>s11b</b></td>
            <td><code>280920ec9559d0c836bab8995de902f227759bb7430025a650f7c20633889f51</code></td>
        </tr>
        <tr>
            <td><b>s11c</b></td>
            <td><code>e49fbd3c76f8137fe4414699c7816143ea6c83c3dd1f8c44db9f1bd007e5ceec</code></td>
        </tr>
        <tr>
            <td><b>s11d</b></td>
            <td><code>b7e8487718b1c3dd835b3b71b785acc367469f5c84e7834d2b91518dc17da21e</code></td>
        </tr>
        <tr>
            <td><b>s11e</b></td>
            <td><code>8400e639567b380f28320ccfc5d624b6aa16f8dafa80fdc212976ab386014a9a</code></td>
        </tr>
        <tr>
            <td><b>s11g</b></td>
            <td><code>60c1e1882b4d9df99478a117a9bfb0d20eb58f4f37305aa46bb1658cf2761eb7</code></td>
        </tr>
        <tr>
            <td><b>s11h</b></td>
            <td><code>de8b36f6bdeb9871b28bf53c2fd13f3f53d836cadcf26fe735358e42151a478b</code></td>
        </tr>
        <tr>
            <td><b>s11i</b></td>
            <td><code>706e9fa4b2b2288b6967cc0e519a109f0d2fd6da01dc190996f331b28e3f57e9</code></td>
        </tr>
        <tr>
            <td><b>s12a</b></td>
            <td><code>e99681d93e10f8cb1fd9fa0ae694bb1f5a517b18a42f8791d0df58feccdd2e1d</code></td>
        </tr>
        <tr>
            <td><b>s12b</b></td>
            <td><code>7f7e125ea50101399608c859611515df3fb6f04c87ccfdcb10521d86a5aff71a</code></td>
        </tr>
        <tr>
            <td><b>s12c</b></td>
            <td><code>3e22cf0791fffbef348149ba97e65b9d147488cb45992a1dd84e343414948cf1</code></td>
        </tr>
        <tr>
            <td><b>s13a</b></td>
            <td><code>3af85549577319540e53c789f8a20fd10d8b080f74b309a3c6e966b453b75544</code></td>
        </tr>
        <tr>
            <td><b>s14e</b></td>
            <td><code>0ad69a93f9aadf2e7b0b254cf6d39ad16c118d0af9686609b9df8ebcbed8986a</code></td>
        </tr>
        <tr>
            <td><b>s15a</b></td>
            <td><code>ab3bf00937e226119c4649e9aa5db7f24e4aab844cb550c752bc3ce1a06f735e</code></td>
        </tr>
        <tr>
            <td><b>s15b</b></td>
            <td><code>5ab64d6c10801c11b0f672cbb4e68ab62ef1bf058944f5c3d32dbd073e3c8501</code></td>
        </tr>
        <tr>
            <td><b>s15c</b></td>
            <td><code>7a6d398f600f359a04b8d9fcb7c006fdc888f4fcbdffd761e09ef4a932195483</code></td>
        </tr>
        <tr>
            <td><b>s16a</b></td>
            <td><code>1bec05b1d61f2f5b6abffa1903abcea0ab9e5f4ddebb88ac64506c81548e6ccb</code></td>
        </tr>
        <tr>
            <td><b>s16b</b></td>
            <td><code>811a2aa5d5cd7ba8673f3ca9cc3a89f07c8ac9e1f3f5843fed311557ebc0b9f6</code></td>
        </tr>
        <tr>
            <td><b>s16c</b></td>
            <td><code>8217a2be487140af5bbded5f0dc37ab8cabedaf9af99d16256650ce27a8a5b50</code></td>
        </tr>
        <tr>
            <td><b>s16d</b></td>
            <td><code>c37c642eb06d7ec39364e4a1fac17e606804eee229e047102d4a2e93346e773f</code></td>
        </tr>
        <tr>
            <td><b>s17a</b></td>
            <td><code>a6b691ff0be4af526fb856847be0549dbe015b31b7fb137a1fbbe6027125d4d1</code></td>
        </tr>
        <tr>
            <td><b>s17ar</b></td>
            <td><code>a6b691ff0be4af526fb856847be0549dbe015b31b7fb137a1fbbe6027125d4d1</code></td>
        </tr>
        <tr>
            <td><b>s18a</b></td>
            <td><code>4f605b802aef5c69ce4cc875165d41139acde9af1e9fdf419d0e4cee2bc7087e</code></td>
        </tr>
        <tr>
            <td><b>s18ar</b></td>
            <td><code>17d33d059f09a7470b2e6f44efc2469f52f7ff74093542ffb4cdf52a5aa6c79d</code></td>
        </tr>
        <tr>
            <td><b>s19a</b></td>
            <td><code>48390084a9a716bef980627c57df1867763a6502ad5109d2a6b3712e652840d7</code></td>
        </tr>
        <tr>
            <td><b>s19ar</b></td>
            <td><code>ef64d5fdb5e8285116ee2f8c693bc20f9af802dc6c16996f815d8823127352e6</code></td>
        </tr>
        <tr>
            <td><b>s19b</b></td>
            <td><code>d757942aca5d36ab95741801de1f68526c3a8e128018814f25655b7d72a7c249</code></td>
        </tr>
        <tr>
            <td><b>s19br</b></td>
            <td><code>3d2d7c04d13dd3f55a97348f74eaf891615cfa203812d15494b53f9e570fe2bd</code></td>
        </tr>
        <tr>
            <td><b>s20a</b></td>
            <td><code>d14fdf0f3b5c98f72fd9f24fd119cdf88660528930ec784dc3d021b92e796925</code></td>
        </tr>
        <tr>
            <td><b>s20ar</b></td>
            <td><code>4d6fee8a574d6b900eadff3925f2a38516c2d28784d6e38444ce6c9ece46e104</code></td>
        </tr>
        <tr>
            <td><b>select</b></td>
            <td><code>10350d22ceb73b58224a2da9cc71a87380415e304b4c161a787b491162636bc9</code></td>
        </tr>
        <tr>
            <td><b>select1</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>select2</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>select3</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>select4</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>selectd</b></td>
            <td><code>6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145</code></td>
        </tr>
        <tr>
            <td><b>sound</b></td>
            <td><code>4173d0fcbc7bfcd477d2e0fa6810b509bf6392efb01fd58a7fa114f003849816</code></td>
        </tr>
        <tr>
            <td><b>title</b></td>
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
            <td>Work on it not yet started.</td>
        </tr>
    </tbody>
</table>

## How to build

1.  Install Python 3 if you haven't and make sure it's in your PATH.
2.  Clone down the PsyQ SDK repo from: https://github.com/FoxdieTeam/psyq_sdk.git
3.  Clone down this repo.
4.  Open a terminal and `cd` into the build directory.
5.  Issue the command `pip install -r requirements.txt`.
6.  Issue the command `python build.py --psyq_path=YourPath` where `YourPath` is the location of your cloned psyq_sdk depot.
    - Alternatively you can add `PSYQ_SDK` to your environment variables before invoking `python build.py`.
7.  At the end you should see a message confirming that the built binary's hash matches the original game's binary's hash. If your code caused the compiler to emit warnings, try to fix them without breaking the match.

## How to use the built executables

Once you have successfully built the executables from the source code, you may want to play it to debug or test the changes you have made. Please keep in mind that if the size of the main executable changes or addresses shift, the original [overlays](#Overlays) won't work properly. This guide does not describe how to repackage overlays (a packer tool is planned for the future).

### PCSX-Redux

[PCSX-Redux](https://github.com/grumpycoders/pcsx-redux) emulator provides a convenient way to load a modified main executable. Once you have loaded the original image of *Metal Gear Solid: Integral* you can load a modified executable in "File > Load binary" menu. This repository contains some helper Lua scripts that can be used with PCSX-Redux in `build/pcsx-redux_scripts` folder.

### Other emulators - rebuilding ISO

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

**Now that the work is moving onto overlays, this section is no longer up to date. Please join [our Discord](https://discord.gg/tTvhQ8w) and ask for help in `#metal_gear_dev`.**

Using IDA or Ghidra (with the [ghidra_psx_ldr extension](https://github.com/lab313ru/ghidra_psx_ldr/)) disassemble the original game binary (SLPM-86247), or use one that you compiled yourself provided that the output was OK. Now choose a .s file from the asm directory where that function isn’t part of `psyq`.

Given the address of the function go to this location in your reversing tool. Delete the .s file and search for a .c file which has a `#pragma INCLUDE_ASM()` directive pointing to the former .s file; if none exists, create a .c file with the name of the function and open it. Now write an empty C function that has the same name as the former assembly function as well as a suitable signature; when you re-execute `python build.py`, the build will not be OK as your empty function will no longer build a matching binary.

Now comes the hard part: implement the function such that it matches the functionality of the assembly and build again. Repeat this until your build is OK – ie your C code is functionally the same and produces exactly the same assembly as the original function.

Iterative building is currently unreliable and it is highly recommended to run `python clean.py && python build.py` to be certain that your binary is truly a match.

## Help, I am totally stuck?

Join [our Discord](https://discord.gg/tTvhQ8w) and ask for help in `#metal_gear_dev`.

There are various Ghidra scripts in `build/ghidra_scripts/` to help with decompilation:

- `import_map.py`: when you have produced a matching build, this imports the symbols from the map file into Ghidra;
- `update_data.py`: make sure to read the instructions to this script, which updates data in accordance with declared data types provided they have been imported from header files;
- `update_functions.py`: updates function return types and parameters according to the declarations of matched functions.

It is highly recommended to re-run auto-analysis whenever you have executed these scripts.

We make extensive use of [decomp.me](https://decomp.me/), which has a *Metal Gear Solid* preset, to help match functions; before working on a function, search for it on the website and if you don't find it, go to the `build` folder and run `python decompme_asm.py [path to .s file]` to have the assembly instructions in your clipboard ready to paste into a new decomp.me scratch.
