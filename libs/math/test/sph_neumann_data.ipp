//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

   static const boost::array<boost::array<typename table_type<T>::type, 3>, 284> sph_neumann_data = {{
      {{ SC_(0), SC_(0.177219114266335964202880859375e-2), SC_(-0.5642723324792311990959765396871018960216e3) }}, 
      {{ SC_(0), SC_(0.22177286446094512939453125e-2), SC_(-0.4509106843488238999473616173421364998283e3) }}, 
      {{ SC_(0), SC_(0.7444499991834163665771484375e-2), SC_(-0.1343236336805396008478682587573788632696e3) }}, 
      {{ SC_(0), SC_(0.1433600485324859619140625e-1), SC_(-0.6974727279167912880150678975872617495088e2) }}, 
      {{ SC_(0), SC_(0.1760916970670223236083984375e-1), SC_(-0.5677979025875563956840873378239183466216e2) }}, 
      {{ SC_(0), SC_(0.6152711808681488037109375e-1), SC_(-0.1622224207701819661207370690041340570512e2) }}, 
      {{ SC_(0), SC_(0.11958599090576171875e0), SC_(-0.8302461728079151325461513362583139756373e1) }}, 
      {{ SC_(0), SC_(0.15262925624847412109375e0), SC_(-0.6475657248546134771634572625845233177042e1) }}, 
      {{ SC_(0), SC_(0.408089816570281982421875e0), SC_(-0.2249212131304610409189209411089291558038e1) }}, 
      {{ SC_(0), SC_(0.6540834903717041015625e0), SC_(-0.1213309779166084571756446746977955970241e1) }}, 
      {{ SC_(0), SC_(0.1097540378570556640625e1), SC_(-0.4152801926629981090971418551680239835571e0) }}, 
      {{ SC_(0), SC_(0.30944411754608154296875e1), SC_(0.3228009577028088632835185600650872623482e0) }}, 
      {{ SC_(0), SC_(0.51139926910400390625e1), SC_(-0.7643635410754817824148236191571837220126e-1) }}, 
      {{ SC_(0), SC_(0.95070552825927734375e1), SC_(0.1048292137319730265210439388887370801248e0) }}, 
      {{ SC_(0), SC_(0.24750102996826171875e2), SC_(-0.3748197858988794731118470575529801883541e-1) }}, 
      {{ SC_(0), SC_(0.637722015380859375e2), SC_(-0.9243942787530241818116046978138604629927e-2) }}, 
      {{ SC_(0), SC_(0.1252804412841796875e3), SC_(-0.7402980669441766401839846974565600278467e-2) }}, 
      {{ SC_(0), SC_(0.25554705810546875e3), SC_(0.1851105232770496300381256908203514858216e-2) }}, 
      {{ SC_(0), SC_(0.503011474609375e3), SC_(-0.1862923061767209624572519967199174532136e-2) }}, 
      {{ SC_(0), SC_(0.10074598388671875e4), SC_(0.5434622896619636174822759159195129760936e-3) }}, 
      {{ SC_(0), SC_(0.1185395751953125e4), SC_(0.4448697855794123235553917677921400676563e-3) }}, 
      {{ SC_(0.1e1), SC_(0.177219114266335964202880859375e-2), SC_(-0.318404765200112567469157464785027433823e6) }}, 
      {{ SC_(0.1e1), SC_(0.22177286446094512939453125e-2), SC_(-0.2033219452576704738500460434959917636461e6) }}, 
      {{ SC_(0.1e1), SC_(0.7444499991834163665771484375e-2), SC_(-0.1804433853974285124747494278925454917131e5) }}, 
      {{ SC_(0.1e1), SC_(0.1433600485324859619140625e-1), SC_(-0.486618196768193316259977336624918918276e4) }}, 
      {{ SC_(0.1e1), SC_(0.1760916970670223236083984375e-1), SC_(-0.322544443971191302525452896173067683304e4) }}, 
      {{ SC_(0.1e1), SC_(0.6152711808681488037109375e-1), SC_(-0.2646594036812657100698306327292119166165e3) }}, 
      {{ SC_(0.1e1), SC_(0.11958599090576171875e0), SC_(-0.704243267085761836707775439192578042573e2) }}, 
      {{ SC_(0.1e1), SC_(0.15262925624847412109375e0), SC_(-0.434234874553672313920027034930149194407e2) }}, 
      {{ SC_(0.1e1), SC_(0.408089816570281982421875e0), SC_(-0.6484035515444221775976367630376209298567e1) }}, 
      {{ SC_(0.1e1), SC_(0.6540834903717041015625e0), SC_(-0.2785182560801830440325676905703325489184e1) }}, 
      {{ SC_(0.1e1), SC_(0.1097540378570556640625e1), SC_(-0.1189358686761883310370162855037394165611e1) }}, 
      {{ SC_(0.1e1), SC_(0.30944411754608154296875e1), SC_(0.8908456605946127242501038405190438284591e-1) }}, 
      {{ SC_(0.1e1), SC_(0.51139926910400390625e1), SC_(0.1650371817824980920597277760628969935339e0) }}, 
      {{ SC_(0.1e1), SC_(0.95070552825927734375e1), SC_(0.1967104757813801271824802511806652238075e-1) }}, 
      {{ SC_(0.1e1), SC_(0.24750102996826171875e2), SC_(0.1357114472738293735380837736920673513642e-1) }}, 
      {{ SC_(0.1e1), SC_(0.637722015380859375e2), SC_(-0.1281134249246794610073876109037108992935e-1) }}, 
      {{ SC_(0.1e1), SC_(0.1252804412841796875e3), SC_(0.2925815571849156117920315547136950241325e-2) }}, 
      {{ SC_(0.1e1), SC_(0.25554705810546875e3), SC_(0.3454900436576811073075917245701360162869e-2) }}, 
      {{ SC_(0.1e1), SC_(0.503011474609375e3), SC_(-0.6977971312135198156036217479682334535885e-3) }}, 
      {{ SC_(0.1e1), SC_(0.10074598388671875e4), SC_(-0.830059360518605915833351761559017133065e-3) }}, 
      {{ SC_(0.1e1), SC_(0.1185395751953125e4), SC_(0.7171402734520886334015615434326112966186e-3) }}, 
      {{ SC_(0.2e1), SC_(0.177219114266335964202880859375e-2), SC_(-0.5390012807345113883197792587292120542031e9) }}, 
      {{ SC_(0.2e1), SC_(0.22177286446094512939453125e-2), SC_(-0.2750403378962024584351226505492891996551e9) }}, 
      {{ SC_(0.2e1), SC_(0.7444499991834163665771484375e-2), SC_(-0.7271410532113085385774156481477356217156e7) }}, 
      {{ SC_(0.2e1), SC_(0.1433600485324859619140625e-1), SC_(-0.1018243656809079180564791631983824027866e7) }}, 
      {{ SC_(0.2e1), SC_(0.1760916970670223236083984375e-1), SC_(-0.5494485904403902454288040447187085252735e6) }}, 
      {{ SC_(0.2e1), SC_(0.6152711808681488037109375e-1), SC_(-0.1288830239246692985269728537863836376468e5) }}, 
      {{ SC_(0.2e1), SC_(0.11958599090576171875e0), SC_(-0.1758400966704601107905829221340068593333e4) }}, 
      {{ SC_(0.2e1), SC_(0.15262925624847412109375e0), SC_(-0.8470334639256196191828910705235499636086e3) }}, 
      {{ SC_(0.2e1), SC_(0.408089816570281982421875e0), SC_(-0.4541702641837159203058389758895634766256e2) }}, 
      {{ SC_(0.2e1), SC_(0.6540834903717041015625e0), SC_(-0.1156112621471167110574129561700037138981e2) }}, 
      {{ SC_(0.2e1), SC_(0.1097540378570556640625e1), SC_(-0.2835694559566832562081631532476610393593e1) }}, 
      {{ SC_(0.2e1), SC_(0.30944411754608154296875e1), SC_(-0.2364352189394648962564115002206693193264e0) }}, 
      {{ SC_(0.2e1), SC_(0.51139926910400390625e1), SC_(0.1732514211714791641487261827982664865146e0) }}, 
      {{ SC_(0.2e1), SC_(0.95070552825927734375e1), SC_(-0.9862191389198304425904745146753435952401e-1) }}, 
      {{ SC_(0.2e1), SC_(0.24750102996826171875e2), SC_(0.3912695898400467874867999209317768037635e-1) }}, 
      {{ SC_(0.2e1), SC_(0.637722015380859375e2), SC_(0.8641265969881876225898539254984860529714e-2) }}, 
      {{ SC_(0.2e1), SC_(0.1252804412841796875e3), SC_(0.7473043056080692435099953164437164248053e-2) }}, 
      {{ SC_(0.2e1), SC_(0.25554705810546875e3), SC_(-0.1810546357287559849120539213331049290221e-2) }}, 
      {{ SC_(0.2e1), SC_(0.503011474609375e3), SC_(0.1858761344789945377984398470433340989203e-2) }}, 
      {{ SC_(0.2e1), SC_(0.10074598388671875e4), SC_(-0.5459340289665852636696979017491079500449e-3) }}, 
      {{ SC_(0.2e1), SC_(0.1185395751953125e4), SC_(-0.4430548467146395559544067187824537160368e-3) }}, 
      {{ SC_(0.4e1), SC_(0.177219114266335964202880859375e-2), SC_(-0.6006708939031862782547423129663205631395e16) }}, 
      {{ SC_(0.4e1), SC_(0.22177286446094512939453125e-2), SC_(-0.1957255048386226906846149698887287471033e16) }}, 
      {{ SC_(0.4e1), SC_(0.7444499991834163665771484375e-2), SC_(-0.4592121279331724272683855783141568753333e13) }}, 
      {{ SC_(0.4e1), SC_(0.1433600485324859619140625e-1), SC_(-0.173402349594767269025145292017473455282e12) }}, 
      {{ SC_(0.4e1), SC_(0.1760916970670223236083984375e-1), SC_(-0.6201611030027830575236750989101389849364e11) }}, 
      {{ SC_(0.4e1), SC_(0.6152711808681488037109375e-1), SC_(-0.1191170341565551054056618133292811190739e9) }}, 
      {{ SC_(0.4e1), SC_(0.11958599090576171875e0), SC_(-0.4297654348662493392476039106116454381053e7) }}, 
      {{ SC_(0.4e1), SC_(0.15262925624847412109375e0), SC_(-0.1269764721301016237085922161946420176713e7) }}, 
      {{ SC_(0.4e1), SC_(0.408089816570281982421875e0), SC_(-0.938834620739078580225698168692023203448e4) }}, 
      {{ SC_(0.4e1), SC_(0.6540834903717041015625e0), SC_(-0.9044373064697326637009564699789610374151e3) }}, 
      {{ SC_(0.4e1), SC_(0.1097540378570556640625e1), SC_(-0.7197096999109657262465719753479013842004e2) }}, 
      {{ SC_(0.4e1), SC_(0.30944411754608154296875e1), SC_(-0.8292878001802161021682270451154977977337e0) }}, 
      {{ SC_(0.4e1), SC_(0.51139926910400390625e1), SC_(-0.1672938782320394591130634026396133319056e0) }}, 
      {{ SC_(0.4e1), SC_(0.95070552825927734375e1), SC_(0.4594823416227780746480571313224025888457e-1) }}, 
      {{ SC_(0.4e1), SC_(0.24750102996826171875e2), SC_(-0.4072966707158819427744567215857101892826e-1) }}, 
      {{ SC_(0.4e1), SC_(0.637722015380859375e2), SC_(-0.7160652662228105175773913698625518194443e-2) }}, 
      {{ SC_(0.4e1), SC_(0.1252804412841796875e3), SC_(-0.7619857201446145509948734118435483624086e-2) }}, 
      {{ SC_(0.4e1), SC_(0.25554705810546875e3), SC_(0.1714938614376801147928666041967663272554e-2) }}, 
      {{ SC_(0.4e1), SC_(0.503011474609375e3), SC_(-0.1848793551823628970369126596953626884517e-2) }}, 
      {{ SC_(0.4e1), SC_(0.10074598388671875e4), SC_(0.5516825949084002964790973918927589969002e-3) }}, 
      {{ SC_(0.4e1), SC_(0.1185395751953125e4), SC_(0.4388089536910184022488035482968780382212e-3) }}, 
      {{ SC_(0.7e1), SC_(0.177219114266335964202880859375e-2), SC_(-0.1388939744137340433522522155157803129493e28) }}, 
      {{ SC_(0.7e1), SC_(0.22177286446094512939453125e-2), SC_(-0.2309408077963500230051756342440986301973e27) }}, 
      {{ SC_(0.7e1), SC_(0.7444499991834163665771484375e-2), SC_(-0.1432466589853457118157199163927226239105e23) }}, 
      {{ SC_(0.7e1), SC_(0.1433600485324859619140625e-1), SC_(-0.7574363861874272531180922496759086862498e20) }}, 
      {{ SC_(0.7e1), SC_(0.1760916970670223236083984375e-1), SC_(-0.1461712611084380044913310721560950112306e20) }}, 
      {{ SC_(0.7e1), SC_(0.6152711808681488037109375e-1), SC_(-0.6581100049139522866420337381107024877831e15) }}, 
      {{ SC_(0.7e1), SC_(0.11958599090576171875e0), SC_(-0.3232691649492879334595332596749659857755e13) }}, 
      {{ SC_(0.7e1), SC_(0.15262925624847412109375e0), SC_(-0.4592558497626386579457472880231329928345e12) }}, 
      {{ SC_(0.7e1), SC_(0.408089816570281982421875e0), SC_(-0.1768093332349639873943590983950796618094e9) }}, 
      {{ SC_(0.7e1), SC_(0.6540834903717041015625e0), SC_(-0.410071253550436848907977153943779570177e7) }}, 
      {{ SC_(0.7e1), SC_(0.1097540378570556640625e1), SC_(-0.6723738931189786892469511427815554534622e5) }}, 
      {{ SC_(0.7e1), SC_(0.30944411754608154296875e1), SC_(-0.2355914723945007502048313939035727585535e2) }}, 
      {{ SC_(0.7e1), SC_(0.51139926910400390625e1), SC_(-0.9095841466009625950437779235402980858269e0) }}, 
      {{ SC_(0.7e1), SC_(0.95070552825927734375e1), SC_(0.4137038128161563987674845255425727782835e-2) }}, 
      {{ SC_(0.7e1), SC_(0.24750102996826171875e2), SC_(0.2840265140460042677367989989206316229572e-1) }}, 
      {{ SC_(0.7e1), SC_(0.637722015380859375e2), SC_(0.1544929171899375325706484638266664284005e-1) }}, 
      {{ SC_(0.7e1), SC_(0.1252804412841796875e3), SC_(-0.1270517672039039606712892170401020621663e-2) }}, 
      {{ SC_(0.7e1), SC_(0.25554705810546875e3), SC_(-0.3630188911697934815681636175552688093357e-2) }}, 
      {{ SC_(0.7e1), SC_(0.503011474609375e3), SC_(0.7967098511734288574306139155656730858314e-3) }}, 
      {{ SC_(0.7e1), SC_(0.10074598388671875e4), SC_(0.815186884113040002201698678223896056766e-3) }}, 
      {{ SC_(0.7e1), SC_(0.1185395751953125e4), SC_(-0.7270795125271877654141198243699517038649e-3) }}, 
      {{ SC_(0.1e2), SC_(0.1433600485324859619140625e-1), SC_(-0.1245530719806351448480124937794738961635e30) }}, 
      {{ SC_(0.1e2), SC_(0.1760916970670223236083984375e-1), SC_(-0.1296992613685647077229845683943181048821e29) }}, 
      {{ SC_(0.1e2), SC_(0.6152711808681488037109375e-1), SC_(-0.1368902717654920136735378996175836140785e23) }}, 
      {{ SC_(0.1e2), SC_(0.11958599090576171875e0), SC_(-0.9156757241161448651951539042135995904994e19) }}, 
      {{ SC_(0.1e2), SC_(0.15262925624847412109375e0), SC_(-0.6256222869032686140322813275452916410343e18) }}, 
      {{ SC_(0.1e2), SC_(0.408089816570281982421875e0), SC_(-0.1257917349261965601916962527396933303977e14) }}, 
      {{ SC_(0.1e2), SC_(0.6540834903717041015625e0), SC_(-0.7063002197882333005631618484528652399524e11) }}, 
      {{ SC_(0.1e2), SC_(0.1097540378570556640625e1), SC_(-0.2427889658115064857278886600528596240123e9) }}, 
      {{ SC_(0.1e2), SC_(0.30944411754608154296875e1), SC_(-0.3394649246350136450439882104151313759251e4) }}, 
      {{ SC_(0.1e2), SC_(0.51139926910400390625e1), SC_(-0.2150737348962304792352416315737126587418e2) }}, 
      {{ SC_(0.1e2), SC_(0.95070552825927734375e1), SC_(-0.2157691001768484850020828031987882855639e0) }}, 
      {{ SC_(0.1e2), SC_(0.24750102996826171875e2), SC_(-0.1260876938605482558721300295302574251533e-1) }}, 
      {{ SC_(0.1e2), SC_(0.637722015380859375e2), SC_(-0.3658561196157287230123135947541224109443e-2) }}, 
      {{ SC_(0.1e2), SC_(0.1252804412841796875e3), SC_(0.7983606267849351237703135831852105823276e-2) }}, 
      {{ SC_(0.1e2), SC_(0.25554705810546875e3), SC_(-0.1072436715227848668749084256488184819454e-2) }}, 
      {{ SC_(0.1e2), SC_(0.503011474609375e3), SC_(0.1776245695123382255186007833872594145979e-2) }}, 
      {{ SC_(0.1e2), SC_(0.10074598388671875e4), SC_(-0.5879910859563235660929418753761246514854e-3) }}, 
      {{ SC_(0.1e2), SC_(0.1185395751953125e4), SC_(-0.411154319810368570839418603704906353283e-3) }}, 
      {{ SC_(0.13e2), SC_(0.6152711808681488037109375e-1), SC_(-0.7096588472433714153042022789489333121863e30) }}, 
      {{ SC_(0.13e2), SC_(0.11958599090576171875e0), SC_(-0.6464704713743915427301824299819781954859e26) }}, 
      {{ SC_(0.13e2), SC_(0.15262925624847412109375e0), SC_(-0.2124330495066614710929484795599742959654e25) }}, 
      {{ SC_(0.13e2), SC_(0.408089816570281982421875e0), SC_(-0.2232620432299327594678167214732483417736e19) }}, 
      {{ SC_(0.13e2), SC_(0.6540834903717041015625e0), SC_(-0.3039495964028968670551250826703930725596e16) }}, 
      {{ SC_(0.13e2), SC_(0.1097540378570556640625e1), SC_(-0.2200572297449479637006380190194549845276e13) }}, 
      {{ SC_(0.13e2), SC_(0.30944411754608154296875e1), SC_(-0.1299211572249285551909779637874602972508e7) }}, 
      {{ SC_(0.13e2), SC_(0.51139926910400390625e1), SC_(-0.1614426118247726564069541604511986952086e4) }}, 
      {{ SC_(0.13e2), SC_(0.95070552825927734375e1), SC_(-0.1192876773324610978227972311096425254541e1) }}, 
      {{ SC_(0.13e2), SC_(0.24750102996826171875e2), SC_(0.1083090330001395226011081713405820116194e-1) }}, 
      {{ SC_(0.13e2), SC_(0.637722015380859375e2), SC_(-0.1103112564518912696072370568742481339126e-1) }}, 
      {{ SC_(0.13e2), SC_(0.1252804412841796875e3), SC_(-0.2698254042376059943851702235540482168386e-2) }}, 
      {{ SC_(0.13e2), SC_(0.25554705810546875e3), SC_(0.3879446011377107269956022967187011973557e-2) }}, 
      {{ SC_(0.13e2), SC_(0.503011474609375e3), SC_(-0.1018154003350369531009009098099277689641e-2) }}, 
      {{ SC_(0.13e2), SC_(0.10074598388671875e4), SC_(-0.7782246846650067854491204003191128582844e-3) }}, 
      {{ SC_(0.13e2), SC_(0.1185395751953125e4), SC_(0.7487965903672491559847491642545850030768e-3) }}, 
      {{ SC_(0.16e2), SC_(0.408089816570281982421875e0), SC_(-0.7968764716391730011103329636034855328962e24) }}, 
      {{ SC_(0.16e2), SC_(0.6540834903717041015625e0), SC_(-0.2632119245040565674510100654677927787303e21) }}, 
      {{ SC_(0.16e2), SC_(0.1097540378570556640625e1), SC_(-0.4021306302655656019280730356166023954594e17) }}, 
      {{ SC_(0.16e2), SC_(0.30944411754608154296875e1), SC_(-0.1024734904321332361176888712960645982827e10) }}, 
      {{ SC_(0.16e2), SC_(0.51139926910400390625e1), SC_(-0.263104548681619029365595821516581062838e6) }}, 
      {{ SC_(0.16e2), SC_(0.95070552825927734375e1), SC_(-0.212434709466762829773238681303207117582e2) }}, 
      {{ SC_(0.16e2), SC_(0.24750102996826171875e2), SC_(-0.2743563165647313690782258876808431412109e-1) }}, 
      {{ SC_(0.16e2), SC_(0.637722015380859375e2), SC_(0.1592868538765449864728958003322337214849e-1) }}, 
      {{ SC_(0.16e2), SC_(0.1252804412841796875e3), SC_(-0.611189995982529806498215807361518117186e-2) }}, 
      {{ SC_(0.16e2), SC_(0.25554705810546875e3), SC_(-0.1551975946286214383853261368195650834803e-3) }}, 
      {{ SC_(0.16e2), SC_(0.503011474609375e3), SC_(-0.1610266445943186662771155287434094951638e-2) }}, 
      {{ SC_(0.16e2), SC_(0.10074598388671875e4), SC_(0.650348574795961322341087383056013722587e-3) }}, 
      {{ SC_(0.16e2), SC_(0.1185395751953125e4), SC_(0.3599072645317034685633234775339363892989e-3) }}, 
      {{ SC_(0.19e2), SC_(0.408089816570281982421875e0), SC_(-0.5008621620829854006954623536723536260922e30) }}, 
      {{ SC_(0.19e2), SC_(0.6540834903717041015625e0), SC_(-0.4015165392251303629512256297488777013034e26) }}, 
      {{ SC_(0.19e2), SC_(0.1097540378570556640625e1), SC_(-0.1295742383468043411565809880265553984875e22) }}, 
      {{ SC_(0.19e2), SC_(0.30944411754608154296875e1), SC_(-0.1440850060936814966263451261627483470922e13) }}, 
      {{ SC_(0.19e2), SC_(0.51139926910400390625e1), SC_(-0.7829560726823223330394765378802240654337e8) }}, 
      {{ SC_(0.19e2), SC_(0.95070552825927734375e1), SC_(-0.8017774502788714016096257024597920080947e3) }}, 
      {{ SC_(0.19e2), SC_(0.24750102996826171875e2), SC_(0.5104725068940265807623171340563537419839e-1) }}, 
      {{ SC_(0.19e2), SC_(0.637722015380859375e2), SC_(-0.1154540926504216331530538721227045039394e-1) }}, 
      {{ SC_(0.19e2), SC_(0.1252804412841796875e3), SC_(0.7285128790438104181486799657416599622562e-2) }}, 
      {{ SC_(0.19e2), SC_(0.25554705810546875e3), SC_(-0.3795974512769646959066511811760180003581e-2) }}, 
      {{ SC_(0.19e2), SC_(0.503011474609375e3), SC_(0.1332792253280798715550694041485478947804e-2) }}, 
      {{ SC_(0.19e2), SC_(0.10074598388671875e4), SC_(0.7140475084390964023422450272059931346758e-3) }}, 
      {{ SC_(0.19e2), SC_(0.1185395751953125e4), SC_(-0.778631877582065133128398725986021189756e-3) }}, 
      {{ SC_(0.22e2), SC_(0.1097540378570556640625e1), SC_(-0.6723360495833044373602236204563863321495e26) }}, 
      {{ SC_(0.22e2), SC_(0.30944411754608154296875e1), SC_(-0.3282992248392472051808450625423987455518e16) }}, 
      {{ SC_(0.22e2), SC_(0.51139926910400390625e1), SC_(-0.3826147075920552238475280662776521115203e11) }}, 
      {{ SC_(0.22e2), SC_(0.95070552825927734375e1), SC_(-0.5311187095528196500675385994412924026797e5) }}, 
      {{ SC_(0.22e2), SC_(0.24750102996826171875e2), SC_(-0.1306396947235207229685397581368310264004e-1) }}, 
      {{ SC_(0.22e2), SC_(0.637722015380859375e2), SC_(0.3811910734895598722091331392361204163648e-2) }}, 
      {{ SC_(0.22e2), SC_(0.1252804412841796875e3), SC_(-0.5694609931721205895231828943722573661955e-3) }}, 
      {{ SC_(0.22e2), SC_(0.25554705810546875e3), SC_(0.1872575932276900334277205173009240761345e-2) }}, 
      {{ SC_(0.22e2), SC_(0.503011474609375e3), SC_(0.1298158890481958119897857861962977581478e-2) }}, 
      {{ SC_(0.22e2), SC_(0.10074598388671875e4), SC_(-0.7329138049351166151988684874280432719372e-3) }}, 
      {{ SC_(0.22e2), SC_(0.1185395751953125e4), SC_(-0.2829751774429469196812768758194950064622e-3) }}, 
      {{ SC_(0.25e2), SC_(0.30944411754608154296875e1), SC_(-0.1132569536096268337562080171402201939034e20) }}, 
      {{ SC_(0.25e2), SC_(0.51139926910400390625e1), SC_(-0.2854197487832370443625499582893796948668e14) }}, 
      {{ SC_(0.25e2), SC_(0.95070552825927734375e1), SC_(-0.557640638109575874026675246942198134901e7) }}, 
      {{ SC_(0.25e2), SC_(0.24750102996826171875e2), SC_(-0.8289220371234890898107740191499805665166e-1) }}, 
      {{ SC_(0.25e2), SC_(0.637722015380859375e2), SC_(0.2867466802758145719509918727955672959562e-2) }}, 
      {{ SC_(0.25e2), SC_(0.1252804412841796875e3), SC_(-0.6426359266478851874122389488976604772913e-2) }}, 
      {{ SC_(0.25e2), SC_(0.25554705810546875e3), SC_(0.2788655268268470964688490819519378700901e-2) }}, 
      {{ SC_(0.25e2), SC_(0.503011474609375e3), SC_(-0.1677047836678118060016484817598253328862e-2) }}, 
      {{ SC_(0.25e2), SC_(0.10074598388671875e4), SC_(-0.6155464006245052959192750335825837759874e-3) }}, 
      {{ SC_(0.25e2), SC_(0.1185395751953125e4), SC_(0.8105378192860076835295337545544333320285e-3) }}, 
      {{ SC_(0.28e2), SC_(0.30944411754608154296875e1), SC_(-0.5621747105301521557947179246637760022417e23) }}, 
      {{ SC_(0.28e2), SC_(0.51139926910400390625e1), SC_(-0.3080131695608097771147596640961172595909e17) }}, 
      {{ SC_(0.28e2), SC_(0.95070552825927734375e1), SC_(-0.8673370399593050580914898499273415127644e9) }}, 
      {{ SC_(0.28e2), SC_(0.24750102996826171875e2), SC_(-0.2256097627150219672124131497323287189991e0) }}, 
      {{ SC_(0.28e2), SC_(0.637722015380859375e2), SC_(-0.6991956238153252791738685651136169064703e-2) }}, 
      {{ SC_(0.28e2), SC_(0.1252804412841796875e3), SC_(0.7795645183045974969575002412572072101911e-2) }}, 
      {{ SC_(0.28e2), SC_(0.25554705810546875e3), SC_(-0.3494172391974151981967644744599232334284e-2) }}, 
      {{ SC_(0.28e2), SC_(0.503011474609375e3), SC_(-0.7872272246020384880492778519333779147176e-3) }}, 
      {{ SC_(0.28e2), SC_(0.10074598388671875e4), SC_(0.825845271938107790489284932094733926616e-3) }}, 
      {{ SC_(0.28e2), SC_(0.1185395751953125e4), SC_(0.1783213113986488862036590535806820370025e-3) }}, 
      {{ SC_(0.31e2), SC_(0.30944411754608154296875e1), SC_(-0.3858743092234085837491563707437405089502e27) }}, 
      {{ SC_(0.31e2), SC_(0.51139926910400390625e1), SC_(-0.4613835194622917257572168439667276505091e20) }}, 
      {{ SC_(0.31e2), SC_(0.95070552825927734375e1), SC_(-0.1902866311295072781213762448066992585084e12) }}, 
      {{ SC_(0.31e2), SC_(0.24750102996826171875e2), SC_(-0.1242902083875520340476461862360617369865e1) }}, 
      {{ SC_(0.31e2), SC_(0.637722015380859375e2), SC_(0.8602616475850209207115672961665438799578e-2) }}, 
      {{ SC_(0.31e2), SC_(0.1252804412841796875e3), SC_(-0.3568328873757026723718279708146103263332e-2) }}, 
      {{ SC_(0.31e2), SC_(0.25554705810546875e3), SC_(-0.4708447548154973984774979548889890332232e-3) }}, 
      {{ SC_(0.31e2), SC_(0.503011474609375e3), SC_(0.1938585486734996435913653188875075463759e-2) }}, 
      {{ SC_(0.31e2), SC_(0.10074598388671875e4), SC_(0.4751515606683130102889789705916848210342e-3) }}, 
      {{ SC_(0.31e2), SC_(0.1185395751953125e4), SC_(-0.8358404490289695691960973315323391126047e-3) }}, 
      {{ SC_(0.34e2), SC_(0.51139926910400390625e1), SC_(-0.9282996603826470817559175093201479899353e23) }}, 
      {{ SC_(0.34e2), SC_(0.95070552825927734375e1), SC_(-0.5671896870965902667567112773375443299376e14) }}, 
      {{ SC_(0.34e2), SC_(0.24750102996826171875e2), SC_(-0.1196836896972653347610997098886066849879e2) }}, 
      {{ SC_(0.34e2), SC_(0.637722015380859375e2), SC_(-0.7840611740006562731867360753764337981193e-2) }}, 
      {{ SC_(0.34e2), SC_(0.1252804412841796875e3), SC_(-0.2528119461363815663298862242098595394995e-2) }}, 
      {{ SC_(0.34e2), SC_(0.25554705810546875e3), SC_(0.3790521728300347929686504759069995348496e-2) }}, 
      {{ SC_(0.34e2), SC_(0.503011474609375e3), SC_(0.6131119580874945273384687636612133212937e-4) }}, 
      {{ SC_(0.34e2), SC_(0.10074598388671875e4), SC_(-0.9142183498980430984586827864611642159497e-3) }}, 
      {{ SC_(0.34e2), SC_(0.1185395751953125e4), SC_(-0.4511848776391923835124583337569697441159e-4) }}, 
      {{ SC_(0.37e2), SC_(0.51139926910400390625e1), SC_(-0.2442375728698405242925453667580696210245e27) }}, 
      {{ SC_(0.37e2), SC_(0.95070552825927734375e1), SC_(-0.2229542216375343293897440256273780674204e17) }}, 
      {{ SC_(0.37e2), SC_(0.24750102996826171875e2), SC_(-0.1737444169853745325867053393033933403419e3) }}, 
      {{ SC_(0.37e2), SC_(0.637722015380859375e2), SC_(0.4279824575041896675727883899347662880186e-2) }}, 
      {{ SC_(0.37e2), SC_(0.1252804412841796875e3), SC_(0.6929401282911254411240566948180148883389e-2) }}, 
      {{ SC_(0.37e2), SC_(0.25554705810546875e3), SC_(-0.2511648418349492118440212332844329555998e-2) }}, 
      {{ SC_(0.37e2), SC_(0.503011474609375e3), SC_(-0.1957162644941089839867703502493036932186e-2) }}, 
      {{ SC_(0.37e2), SC_(0.10074598388671875e4), SC_(-0.2872884073535241094708945526011230038645e-3) }}, 
      {{ SC_(0.37e2), SC_(0.1185395751953125e4), SC_(0.8432140708713275871141861113932655356805e-3) }}, 
      {{ SC_(0.4e2), SC_(0.95070552825927734375e1), SC_(-0.1128026063781401159493204975300213163583e20) }}, 
      {{ SC_(0.4e2), SC_(0.24750102996826171875e2), SC_(-0.3536320450284364302528532664762113675546e4) }}, 
      {{ SC_(0.4e2), SC_(0.637722015380859375e2), SC_(0.2749332472515275038091640131810993326854e-2) }}, 
      {{ SC_(0.4e2), SC_(0.1252804412841796875e3), SC_(-0.8189335561734438098491340276810366230728e-2) }}, 
      {{ SC_(0.4e2), SC_(0.25554705810546875e3), SC_(-0.1601472101873495352874904527747422350107e-2) }}, 
      {{ SC_(0.4e2), SC_(0.503011474609375e3), SC_(0.8063429370382054903944011477925178824483e-3) }}, 
      {{ SC_(0.4e2), SC_(0.10074598388671875e4), SC_(0.9774185681131416958979641163273033546007e-3) }}, 
      {{ SC_(0.4e2), SC_(0.1185395751953125e4), SC_(-0.1146975806174666671253112473359257996345e-3) }}, 
      {{ SC_(0.43e2), SC_(0.95070552825927734375e1), SC_(-0.7198591295447037635860529334856057232135e22) }}, 
      {{ SC_(0.43e2), SC_(0.24750102996826171875e2), SC_(-0.9641200720117521887788006798691601480704e5) }}, 
      {{ SC_(0.43e2), SC_(0.637722015380859375e2), SC_(-0.1236200080963258936021132338688942409822e-1) }}, 
      {{ SC_(0.43e2), SC_(0.1252804412841796875e3), SC_(0.6766741286829961971926652018652618379149e-2) }}, 
      {{ SC_(0.43e2), SC_(0.25554705810546875e3), SC_(0.3930507468976728535272404195834679836265e-2) }}, 
      {{ SC_(0.43e2), SC_(0.503011474609375e3), SC_(0.1564028674659955458649814316707562782221e-2) }}, 
      {{ SC_(0.43e2), SC_(0.10074598388671875e4), SC_(0.5187580633057582060435802616437238457919e-4) }}, 
      {{ SC_(0.43e2), SC_(0.1185395751953125e4), SC_(-0.8191603697467604740041636746614045025268e-3) }}, 
      {{ SC_(0.46e2), SC_(0.95070552825927734375e1), SC_(-0.5695769033255529210361047038599776733494e25) }}, 
      {{ SC_(0.46e2), SC_(0.24750102996826171875e2), SC_(-0.3407542572880364861061570256982516465991e7) }}, 
      {{ SC_(0.46e2), SC_(0.637722015380859375e2), SC_(0.1892031070374081055519173538522022424373e-1) }}, 
      {{ SC_(0.46e2), SC_(0.1252804412841796875e3), SC_(-0.3930999501654252080115547096167591365109e-2) }}, 
      {{ SC_(0.46e2), SC_(0.25554705810546875e3), SC_(-0.2252774787151350219685297262688267474083e-2) }}, 
      {{ SC_(0.46e2), SC_(0.503011474609375e3), SC_(-0.160470127490624290303361714195055152753e-2) }}, 
      {{ SC_(0.46e2), SC_(0.10074598388671875e4), SC_(-0.9898053187382996942921915807261270222834e-3) }}, 
      {{ SC_(0.46e2), SC_(0.1185395751953125e4), SC_(0.2945850112272429804450537869110995190276e-3) }}, 
      {{ SC_(0.49e2), SC_(0.95070552825927734375e1), SC_(-0.5505988900115077682063953616131381316684e28) }}, 
      {{ SC_(0.49e2), SC_(0.24750102996826171875e2), SC_(-0.1522647860770080599776352342021496844231e9) }}, 
      {{ SC_(0.49e2), SC_(0.637722015380859375e2), SC_(-0.117811227613905121473227334683521728565e-1) }}, 
      {{ SC_(0.49e2), SC_(0.1252804412841796875e3), SC_(0.8581798088552142472627658285170409572199e-3) }}, 
      {{ SC_(0.49e2), SC_(0.25554705810546875e3), SC_(-0.1525297082577234374630319883497973286237e-2) }}, 
      {{ SC_(0.49e2), SC_(0.503011474609375e3), SC_(-0.6789386510763052793814186176994423811279e-3) }}, 
      {{ SC_(0.49e2), SC_(0.10074598388671875e4), SC_(0.2213660813860061497235236488103940641175e-3) }}, 
      {{ SC_(0.49e2), SC_(0.1185395751953125e4), SC_(0.7493404081650790642056171825780752281226e-3) }}, 
      {{ SC_(0.52e2), SC_(0.24750102996826171875e2), SC_(-0.8431613692546440958427835805924554720791e10) }}, 
      {{ SC_(0.52e2), SC_(0.637722015380859375e2), SC_(-0.1115225300535010626455229302801432083119e-1) }}, 
      {{ SC_(0.52e2), SC_(0.1252804412841796875e3), SC_(0.1744660661299516008597246745970354205394e-2) }}, 
      {{ SC_(0.52e2), SC_(0.25554705810546875e3), SC_(0.3871637644673301315119914349891630279192e-2) }}, 
      {{ SC_(0.52e2), SC_(0.503011474609375e3), SC_(0.1991638261007561367287975226510189975247e-2) }}, 
      {{ SC_(0.52e2), SC_(0.10074598388671875e4), SC_(0.9236248731028976631695212457160479065712e-3) }}, 
      {{ SC_(0.52e2), SC_(0.1185395751953125e4), SC_(-0.4815665463345610915674607850479789186718e-3) }}, 
      {{ SC_(0.55e2), SC_(0.24750102996826171875e2), SC_(-0.5691393603639469399255323205962188964084e12) }}, 
      {{ SC_(0.55e2), SC_(0.637722015380859375e2), SC_(0.2006392327938634300862385080463293572511e-1) }}, 
      {{ SC_(0.55e2), SC_(0.1252804412841796875e3), SC_(-0.3619108023378490361858076559653708839139e-2) }}, 
      {{ SC_(0.55e2), SC_(0.25554705810546875e3), SC_(-0.2962856754548850012378937612844037689574e-2) }}, 
      {{ SC_(0.55e2), SC_(0.503011474609375e3), SC_(-0.5505670779964820186689463080699492719812e-3) }}, 
      {{ SC_(0.55e2), SC_(0.10074598388671875e4), SC_(-0.5086536723538768197623992809520331865266e-3) }}, 
      {{ SC_(0.55e2), SC_(0.1185395751953125e4), SC_(-0.6210859629328079732529943111160023713285e-3) }}, 
      {{ SC_(0.58e2), SC_(0.24750102996826171875e2), SC_(-0.4618503933439028301329509946039169091138e14) }}, 
      {{ SC_(0.58e2), SC_(0.637722015380859375e2), SC_(0.1402558269735743898212790386772249256841e-1) }}, 
      {{ SC_(0.58e2), SC_(0.1252804412841796875e3), SC_(0.4775384619486356255055098430929380737203e-2) }}, 
      {{ SC_(0.58e2), SC_(0.25554705810546875e3), SC_(-0.2015373395162996137089683702058573806025e-3) }}, 
      {{ SC_(0.58e2), SC_(0.503011474609375e3), SC_(-0.1623050637742511470123447378958753891598e-2) }}, 
      {{ SC_(0.58e2), SC_(0.10074598388671875e4), SC_(-0.7550604452502297124697636692423906683648e-3) }}, 
      {{ SC_(0.58e2), SC_(0.1185395751953125e4), SC_(0.6549895436356671365157678660370603606525e-3) }}, 
      {{ SC_(0.61e2), SC_(0.24750102996826171875e2), SC_(-0.4452493733367375303990916467937068229415e16) }}, 
      {{ SC_(0.61e2), SC_(0.637722015380859375e2), SC_(-0.1321805471789013172474419554540756891808e-1) }}, 
      {{ SC_(0.61e2), SC_(0.1252804412841796875e3), SC_(-0.531088356762363908667551449646716451263e-2) }}, 
      {{ SC_(0.61e2), SC_(0.25554705810546875e3), SC_(0.3137411891941427755699863352585675704239e-2) }}, 
      {{ SC_(0.61e2), SC_(0.503011474609375e3), SC_(0.1656289965758384211758434873072034259055e-2) }}, 
      {{ SC_(0.61e2), SC_(0.10074598388671875e4), SC_(0.7696420775050426274332928912448241809519e-3) }}, 
      {{ SC_(0.61e2), SC_(0.1185395751953125e4), SC_(0.4272402417161322625448726249065820441606e-3) }}
   }};


