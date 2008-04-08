#define SC_(x) static_cast<T>(BOOST_JOIN(x, L))
   static const boost::array<boost::array<T, 2>, 200> zeta_data = {{
      { SC_(1.16628754138946533203125), SC_(6.602868183069916948720755731837247651904) }, 
      { SC_(1.28222560882568359375), SC_(4.140637712279411074557164685415721499333) }, 
      { SC_(1.7022221088409423828125), SC_(2.049914055577335303673424130546639695977) }, 
      { SC_(1.79880845546722412109375), SC_(1.884017213259316830925461356827163589705) }, 
      { SC_(2.048659801483154296875), SC_(1.601558368429615698519833097274473510457) }, 
      { SC_(2.8781378269195556640625), SC_(1.228101328930692778618914405979886894909) }, 
      { SC_(3.032318592071533203125), SC_(1.195776877916973414012665761751705560617) }, 
      { SC_(3.1069891452789306640625), SC_(1.182159242558432231709092493922425008201) }, 
      { SC_(3.1500339508056640625), SC_(1.174833816740130223224455066511517932084) }, 
      { SC_(3.724112033843994140625), SC_(1.104091496679991538723159196605198807097) }, 
      { SC_(4.021769046783447265625), SC_(1.080838392415394466528941224431751600289) }, 
      { SC_(4.18305683135986328125), SC_(1.070728699189787267711417808282208201243) }, 
      { SC_(4.988127231597900390625), SC_(1.037268683773212337925891820825986369163) }, 
      { SC_(5.475403308868408203125), SC_(1.025677237452222708699509051024184979758) }, 
      { SC_(6.73077487945556640625), SC_(1.010147799135311596739412446000395677634) }, 
      { SC_(6.75488376617431640625), SC_(1.009971613405573851873574290566390329028) }, 
      { SC_(7.481843471527099609375), SC_(1.005903033995481747047683253211887943379) }, 
      { SC_(7.635406494140625), SC_(1.005288494073193869275365293603878222362) }, 
      { SC_(8.020862579345703125), SC_(1.004017268583341130595381689022448999632) }, 
      { SC_(8.38578319549560546875), SC_(1.003100201571479771794633384423398597856) }, 
      { SC_(8.42790126800537109375), SC_(1.003009041836055382568010141093226826892) }, 
      { SC_(8.492221832275390625), SC_(1.002875040229932893183945988160370427031) }, 
      { SC_(8.66446590423583984375), SC_(1.002545196845709311376898921088902444564) }, 
      { SC_(8.9931430816650390625), SC_(1.002018125856127423319731400168443258982) }, 
      { SC_(9.1788425445556640625), SC_(1.001770614157242715970257755765969939378) }, 
      { SC_(9.3712940216064453125), SC_(1.001546356501243682890096399666391078865) }, 
      { SC_(9.79772472381591796875), SC_(1.001146130957712750505516168299351687689) }, 
      { SC_(9.808345794677734375), SC_(1.00113762301831987584969089187780050217) }, 
      { SC_(10.11186695098876953125), SC_(1.000919597225029357674089436218492816592) }, 
      { SC_(10.29917240142822265625), SC_(1.000806567139600490049263928993429525886) }, 
      { SC_(10.325397491455078125), SC_(1.000791898339491638031859012162073442552) }, 
      { SC_(10.59409236907958984375), SC_(1.000656217007150362893379421381526735049) }, 
      { SC_(11.10001468658447265625), SC_(1.000460863347090913162269206213828518989) }, 
      { SC_(11.258045196533203125), SC_(1.000412744570371150451037951828092883018) }, 
      { SC_(12.02548313140869140625), SC_(1.000241757815894734629418410369301746079) }, 
      { SC_(12.114536285400390625), SC_(1.000227221507799340331471780559564457085) }, 
      { SC_(12.59912014007568359375), SC_(1.000162173028028771481952241164711193704) }, 
      { SC_(13.27601528167724609375), SC_(1.000101287979535386768777024448093303828) }, 
      { SC_(13.40233516693115234375), SC_(1.000092774524593217714357153624534009066) }, 
      { SC_(13.50353527069091796875), SC_(1.000086474027947163401202419199584993912) }, 
      { SC_(13.81703281402587890625), SC_(1.00006954876715640831942977005349491939) }, 
      { SC_(14.04100894927978515625), SC_(1.000059528194484375589465960959559392027) }, 
      { SC_(14.2049045562744140625), SC_(1.000053123725822614470754551602877776071) }, 
      { SC_(14.57920742034912109375), SC_(1.000040965134201953746630782215943808799) }, 
      { SC_(15.36797332763671875), SC_(1.000023694259291145619969142932513875694) }, 
      { SC_(15.8139476776123046875), SC_(1.000017387917474363833490985179130947483) }, 
      { SC_(16.0026493072509765625), SC_(1.000015254196094267783311053302032549741) }, 
      { SC_(16.0506114959716796875), SC_(1.000014754970384001823203354717544204648) }, 
      { SC_(16.1929874420166015625), SC_(1.000013367248015505858617397050136565041) }, 
      { SC_(17.285480499267578125), SC_(1.000006265375288782355276787853647834027) }, 
      { SC_(17.3384552001953125), SC_(1.000006039370585766187763904743838901712) }, 
      { SC_(17.431396484375), SC_(1.000005662382433471779572282335717605371) }, 
      { SC_(17.864501953125), SC_(1.00000419335137039446528405523273417847) }, 
      { SC_(18.5247364044189453125), SC_(1.000002653000473253577578493409620982871) }, 
      { SC_(18.69007110595703125), SC_(1.000002365653327425220021887287461178979) }, 
      { SC_(18.81287384033203125), SC_(1.000002172565731416793616844762261244142) }, 
      { SC_(19.1818561553955078125), SC_(1.000001682165061320587705723061871112821) }, 
      { SC_(19.67647552490234375), SC_(1.00000119382334998635578076483569134487) }, 
      { SC_(19.70886993408203125), SC_(1.000001167310591227212167384387209403708) }, 
      { SC_(20.61444854736328125), SC_(1.000000623066938898373480079125184673916) }, 
      { SC_(20.89023590087890625), SC_(1.000000514640103638265544723138844382034) }, 
      { SC_(21.0827579498291015625), SC_(1.000000450341377189234015911832375901699) }, 
      { SC_(21.6490421295166015625), SC_(1.000000304127710718113360167907484415053) }, 
      { SC_(21.7479114532470703125), SC_(1.000000283981940559836806790957987649415) }, 
      { SC_(21.8129825592041015625), SC_(1.000000271456777007108293719830577426366) }, 
      { SC_(22.024364471435546875), SC_(1.000000234457016042858052978953659230864) }, 
      { SC_(22.31634521484375), SC_(1.000000191496938987028342073327362804024) }, 
      { SC_(23.4463043212890625), SC_(1.000000087496653103497740447812661569997) }, 
      { SC_(23.5119476318359375), SC_(1.000000083604563844903851348021422245475) }, 
      { SC_(23.8504581451416015625), SC_(1.000000066118672757144002036583533060251) }, 
      { SC_(23.9256191253662109375), SC_(1.000000062762118335210507369548667805974) }, 
      { SC_(24.1413936614990234375), SC_(1.000000054043162442589559272614572137384) }, 
      { SC_(24.1469058990478515625), SC_(1.000000053837061982953069368273926175689) }, 
      { SC_(24.2995853424072265625), SC_(1.000000048430482721838693416022261315822) }, 
      { SC_(24.52557373046875), SC_(1.00000004140831046897333530316265610171) }, 
      { SC_(24.8483028411865234375), SC_(1.000000033108065641575998984551968709104) }, 
      { SC_(25.115139007568359375), SC_(1.000000027517326675188465672935455696634) }, 
      { SC_(25.347324371337890625), SC_(1.000000023426640017082892404381467024384) }, 
      { SC_(25.883914947509765625), SC_(1.000000016150174569147643163428466835474) }, 
      { SC_(25.903171539306640625), SC_(1.000000015936036497475570766824085170722) }, 
      { SC_(25.9667415618896484375), SC_(1.000000015249075980692704336912033740583) }, 
      { SC_(26.88591766357421875), SC_(1.000000008063810840808460735890647313959) }, 
      { SC_(27.289585113525390625), SC_(1.000000006095693351337655085514196913602) }, 
      { SC_(27.9059352874755859375), SC_(1.000000003976323567324742280069738235563) }, 
      { SC_(28.0213603973388671875), SC_(1.000000003670583049284047356311447119736) }, 
      { SC_(28.6940479278564453125), SC_(1.000000002302686016920949834610470007565) }, 
      { SC_(28.924041748046875), SC_(1.000000001963357304099298248229398455341) }, 
      { SC_(29.0107631683349609375), SC_(1.000000001848815070266702493862791862422) }, 
      { SC_(29.6371631622314453125), SC_(1.000000001197643401744885528390587608634) }, 
      { SC_(29.7665653228759765625), SC_(1.000000001094897489879537307636075154625) }, 
      { SC_(29.896099090576171875), SC_(1.000000001000874865523017090100762703195) }, 
      { SC_(29.9447536468505859375), SC_(1.000000000967683322176361378042505764603) }, 
      { SC_(30.40348052978515625), SC_(1.000000000704112916637256444040895840462) }, 
      { SC_(30.716098785400390625), SC_(1.000000000566936750566018696285006521506) }, 
      { SC_(30.851467132568359375), SC_(1.000000000516160286455123973861824307492) }, 
      { SC_(32.114917755126953125), SC_(1.000000000215004429998345753311603463246) }, 
      { SC_(32.31705474853515625), SC_(1.000000000186895151300205581521237835124) }, 
      { SC_(33.2660064697265625), SC_(1.000000000096813254374934769090357620442) }, 
      { SC_(33.285717010498046875), SC_(1.000000000095499555541792141940005023127) }, 
      { SC_(33.286014556884765625), SC_(1.000000000095479861400139003020181708444) }, 
      { SC_(33.43369293212890625), SC_(1.000000000086189849924727332774207599423) }, 
      { SC_(34.13188934326171875), SC_(1.000000000053122428800090015460135314565) }, 
      { SC_(34.501476287841796875), SC_(1.000000000041116970445658244297262938037) }, 
      { SC_(34.5605926513671875), SC_(1.000000000039466198914643412779159907251) }, 
      { SC_(34.85152435302734375), SC_(1.000000000032258642822020209836223179965) }, 
      { SC_(35.2764434814453125), SC_(1.000000000024028830747846719836544655561) }, 
      { SC_(35.530582427978515625), SC_(1.000000000020147871220182569297544208725) }, 
      { SC_(35.530796051025390625), SC_(1.000000000020144888100208513063984898063) }, 
      { SC_(35.9766082763671875), SC_(1.000000000014789788630980767807649535379) }, 
      { SC_(36.075710296630859375), SC_(1.000000000013807952318212484703393304569) }, 
      { SC_(37.346637725830078125), SC_(1.000000000005721921857809586500408112553) }, 
      { SC_(38.30919647216796875), SC_(1.000000000002936181040773097124904210497) }, 
      { SC_(38.746036529541015625), SC_(1.00000000000216910640536046429265717688) }, 
      { SC_(38.9936981201171875), SC_(1.000000000001826952613666734849972430403) }, 
      { SC_(39.13246917724609375), SC_(1.000000000001659407425313111065810951635) }, 
      { SC_(39.650783538818359375), SC_(1.000000000001158576855480162680056752427) }, 
      { SC_(39.67319488525390625), SC_(1.000000000001140718173333054850436397748) }, 
      { SC_(39.688701629638671875), SC_(1.000000000001128522871078350064987157044) }, 
      { SC_(40.1527252197265625), SC_(1.00000000000081813568920259864182340915) }, 
      { SC_(41.04537200927734375), SC_(1.000000000000440668358431418275080044096) }, 
      { SC_(41.102458953857421875), SC_(1.000000000000423571747277636883518004963) }, 
      { SC_(41.10936737060546875), SC_(1.00000000000042154830144392988490289401) }, 
      { SC_(41.2002105712890625), SC_(1.000000000000395822807194682529407123307) }, 
      { SC_(41.9948883056640625), SC_(1.000000000000228180734060750744420949622) }, 
      { SC_(42.01873779296875), SC_(1.000000000000224439639108525255752196646) }, 
      { SC_(42.245525360107421875), SC_(1.000000000000191791651936161940112696305) }, 
      { SC_(42.640682220458984375), SC_(1.000000000000145839655420702994396584213) }, 
      { SC_(42.656719207763671875), SC_(1.000000000000144227479936645019793391633) }, 
      { SC_(42.8525238037109375), SC_(1.000000000000125922969766185468474101667) }, 
      { SC_(42.93152618408203125), SC_(1.000000000000119212795161526838438039263) }, 
      { SC_(43.824497222900390625), SC_(1.000000000000064196566283314196661109382) }, 
      { SC_(43.89032745361328125), SC_(1.000000000000061333101268165345810372718) }, 
      { SC_(44.2351226806640625), SC_(1.00000000000004829489412268436483221931) }, 
      { SC_(44.69818878173828125), SC_(1.000000000000035035186258816984623517723) }, 
      { SC_(44.844814300537109375), SC_(1.000000000000031649419666232107485326247) }, 
      { SC_(45.324756622314453125), SC_(1.000000000000022692832892549255237158092) }, 
      { SC_(45.4700164794921875), SC_(1.000000000000020519233831913348485253367) }, 
      { SC_(45.52651214599609375), SC_(1.000000000000019731234145578672796054892) }, 
      { SC_(45.67481231689453125), SC_(1.000000000000017803748480318501874295268) }, 
      { SC_(45.706668853759765625), SC_(1.000000000000017414927749921329025278045) }, 
      { SC_(45.942142486572265625), SC_(1.000000000000014792345774484033646200826) }, 
      { SC_(46.061252593994140625), SC_(1.000000000000013620132568841259892936442) }, 
      { SC_(46.165493011474609375), SC_(1.000000000000012670735995557404974141305) }, 
      { SC_(46.66110992431640625), SC_(1.000000000000008986824993086497939810961) }, 
      { SC_(46.95496368408203125), SC_(1.000000000000007330734455050719634274445) }, 
      { SC_(46.970867156982421875), SC_(1.000000000000007250368259197024518158727) }, 
      { SC_(47.740230560302734375), SC_(1.000000000000004253619155993815373574244) }, 
      { SC_(47.82225799560546875), SC_(1.00000000000000401851769095578631160734) }, 
      { SC_(47.844524383544921875), SC_(1.000000000000003956972517068642986534164) }, 
      { SC_(47.916797637939453125), SC_(1.000000000000003763627354737768001799664) }, 
      { SC_(48.03951263427734375), SC_(1.000000000000003456732091224533384587416) }, 
      { SC_(48.077789306640625), SC_(1.000000000000003366226193065923102690805) }, 
      { SC_(48.088245391845703125), SC_(1.000000000000003341917308946400199448992) }, 
      { SC_(48.21654510498046875), SC_(1.000000000000003057550491069862425535113) }, 
      { SC_(48.644329071044921875), SC_(1.000000000000002272991605673625823218911) }, 
      { SC_(48.682353973388671875), SC_(1.000000000000002213865312361618938196866) }, 
      { SC_(48.7743377685546875), SC_(1.000000000000002077118692813712217229131) }, 
      { SC_(49.042804718017578125), SC_(1.000000000000001724426584048478072980917) }, 
      { SC_(49.068695068359375), SC_(1.00000000000000169375635354541860333178) }, 
      { SC_(49.429607391357421875), SC_(1.000000000000001318880667089529421391478) }, 
      { SC_(49.453510284423828125), SC_(1.000000000000001297209182880660183342645) }, 
      { SC_(49.4922943115234375), SC_(1.000000000000001262800830493712288542346) }, 
      { SC_(49.584011077880859375), SC_(1.000000000000001185019129246615676129004) }, 
      { SC_(50.018886566162109375), SC_(1.000000000000000876626902724624554021734) }, 
      { SC_(50.265506744384765625), SC_(1.000000000000000738881381594389232226354) }, 
      { SC_(50.60231781005859375), SC_(1.000000000000000585038557479300395348451) }, 
      { SC_(51.059597015380859375), SC_(1.000000000000000426117855101476521328968) }, 
      { SC_(51.098628997802734375), SC_(1.000000000000000414743830855801205190555) }, 
      { SC_(52.473300933837890625), SC_(1.000000000000000159941972488386163451755) }, 
      { SC_(52.728687286376953125), SC_(1.000000000000000133993427096920945462604) }, 
      { SC_(52.8274078369140625), SC_(1.00000000000000012513121114750147039425) }, 
      { SC_(53.563289642333984375), SC_(1.000000000000000075135148894081185552722) }, 
      { SC_(54.441722869873046875), SC_(1.000000000000000040870354119536041226567) }, 
      { SC_(54.534519195556640625), SC_(1.000000000000000038324272820380003916252) }, 
      { SC_(54.8891754150390625), SC_(1.00000000000000002997172663898867687923) }, 
      { SC_(55.0283966064453125), SC_(1.000000000000000027214603309398090046137) }, 
      { SC_(55.1144256591796875), SC_(1.000000000000000025639212561447923551389) }, 
      { SC_(55.33161163330078125), SC_(1.000000000000000022055920618207215687506) }, 
      { SC_(55.826557159423828125), SC_(1.000000000000000015650626977085832472044) }, 
      { SC_(56.10559844970703125), SC_(1.000000000000000012898284202740849648306) }, 
      { SC_(56.106632232666015625), SC_(1.000000000000000012889045070538182553024) }, 
      { SC_(56.464366912841796875), SC_(1.000000000000000010058468799404521129717) }, 
      { SC_(57.06310272216796875), SC_(1.000000000000000006641932153342522535343) }, 
      { SC_(57.346035003662109375), SC_(1.000000000000000005459128681570429564283) }, 
      { SC_(57.472850799560546875), SC_(1.000000000000000004999746361816983875868) }, 
      { SC_(57.4929046630859375), SC_(1.000000000000000004930729282248733593481) }, 
      { SC_(57.598194122314453125), SC_(1.000000000000000004583696701999359539209) }, 
      { SC_(57.61005401611328125), SC_(1.000000000000000004546170184327776041529) }, 
      { SC_(57.6248931884765625), SC_(1.00000000000000000449964916454958377241) }, 
      { SC_(57.9284210205078125), SC_(1.000000000000000003645924503223314003083) }, 
      { SC_(57.933013916015625), SC_(1.000000000000000003634335967038469182822) }, 
      { SC_(58.09400177001953125), SC_(1.000000000000000003250595270157055505909) }, 
      { SC_(58.16320037841796875), SC_(1.000000000000000003098361177564293540649) }, 
      { SC_(58.26497650146484375), SC_(1.000000000000000002887316391786182139852) }, 
      { SC_(58.885471343994140625), SC_(1.00000000000000000187804855653649070089) }, 
      { SC_(59.2601165771484375), SC_(1.000000000000000001448529565053139975957) }, 
      { SC_(59.322772979736328125), SC_(1.000000000000000001386966294498092563052) }, 
      { SC_(59.579998016357421875), SC_(1.000000000000000001160468764851974345628) }, 
      { SC_(59.650043487548828125), SC_(1.000000000000000001105471797878708756365) }, 
      { SC_(59.791217803955078125), SC_(1.000000000000000001002420555691430478745) }
   }};
#undef SC_

