<distribution version="19.0.0" name="Temp Control" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{70A8B970-CB1F-4999-8A79-88DF9F724D09}">
		<general appName="Temp Control" outputLocation="c:\Users\Yuval.sh\Desktop\CVI\cvidistkit.Temp Control" relOutputLocation="cvidistkit.Temp Control" outputLocationWithVars="c:\Users\Yuval.sh\Desktop\CVI\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.1">
			<arp company="Afeka College of Engineering" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="Temp Control" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="Temp Control" dirID="100" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Temp Control" dirID="101" parentID="7" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="C:\Users\Yuval.sh\Desktop\CVI\arduino\arduino.ino" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="C:\Users\Yuval.sh\Desktop\CVI\42650thermometer_99061.ico" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="c:\Users\Yuval.sh\Desktop\CVI\cvibuild.project\Release\project.exe" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="C:\Users\Yuval.sh\Desktop\CVI\DLL.dll" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="100" projectID="0">
				<fileID>2</fileID></projectOutput>
			<projectDependencies dirID="100" projectID="0">
				<fileID>3</fileID></projectDependencies></fileGroups>
		<shortcuts>
			<shortcut name="Temp Control" targetFileID="2" destDirID="101" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="false" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="true">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>activeXsup</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<exeName>install.exe</exeName>
			<launchConditions>
				<condition>MINOS_WIN7_SP1</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI LabWindows/CVI Shared Runtime 2019" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{2EB63900-C920-494E-9F7B-56E6B2DCBEE9}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="19.0.49152">
				<dependencies>
					<productID>{0946CDFA-C3C6-4AD5-B884-FB72701ED351}</productID>
					<productID>{14B23AC5-B7EF-47D1-A57D-8666BAEE13C3}</productID>
					<productID>{16BC0547-DF57-48CF-8CB5-1CC0DF3B4911}</productID>
					<productID>{52981014-740C-430E-A83A-711186DF565B}</productID>
					<productID>{5B4D362F-8203-490C-82D1-5F607972196F}</productID>
					<productID>{60684600-163F-45D7-83DB-E247FA48D81F}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{69181DFA-D7CA-4AFE-98E2-A985F32B557B}</productID>
					<productID>{6E1BCD5B-41A1-4E69-8C6E-389F57A19F00}</productID>
					<productID>{75191165-D39E-42A2-A7A2-D74AE99F8A84}</productID>
					<productID>{7EE28BBA-8A24-40B1-B0D0-9066A8CFA4AA}</productID>
					<productID>{81710CDC-7B4D-4A91-8D44-8E2F8B5C2B6E}</productID>
					<productID>{820FB6E8-8856-48D7-934C-76169DCCFD48}</productID>
					<productID>{88104A0D-1729-4A73-B798-80BEFC243F18}</productID>
					<productID>{88DFF01E-7C87-4E35-B194-CB7A2E32FA6D}</productID>
					<productID>{93977567-FFEC-453C-A47F-CE30077E9F4B}</productID>
					<productID>{9B14BAA8-31A5-463B-88C8-EC81F67BEE57}</productID>
					<productID>{AFC999BB-F270-46EF-B748-AE755EC75322}</productID>
					<productID>{B0049D5A-380E-4219-A69D-02273F86891C}</productID>
					<productID>{B29007A1-E053-46E4-8A51-6803638AF06D}</productID>
					<productID>{C0A9F5E2-DCD5-44C1-8B03-C560F4C06D6C}</productID>
					<productID>{CE61F080-FB64-4F6C-9763-A3060A0E59E6}</productID>
					<productID>{D1027BA0-C959-44E2-B4FA-10386404AF75}</productID>
					<productID>{D72C00A8-14F3-4E45-AFAC-5A71F833E210}</productID>
					<productID>{E12F09FF-07B3-4677-8D5C-BDD01E9A5545}</productID>
					<productID>{ED664E5A-6D28-48EA-A2EE-B6356EF01B37}</productID>
					<productID>{EEA5281C-7DA9-492E-8F6F-4127DC67AAD6}</productID>
					<productID>{EFC648C5-F3BC-4096-9AFE-23121EF06828}</productID>
					<productID>{F2EEE63A-0DCA-41BF-A243-4E4C0DFA38A4}</productID>
					<productID>{F456DB40-F5DF-45FE-A582-83DBED5D6432}</productID>
					<productID>{F8018104-6294-4896-A9E2-CBC919992310}</productID>
					<productID>{FA85DBC5-063E-4CA0-9E3A-7C1180D8F7AE}</productID>
					<productID>{FAFB3CD7-F8A6-4D31-BCB4-57354C17128E}</productID>
					<productID>{FB67912C-BB8D-4FE2-B64E-7712EB90DEA4}</productID></dependencies></product></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="c:\Users\Yuval.sh\Desktop\CVI\project.prj" ProjectRelativePath="project.prj"/></Projects>
		<buildData progressBarRate="0.750582695172601">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.060256000000000</ProductsAdded>
				<DPConfigured>0.735256500000000</DPConfigured>
				<DPMergeModulesAdded>3.080257500000000</DPMergeModulesAdded>
				<DPClosed>10.830254999999999</DPClosed>
				<DistributionsCopied>16.655522500000004</DistributionsCopied>
				<End>133.229823500000009</End></progressTimes></buildData>
	</msi>
</distribution>
