<distribution version="10.0.1" name="MCTBox_API" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{6B6A04AE-E86F-40F3-BE89-152A22334029}">
		<general appName="MCTBox_API" outputLocation="d:\Projects\DCU_MCTBox\MCTBox_API\cvidistkit.MCTBox_API" relOutputLocation="cvidistkit.MCTBox_API" outputLocationWithVars="d:\Projects\DCU_MCTBox\MCTBox_API\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="false" version="1.0.1">
			<arp company="%company" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" showPaths="true" readMe="" license="">
			<dlgstrings welcomeTitle="MCTBox_API" welcomeText=""/></userinterface>
		<dirs appDirID="100">
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="MCTBox_API" dirID="100" parentID="2" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API_AIO.h" relSourcePath="MCTBox_API_AIO.h" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\cvibuild.MCTBox_API\Release\MCTBox_API.lib" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\cvibuild.MCTBox_API\Release\MCTBox_API.dll" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API.h" relSourcePath="MCTBox_API.h" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="4" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API_SwitchControl.h" relSourcePath="MCTBox_API_SwitchControl.h" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="5" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API_import_export.h" relSourcePath="MCTBox_API_import_export.h" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="6" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API_FIN.h" relSourcePath="MCTBox_API_FIN.h" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="7" sourcePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API_DIO.h" relSourcePath="MCTBox_API_DIO.h" relSourceBase="0" targetDir="100" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="1" dirID="100" projectID="0">
				<fileID>2</fileID>
				<fileID>1</fileID></projectOutput></fileGroups>
		<mergemodules/>
		<products/>
		<runtimeEngine cvirte="true" instrsup="true" lvrt="true" analysis="true" netvarsup="true" dotnetsup="true" activeXsup="true" lowlevelsup="true" rtutilsup="true" installToAppDir="false"/>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WINXP</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>c:\program files\national instruments\cvi2010\bin\msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="d:\Projects\DCU_MCTBox\MCTBox_API\MCTBox_API.prj" ProjectRelativePath="MCTBox_API.prj"/></Projects>
		<buildData progressBarRate="0.840743605434452">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.073011500000000</ProductsAdded>
				<DPConfigured>1.673455500000000</DPConfigured>
				<DPMergeModulesAdded>4.052893000000000</DPMergeModulesAdded>
				<DPClosed>13.002896000000000</DPClosed>
				<DistributionsCopied>15.653053500000000</DistributionsCopied>
				<End>118.942325999999980</End></progressTimes></buildData>
	</msi>
</distribution>
