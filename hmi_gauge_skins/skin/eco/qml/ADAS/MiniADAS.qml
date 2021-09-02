import QtQuick 2.8
import "../Common/"
import qmlEnums 1.0
import QtQuick.Shapes 1.0
import QtGraphicalEffects 1.0
import "./custools"
import "./adas3d"

Item {
    id:winadas
    width: 1920
    height: 720
    visible: isAdasWarn

    property var isAdasWarn: ADASScreen.miniAdasVisible //是否有报警

    property var naviMapMod: InterconnectScreen.navigationMapMod
    property var miniDoorFl: ADASScreen.ADAS_DOW_FL
    property var miniDoorFr: ADASScreen.ADAS_DOW_FR
    property var miniDoorRl: ADASScreen.ADAS_DOW_RL
    property var miniDoorRR: ADASScreen.ADAS_DOW_RR
    property var miniRcw:   ADASScreen.RCW_WARN
    property var miniFcw:   ADASScreen.FCW_WARN
    property var miniBSDLeft:   ADASScreen.LCA_LEFT_WARN
    property var miniBSDRight:  ADASScreen.LCA_RIGHT_WARN
    property var miniFctaLeft: ADASScreen.fctaLeft
    property var miniFctaRight: ADASScreen.fctaRight
    property var miniRctaLeft: ADASScreen.RCTA_LEFT_WARN
    property var miniRctaRight: ADASScreen.RCTA_RIGHT_WARN
    property var miniLDWLeft: ADASScreen.laneLine1_Color
    property var miniLDWRight: ADASScreen.laneLine2_Color
    property var leftILC: ADASScreen.leftILC
    property var rightILC: ADASScreen.rightILC
    property var leftILCVisible: ADASScreen.leftILCVisible
    property var rightILCVisible: ADASScreen.rightILCVisible
    property var laneLine1_Type: ADASScreen.laneLine1_Type
    property var laneLine2_Type: ADASScreen.laneLine2_Type

    Item{
        id: miniAdas
        x:1371
        y:240
        width: 510
        height: 289
        Image{
            id:miniAdasBg
            source:"pic_HMI_D_classic_default_road_outline.png"
        }
        Image{
            id:miniAdasRoadLineLeft
            x:181
            width: 64
            height: 236
            source:{
                if(laneLine1_Type === 1)//实线
                {
                    if(miniLDWLeft === "#fcc338"){
                        "pic_HMI_D_classic_default_road_inline_right_normal2.png"
                    }else if(miniLDWLeft === "#e76e66"){
                        "pic_HMI_D_classic_default_road_inline_left_normal.png"
                    }else{
                        "pic_HMI_D_classic_default_road_inline_left_blue.png"
                    }
                }else if(laneLine1_Type === 2){//虚线
                    if(miniLDWLeft === "#fcc338"){
                        "pic_HMI_D_classic_dashed_road_inline_right_normal2.png"
                    }else if(miniLDWLeft === "#e76e66"){
                        "pic_HMI_D_classic_dashed_road_inline_left_normal.png"
                    }else{
                        "pic_HMI_D_classic_dashed_road_inline_left_blue.png"
                    }
                }else{
                    "pic_HMI_D_classic_default_road_inline_left_blue.png"
                }


            }


        }
        Image{
            id:miniAdasRoadLineRight
            x:267
            width: 64
            height: 236
            source:{
                if(laneLine2_Type === 1){
                    if(miniLDWRight === "#fcc338"){
                        "pic_HMI_D_classic_default_road_inline_right_normal.png"
                    }else if(miniLDWRight === "#e76e66"){
                        "pic_HMI_D_classic_default_road_inline_left_normal2.png"
                    }else{
                        "pic_HMI_D_classic_default_road_inline_right_blue.png"
                    }
                }
                else if(laneLine2_Type === 2)
                {
                    if(miniLDWRight === "#fcc338"){
                        "pic_HMI_D_classic_dashed_road_inline_right_normal.png"
                    }else if(miniLDWRight === "#e76e66"){
                        "pic_HMI_D_classic_dashed_road_inline_left_normal2.png"
                    }else{
                        "pic_HMI_D_classic_dashed_road_inline_right_blue.png"
                    }
                }else{
                    "pic_HMI_D_classic_default_road_inline_right_blue.png"
                }

            }

        }
        Image{
            id:miniAdasForntCarleft
            x:137
            y:26
            width: 99
            height: 134
            visible: leftILCVisible === false
            source:"pic_HMI_D_classic_default_road_car2.png"
        }
        Image{
            id:miniAdasForntCarRight
            x:275
            y:9
            width: 73
            height: 98
            source:"pic_HMI_D_classic_default_road_car3.png"
        }
        Image{
            id:miniAdasCarDoorFL
            x:196
            y:127
            source:{
               if(miniDoorFl === 1){
                  "pic_HMI_D_classic_default_road_dooropen_yellow2.png"
               }else if(miniDoorFl === 2){
                   "pic_HMI_D_classic_default_road_dooropen_red.png"
               }else{
                   ""
               }
            }

        }
        Image{
            id:miniAdasCarDoorRL
            x:193
            y:148
            source:{
               if(miniDoorRl === 1){
                  "pic_HMI_D_classic_default_road_dooropen_yellow2.png"
               }else if(miniDoorRl === 2){
                   "pic_HMI_D_classic_default_road_dooropen_red.png"
               }else{
                   ""
               }
            }
        }
        Image{
            id:miniAdasCarDoorFR
            x:287
            y:131
            source:{
                if(miniDoorFr === 1){
                    "pic_HMI_D_classic_default_road_dooropen_yellow.png"
                }else if(miniDoorFr === 2){
                    "pic_HMI_D_classic_default_road_dooropen_red2.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasCarDoorRR
            x:290
            y:148
            source:{
                if(miniDoorRR === 1){
                   "pic_HMI_D_classic_default_road_dooropen_yellow.png"
                }else if(miniDoorRR === 2){
                    "pic_HMI_D_classic_default_road_dooropen_red2.png"
                }else{
                    ""
                }
            }

        }
        Image{
            id:miniAdasArrowLeft
            x:185
            y:68
            width: 54
            height: 52
            visible: leftILCVisible
            source: {
                if(leftILC === 1){
                    "pic_HMI_D_classic_default_road_turnarrow_blue.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasArrowRight
            x:293
            y:68
            width: 54
            height: 52
            visible: rightILCVisible
            source: {
                if(rightILC === 1){
                    "pic_HMI_D_classic_default_road_turnarrow_blue2.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasFCW
            x:171
            y:60
            width: 162
            height: 85
            source:{
                if(miniFcw === 1){
                    "pic_HMI_D_classic_default_road_RCW_FCW2.png"
                }else if(miniFcw === 2){
                     "pic_HMI_D_classic_default_road_RCW_FCW.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasMainCar
            x:195
            y:107
            width: 120
            height: 120
            source:"pic_HMI_D_classic_default_road_car.png"
        }
        Image{
            id:miniAdasRCW
            x:171
            y:148
            width: 162
            height: 85
            source:{
                if(miniRcw === 1){
                    "pic_HMI_D_classic_default_road_RCW_FCW2.png"
                }else if(miniRcw === 2){
                     "pic_HMI_D_classic_default_road_RCW_FCW.png"
                }else{
                    ""
                }
            }

        }
        Image{
            id:miniAdasBSDLeft
            x:88
            y:164
            width: 169
            height: 116
            source: {
                if(miniBSDLeft === 1){
                    "pic_HMI_D_classic_default_road_BSD_yellow.png"
                }else if(miniBSDLeft === 2){
                    "pic_HMI_D_classic_default_road_BSD_red.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasBSDRight
            x:257
            y:164
            width: 169
            height: 116
            source: {
                if(miniBSDRight === 1){
                    "pic_HMI_D_classic_default_road_BSD_yellow2.png"
                }else if(miniBSDRight === 2){
                    "pic_HMI_D_classic_default_road_BSD_red2.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasFCTALeft
            x:1491 - parent.x
            y:363 - parent.y
            source: {
                if(miniFctaLeft === 1){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA_yellow.png"
                }else if(miniFctaLeft === 2){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasFCTARight
            x:1644 - parent.x
            y:363 - parent.y
            source: {
                if(miniFctaRight === 1){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA_yellow2.png"
                }else if(miniFctaRight === 2){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA2.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasRCTALeft
            x:97
            y:159
            source: {
                if(miniRctaLeft === 1){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA_yellow.png"
                }else if(miniRctaLeft === 2){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA.png"
                }else{
                    ""
                }
            }
        }
        Image{
            id:miniAdasRCTARight
            x:298
            y:159
            source: {
                if(miniRctaRight === 1){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA_yellow2.png"
                }else if(miniRctaRight === 2){
                    "pic_HMI_D_classic_default_road_RCTA_FCTA2.png"
                }else{
                    ""
                }
            }
        }

    }


}
