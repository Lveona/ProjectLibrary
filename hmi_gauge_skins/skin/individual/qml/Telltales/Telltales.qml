import QtQuick 2.8
import qmlEnums 1.0
import "../Common"

Item {
    id: telltaleContent
//    property bool languge: LangugeManage.langugeChengeSW==="CN"       //CN=true,EN=false
//    property string over_speed     : TelltalesScreen.over_speed
//    property bool overspeedvisible     : TelltalesScreen.overspeedvisible

//    Component.onCompleted:
//    {
//        //        console.log("tell ", COLORTYPEEnums.COLORTYPEQML_GREEN, COLORTYPEEnums.COLORTYPEQML_YELLOW)
//    }

//    Loader{
//        id: loaderACCTargetSpeed
//        active:overspeedvisible
//        sourceComponent: comACCTargetSpeed
//        onLoaded: {
//            active = true
//        }
//    }

//    Component{
//        id: comACCTargetSpeed
//        Item{
//            width: 1920
//            height: 720
//            visible:false
//            Image{
//                id:unitImg
//                x:1434;y:506;
//                source: "Telltale_ACC_mubiaochesu.png"
//                CustomText{//左前
//                    y: -4;
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    font.pixelSize: 30
//                    text: over_speed
////                    font.family:"Source Han Sans CN Bold"
//                    color: "white"
//                    font.bold: true
//                }
//            }
//        }
//    }

//    Image{
//        x: 1228; y: 16;
//        source: "right_turn.png"
//        visible:TelltalesScreen.rightvisible
//    }

//    Image{
//        x: 634; y: 16;
//        source: "left_turn.png"
//        visible:TelltalesScreen.leftvisible
//    }

//    Image{
//        x: 1308; y: 569;
//        source: TelltalesScreen.waterTemp?"water2.png":""
//        //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
//    }
//    Image{
//        x: 554; y: 569;
//        source: TelltalesScreen.fuellackvisible?"fuel2.png":""
//        //visible: Manager.receiveCtrlPowerMode === ManagerEnums.QML_POWERMODE_D1
//    }

//    Image{ x: 428; y: 506;source: "ibooster_fault.png";visible: TelltalesScreen.brakefaultvisible }
//    Image{ x: 365; y: 107;source: "tire_pressure.png";visible: TelltalesScreen.tempvisible;}
//    Image{ x: 302; y: 107;source: "Telltale_yurezhishi.png";visible: TelltalesScreen.glowVisible;}
//    Image{ x: 491; y: 107;source: "Telltale_yuanguangdeng.png";visible: TelltalesScreen.farvisible;}
//    Image{ x: 554; y: 107;source: "Telltale_shikuodeng.png";visible: TelltalesScreen.positionvisible;}
//    Image{ x: 1497; y: 107; source: "Telltale_anquandai_1.png";visible: TelltalesScreen.seatbeltFL;}
//    Image{ x: 1560; y: 107;source: "Telltale_anquandai_2.png";visible: TelltalesScreen.seatbeltFR;}
//    Image{ x: 1623; y: 107;source: "Telltale_xudianchifangdian.png";visible: TelltalesScreen.chargeConVisible;}
//    Image{ x: 1606; y: 643;source: "Telltale_jiyouyalidi.png";visible: TelltalesScreen.oillackvisibl;}
//    Image{ x: 1669; y: 643;source: "Telltale_fadongjifangdao.png";visible: TelltalesScreen.engineAntiTheftVisible;}
//    Image{ x: 302; y: 170;source: "Telltale_fadongjiguzhang.png";visible: TelltalesScreen.engineFaultVisible;}
//    Image{ x: 365; y: 170;source: "Telltale_fadongjipaifangguzhang.png";visible: TelltalesScreen.milVisible;}
//    //Image{ x: 491; y: 170;source: "Telltale_zhinengyuanguangdeng_gray.png";visible: TelltalesScreen.highBeamVisible;}//fip无
//    Image{x: 554; y: 170;source: "Telltale_houwudeng.png";visible: TelltalesScreen.rearfogvisible;}
//    //Image{ x: 1371; y: 170;source: "Telltale_anquanqinangguzhang.png";visible: TelltalesScreen.seatBeltFaultVisible;}//fip无
//    Image{ x: 1497; y: 170;source: "Telltale_anquandai_3.png";visible: TelltalesScreen.seatbeltRL;}
//    Image{ x: 1560; y: 170;source: "Telltale_anquandai_4.png";visible: TelltalesScreen.seatbeltRM; }
//    Image{ x: 1623; y: 170;source: "Telltale_anquandai_5.png";visible: TelltalesScreen.seatbeltRR;}
//    Image{ x: 1686; y: 170;source: "Telltale_EPS_shixiao.png";visible: TelltalesScreen.espFaultVisible;}
//    Image{ x: 428; y: 380;source: "Telltale_EBD.png";visible: TelltalesScreen.ebdvisible;}
//    //Image{ x: 1434; y: 380;source: "Telltale_dingshuxunhang_green.png";visible: TelltalesScreen.adaptiveCruiseVisible;}//fip无
//    Image{ x: 428; y: 443;source: "Telltale_ABS.png";visible: TelltalesScreen.absvisible;}
//    //Image{ x: 1434; y: 443;source: "Telltale_chedaopianli_green.png";visible: TelltalesScreen.laneDepartureVisible;}//fip无
//    Image{ x: 491; y: 506;
//        source:
//            {
//            if(TelltalesScreen.autoholdType===COLORTYPEEnums.COLORTYPEQML_YELLOW)
//            {
//                "Telltale_AutoHold_yellow.png"
//            }
//            else if(TelltalesScreen.autoholdType===COLORTYPEEnums.COLORTYPEQML_GREEN)
//            {
//                "Telltale_AutoHold_green.png"
//            }
//            else{
//                ""
//            }
//        }
//        visible: TelltalesScreen.autoholdvisible
//    }
//    Image{
//        x: 1371; y: 506;
//        source: {
//            if(TelltalesScreen.cruiseType===COLORTYPEEnums.COLORTYPEQML_WHITE){
//                "Telltale_zhishiyingxunhang_white.png"
//            }
//            else if(TelltalesScreen.cruiseType===COLORTYPEEnums.COLORTYPEQML_GREEN){
//                "Telltale_zhishiyingxunhang_green.png"
//            }
//            else{
//                ""
//            }
//        }
//        visible: false
//    }
//    Image{
//        x: 1434; y: 380;
//        source: {
//            if(TelltalesScreen.cruiseType===COLORTYPEEnums.COLORTYPEQML_WHITE){
//                "Telltale_dingsuxunhang_white.png"
//            }
//            else if(TelltalesScreen.cruiseType===COLORTYPEEnums.COLORTYPEQML_GREEN){
//                "Telltale_dingsuxunhang_green.png"
//            }
//            else{
//                ""
//            }
//        }
//        visible: TelltalesScreen.cruiseVisible
//    }

//    Image{ x: 428; y: 569;source: "park_brake.png";visible: TelltalesScreen.epbvisible;}
//    Image{ x: 491; y: 569;source: "Telltale_EPB_guzhang.png";visible: TelltalesScreen.epbfaultvisible}
//    Image{ x: 256; y: 643;source: "Telltale_DPF.png";visible: TelltalesScreen.dpfvisible; }
//    Image{ x: 319; y: 643;source: "Telltale_SCR.png";visible: TelltalesScreen.scrvisible;}
//    Image{ x: 635; y: 643;source: "Telltale_ranyoujishui.png";visible: TelltalesScreen.waterInFuelVisible;}
//    Image{ x: 698; y: 643;source: "Telltale_HDC_yellow.png";visible: TelltalesScreen.hdcvisible&&TelltalesScreen.hdcType===COLORTYPEEnums.COLORTYPEQML_YELLOW;}
//    Image{ x: 698; y: 643;source: "Telltale_HDC_green.png";visible: TelltalesScreen.hdcvisible&&TelltalesScreen.hdcType===COLORTYPEEnums.COLORTYPEQML_GREEN;}
//    Image{ x: 1159; y: 643;source: "Telltale_ESP.png";visible: TelltalesScreen.escvisible;}
//    Image{ x: 1222; y: 643;source: "Telltale_ESP_guanbi.png";visible: TelltalesScreen.escoffvisible;}
//    Image{ x: 1371; y: 107;source: "Telltale_siquguzhang.png";visible: TelltalesScreen.drvfaultvisible ;}
//    Image{ x: 1371; y: 170;source: "Telltale_anquanqinangguzhang.png";visible: TelltalesScreen.airbagvisible;}
//    //适时四驱模式指示灯
//     Image{
//         x: 1371; y: 107;
//         source: {
//             if(TelltalesScreen.driveType===COLORTYPEEnums.COLORTYPEQML_RED){
//                 "Telltale_2H.png"
//             }
//             else if(TelltalesScreen.driveType===COLORTYPEEnums.COLORTYPEQML_WHITE){
//                 "Telltale_4H.png"
//             }
//             else if(TelltalesScreen.driveType===COLORTYPEEnums.COLORTYPEQML_YELLOW){
//                 "Telltale_4L.png"
//             }
//             else if(TelltalesScreen.driveType===COLORTYPEEnums.COLORTYPEQML_GREEN){
//                 "Telltale_AUTO.png"
//             }
//             else{
//                 ""
//             }
//         }
//         visible: TelltalesScreen.drivevisible
//     }

//     //分时四驱模式指示灯
//      Image{
//          x: 1371; y: 107;
//          source: {
//              if(TelltalesScreen.driveModeFenshiType===COLORTYPEEnums.COLORTYPEQML_RED){
//                  "Telltale_fenshisiqu_2H.png"
//              }
//              else if(TelltalesScreen.driveModeFenshiType===COLORTYPEEnums.COLORTYPEQML_WHITE){
//                  "Telltale_fenshisiqu_4H.png"
//              }
//              else if(TelltalesScreen.driveModeFenshiType===COLORTYPEEnums.COLORTYPEQML_YELLOW){
//                  "Telltale_fenshisiqu_4L.png"
//              }
//              else{
//                  ""
//              }
//          }
//          visible: TelltalesScreen.driveModeFenshiVisible
//      }
//      //分时故障指示灯
//      Image{ x: 1371; y: 107;source: "Telltale_fenshisiqu_guzhang.png";visible: TelltalesScreen.driveModeFenshiFaultVisible;}


//    Image{ x: 382; y: 643;source: "Telltale_biansuxiangguzhang.png";visible: TelltalesScreen.gearboxFault;}//以下visible待对应
//    Image{ x: 1434; y: 569;source: "Telltale_jiaotongxiansu.png";visible: false;}
//    Image{ x: 1371; y: 569;source: "Telltale_qianpengzhuang_red .png";visible: false;}
//    Image{ x: 1371; y: 569;source: "Telltale_qianpengzhuang_yellow.png";visible: false;}
}












