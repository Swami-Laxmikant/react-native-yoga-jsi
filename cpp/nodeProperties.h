#ifndef NODE_PROPERTIES_H
#define NODE_PROPERTIES_H

#include <jsi/jsi.h>
#include <yoga/Yoga.h>
#include "macros.h"

#define INSTALL_HOST_FUN(funcName, argCount, body)                                                                                                           \
    auto funcName = Function::createFromHostFunction(rt,                                                                                                     \
                                                     PropNameID::forAscii(rt, #funcName),                                                                    \
                                                     argCount,                                                                                               \
                                                     [node](Runtime & runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value body); \
    nodeObject.setProperty(rt, #funcName, std::move(funcName));

using namespace facebook::jsi;

namespace nodeProperties
{

    void set(Object &nodeObject, Runtime &rt, YGNodeRef node)
    {
        INSTALL_HOST_FUN(setWidth, 1, {
            SET_AUTO_PERCENT_NUMBER(YGNodeStyleSetWidthAuto, YGNodeStyleSetWidthPercent, YGNodeStyleSetWidth);
        });

        INSTALL_HOST_FUN(setWidthAuto, 0, {
            YGNodeStyleSetWidthAuto(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setWidthPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetWidthAuto(node), YGNodeStyleSetWidthPercent(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMaxWidth, 1, {
            ON_VALUE_PERCENT_UND_NUM(
                arguments[0],
                YGNodeStyleSetMaxWidthPercent(node, percentage),
                YGNodeStyleSetMaxWidth(node, YGUndefined),
                YGNodeStyleSetMaxWidth(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMaxWidthPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetMaxWidthPercent(node, YGUndefined), YGNodeStyleSetMaxWidthPercent(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMinWidth, 1, {
            ON_VALUE_PERCENT_UND_NUM(
                arguments[0],
                YGNodeStyleSetMinWidthPercent(node, percentage),
                YGNodeStyleSetMinWidth(node, YGUndefined),
                YGNodeStyleSetMinWidth(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMinWidthPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetMinWidthPercent(node, YGUndefined), YGNodeStyleSetMinWidthPercent(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(getWidth, 0, {
            SET_YGVALUE(YGNodeStyleGetWidth(node));
        })

        INSTALL_HOST_FUN(getMaxWidth, 0, {
            SET_YGVALUE(YGNodeStyleGetMaxWidth(node));
        })

        INSTALL_HOST_FUN(getMinWidth, 0, {
            SET_YGVALUE(YGNodeStyleGetMinWidth(node));
        })

        INSTALL_HOST_FUN(getComputedWidth, 0, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetWidth(node));
        })

        INSTALL_HOST_FUN(setHeight, 1, {
            SET_AUTO_PERCENT_NUMBER(YGNodeStyleSetHeightAuto, YGNodeStyleSetHeightPercent, YGNodeStyleSetHeight);
        });

        INSTALL_HOST_FUN(setHeightAuto, 0, {
            YGNodeStyleSetHeightAuto(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setHeightPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetHeightPercent(node, YGUndefined), YGNodeStyleSetHeightPercent(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMaxHeight, 1, {
            ON_VALUE_PERCENT_UND_NUM(
                arguments[0],
                YGNodeStyleSetMaxHeightPercent(node, percentage),
                YGNodeStyleSetMaxHeight(node, YGUndefined),
                YGNodeStyleSetMaxHeight(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMaxHeightPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetMaxHeightPercent(node, YGUndefined), YGNodeStyleSetMaxHeightPercent(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMinHeight, 1, {
            ON_VALUE_PERCENT_UND_NUM(
                arguments[0],
                YGNodeStyleSetMinHeightPercent(node, percentage),
                YGNodeStyleSetMinHeight(node, YGUndefined),
                YGNodeStyleSetMinHeight(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(setMinHeightPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetMinHeightPercent(node, YGUndefined), YGNodeStyleSetMinHeightPercent(node, arguments[0].getNumber()));
        })

        INSTALL_HOST_FUN(getHeight, 0, {
            SET_YGVALUE(YGNodeStyleGetHeight(node));
        })

        INSTALL_HOST_FUN(getComputedHeight, 0, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetHeight(node));
        })

        INSTALL_HOST_FUN(getMaxHeight, 0, {
            SET_YGVALUE(YGNodeStyleGetMaxHeight(node));
        })

        INSTALL_HOST_FUN(getMinHeight, 0, {
            SET_YGVALUE(YGNodeStyleGetMinHeight(node));
        })

        INSTALL_HOST_FUN(setPadding, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_VALUE_PERCENT_UND_NUM(
                arguments[1],
                YGNodeStyleSetPaddingPercent(node, edge, percentage),
                YGNodeStyleSetPadding(node, edge, YGUndefined),
                YGNodeStyleSetPadding(node, edge, arguments[1].getNumber()));
        })

        INSTALL_HOST_FUN(setPaddingPercent, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_NUM_UNDEFINED(arguments[1], YGNodeStyleSetPaddingPercent(node, edge, YGUndefined), YGNodeStyleSetPaddingPercent(node, edge, arguments[1].getNumber()));
        })

        INSTALL_HOST_FUN(getPadding, 1, {
            SET_YGVALUE(YGNodeStyleGetPadding(node, YGEdge(arguments[0].getNumber())));
        })

        INSTALL_HOST_FUN(getComputedPadding, 1, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetPadding(node, YGEdge(arguments[0].getNumber())));
        })

        INSTALL_HOST_FUN(setMargin, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_VALUE_AUTO_PERCENT_UND_NUM(
                arguments[1],
                YGNodeStyleSetMarginAuto(node, edge),
                YGNodeStyleSetMarginPercent(node, edge, percentage),
                YGNodeStyleSetMargin(node, edge, YGUndefined),
                YGNodeStyleSetMargin(node, edge, arguments[1].getNumber()));
        })

        INSTALL_HOST_FUN(setMarginAuto, 1, {
            auto edge = YGEdge(arguments[0].getNumber());
            YGNodeStyleSetMarginAuto(node, edge);
            return Value::undefined();
        })

        INSTALL_HOST_FUN(setMarginPercent, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_NUM_UNDEFINED(arguments[1], YGNodeStyleSetMarginPercent(node, edge, arguments[1].getNumber()), YGNodeStyleSetMarginPercent(node, edge, YGUndefined));
        })

        INSTALL_HOST_FUN(setPosition, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_VALUE_PERCENT_UND_NUM(
                arguments[1],
                YGNodeStyleSetPositionPercent(node, edge, percentage),
                YGNodeStyleSetPosition(node, edge, YGUndefined),
                YGNodeStyleSetPosition(node, edge, arguments[1].getNumber()));
        })

        INSTALL_HOST_FUN(setPositionPercent, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_NUM_UNDEFINED(arguments[1], YGNodeStyleSetPositionPercent(node, edge, YGUndefined), YGNodeStyleSetPositionPercent(node, edge, arguments[1].getNumber()));
        })

        INSTALL_HOST_FUN(getMargin, 1, {
            SET_YGVALUE(YGNodeStyleGetMargin(node, YGEdge(arguments[0].getNumber())));
        })

        INSTALL_HOST_FUN(getComputedMargin, 1, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetMargin(node, YGEdge(arguments[0].getNumber())));
        })

        INSTALL_HOST_FUN(setPositionType, 1, {
            YGNodeStyleSetPositionType(node, static_cast<YGPositionType>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getPosition, 1, {
            SET_YGVALUE(YGNodeStyleGetPosition(node, YGEdge(arguments[0].getNumber())));
        });

        INSTALL_HOST_FUN(getPositionType, 0, {
            return Value(static_cast<double>(YGNodeStyleGetPositionType(node)));
        });

        INSTALL_HOST_FUN(setDisplay, 1, {
            YGNodeStyleSetDisplay(node, static_cast<YGDisplay>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getDisplay, 0, {
            return Value(static_cast<double>(YGNodeStyleGetDisplay(node)));
        });

        INSTALL_HOST_FUN(setFlex, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetFlex(node, arguments[0].getNumber()), YGNodeStyleSetFlex(node, YGUndefined));
        });

        INSTALL_HOST_FUN(setFlexGrow, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetFlexGrow(node, YGUndefined), YGNodeStyleSetFlexGrow(node, arguments[0].getNumber()));
        });

        INSTALL_HOST_FUN(setFlexShrink, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetFlexShrink(node, arguments[0].getNumber()), YGNodeStyleSetFlexShrink(node, YGUndefined));
        });

        INSTALL_HOST_FUN(setFlexBasis, 1, {
            SET_AUTO_PERCENT_NUMBER(YGNodeStyleSetFlexBasisAuto, YGNodeStyleSetFlexBasisPercent, YGNodeStyleSetFlexBasis);
        });

        INSTALL_HOST_FUN(setFlexBasisAuto, 0, {
            YGNodeStyleSetFlexBasisAuto(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setFlexBasisPercent, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetFlexBasisPercent(node, YGUndefined), YGNodeStyleSetFlexBasisPercent(node, arguments[0].getNumber()));
        });

        INSTALL_HOST_FUN(setFlexDirection, 1, {
            YGNodeStyleSetFlexDirection(node, static_cast<YGFlexDirection>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setFlexWrap, 1, {
            YGNodeStyleSetFlexWrap(node, static_cast<YGWrap>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getFlexBasis, 0, {
            SET_YGVALUE(YGNodeStyleGetFlexBasis(node));
        });

        INSTALL_HOST_FUN(getFlexDirection, 0, {
            return Value(static_cast<double>(YGNodeStyleGetFlexDirection(node)));
        });

        INSTALL_HOST_FUN(getFlexGrow, 0, {
            RETURN_AS_DOUBLE(YGNodeStyleGetFlexGrow(node));
        });

        INSTALL_HOST_FUN(getFlex, 0, {
            RETURN_AS_DOUBLE(YGNodeStyleGetFlex(node));
        });

        INSTALL_HOST_FUN(getFlexShrink, 0, {
            RETURN_AS_DOUBLE(YGNodeStyleGetFlexShrink(node));
        });

        INSTALL_HOST_FUN(getFlexWrap, 0, {
            return Value(static_cast<double>(YGNodeStyleGetFlexWrap(node)));
        });

        INSTALL_HOST_FUN(setDirection, 1, {
            YGNodeStyleSetDirection(node, static_cast<YGDirection>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getDirection, 0, {
            return Value(static_cast<double>(YGNodeStyleGetDirection(node)));
        });

        INSTALL_HOST_FUN(setBorder, 2, {
            auto edge = YGEdge(arguments[0].getNumber());
            ON_NUM_UNDEFINED(arguments[1], YGNodeStyleSetBorder(node, edge, arguments[1].getNumber()), YGNodeStyleSetBorder(node, edge, YGUndefined));
        });

        INSTALL_HOST_FUN(getBorder, 1, {
            RETURN_AS_DOUBLE(YGNodeStyleGetBorder(node, YGEdge(arguments[0].getNumber())));
        });

        INSTALL_HOST_FUN(getComputedBorder, 1, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetBorder(node, YGEdge(arguments[0].getNumber())));
        });

        INSTALL_HOST_FUN(getComputedLayout, 0, {
            auto valueObject = Object(runtime);
            valueObject.setProperty(runtime, "left", YGNodeLayoutGetLeft(node));
            valueObject.setProperty(runtime, "right", YGNodeLayoutGetRight(node));
            valueObject.setProperty(runtime, "top", YGNodeLayoutGetTop(node));
            valueObject.setProperty(runtime, "bottom", YGNodeLayoutGetBottom(node));
            valueObject.setProperty(runtime, "width", YGNodeLayoutGetWidth(node));
            valueObject.setProperty(runtime, "height", YGNodeLayoutGetHeight(node));
            return valueObject;
        });

        INSTALL_HOST_FUN(getLayoutInRoot, 0, {
            auto getLeftInRoot = [](YGNodeRef node) -> float
            {
                float left = 0.0f;
                YGNodeRef current = node;
                while (current != nullptr)
                {
                    left += YGNodeLayoutGetLeft(current);
                    current = YGNodeGetParent(current);
                }
                return left;
            };

            auto getTopInRoot = [](YGNodeRef node) -> float
            {
                float top = 0.0f;
                YGNodeRef current = node;
                while (current != nullptr)
                {
                    top += YGNodeLayoutGetTop(current);
                    current = YGNodeGetParent(current);
                }
                return top;
            };

            auto valueObject = Object(runtime);

            float absoluteTop = getTopInRoot(node);
            float absoluteLeft = getLeftInRoot(node);

            valueObject.setProperty(runtime, "top", absoluteTop);
            valueObject.setProperty(runtime, "left", absoluteLeft);
            valueObject.setProperty(runtime, "width", YGNodeLayoutGetWidth(node));
            valueObject.setProperty(runtime, "height", YGNodeLayoutGetHeight(node));

            return valueObject;
        });

        INSTALL_HOST_FUN(getComputedLeft, 0, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetLeft(node));
        });

        INSTALL_HOST_FUN(getComputedRight, 0, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetRight(node));
        });

        INSTALL_HOST_FUN(getComputedTop, 0, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetTop(node));
        });

        INSTALL_HOST_FUN(getComputedBottom, 0, {
            RETURN_AS_DOUBLE(YGNodeLayoutGetBottom(node));
        });

        INSTALL_HOST_FUN(calculateLayout, 3, {
            auto ownerWidth = YGUndefined;
            auto ownerHeight = YGUndefined;
            auto direction = YGDirection::YGDirectionInherit;
            if (count > 0 && arguments[0].isNumber())
                ownerWidth = arguments[0].getNumber();

            if (count > 1 && arguments[1].isNumber())
                ownerHeight = arguments[1].getNumber();

            if (count == 3 && arguments[2].isNumber())
                direction = static_cast<YGDirection>(arguments[2].getNumber());

            YGNodeCalculateLayout(node, ownerWidth, ownerHeight, direction);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setAlignItems, 1, {
            YGNodeStyleSetAlignItems(node, static_cast<YGAlign>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setAlignSelf, 1, {
            YGNodeStyleSetAlignSelf(node, static_cast<YGAlign>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(setAlignContent, 1, {
            YGNodeStyleSetAlignContent(node, static_cast<YGAlign>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getAlignItems, 0, {
            return Value(static_cast<double>(YGNodeStyleGetAlignItems(node)));
        });

        INSTALL_HOST_FUN(getAlignSelf, 0, {
            return Value(static_cast<double>(YGNodeStyleGetAlignSelf(node)));
        });

        INSTALL_HOST_FUN(getAlignContent, 0, {
            return Value(static_cast<double>(YGNodeStyleGetAlignContent(node)));
        });

        INSTALL_HOST_FUN(setJustifyContent, 1, {
            YGNodeStyleSetJustifyContent(node, static_cast<YGJustify>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getJustifyContent, 0, {
            return Value(static_cast<double>(YGNodeStyleGetJustifyContent(node)));
        });

        INSTALL_HOST_FUN(setOverflow, 1, {
            YGNodeStyleSetOverflow(node, static_cast<YGOverflow>(arguments[0].getNumber()));
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getOverflow, 0, {
            return Value(static_cast<double>(YGNodeStyleGetOverflow(node)));
        });

        INSTALL_HOST_FUN(setAspectRatio, 1, {
            ON_NUM_UNDEFINED(arguments[0], YGNodeStyleSetAspectRatio(node, arguments[0].getNumber()), YGNodeStyleSetAspectRatio(node, YGUndefined));
        });

        INSTALL_HOST_FUN(getAspectRatio, 0, {
            RETURN_AS_DOUBLE(YGNodeStyleGetAspectRatio(node));
        });

        INSTALL_HOST_FUN(free, 0, {
            YGNodeFree(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(freeRecursive, 0, {
            YGNodeFreeRecursive(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(isDirty, 0, {
            return Value(YGNodeIsDirty(node));
        });

        INSTALL_HOST_FUN(markDirty, 0, {
            YGNodeMarkDirty(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(reset, 0, {
            YGNodeReset(node);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(markLayoutSeen, 0, {
            YGNodeSetHasNewLayout(node, false);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(copyStyle, 1, {
            READ_NODE(arguments[0].asObject(runtime));
            YGNodeCopyStyle(node, nodeFromRt);

            return Value::undefined();
        });

        INSTALL_HOST_FUN(getChildCount, 0, {
            RETURN_AS_DOUBLE(YGNodeGetChildCount(node));
        });

        INSTALL_HOST_FUN(insertChild, 2, {
            auto index = arguments[1].getNumber();
            READ_NODE(arguments[0].asObject(runtime));
            YGNodeInsertChild(node, nodeFromRt, index);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getChild, 1, {
            auto index = arguments[0].getNumber();
            auto childNode = YGNodeGetChild(node, index);
            auto childNodeObj = Object(runtime);
            set(childNodeObj, runtime, childNode);
            return childNodeObj;
        });

        INSTALL_HOST_FUN(removeChild, 1, {
            READ_NODE(arguments[0].asObject(runtime));
            YGNodeRemoveChild(node, nodeFromRt);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getParent, 0, {
            auto parentNode = YGNodeGetParent(node);
            if (!parentNode)
                return Value::null();
            auto parentNodeObj = Object(runtime);
            set(parentNodeObj, runtime, parentNode);
            return parentNodeObj;
        });

        // INSTALL_HOST_FUN(getOwner, 0, {
        //     auto ownerNode = YGNodeGetOwner(node);
        //     if (!ownerNode)
        //         return Value::null();
        //     auto ownerNodeObj = Object(runtime);
        //     setNodeNodee(ownerNodeObj, runtime, ownerNode);
        //     return ownerNodeObj;
        // });

        INSTALL_HOST_FUN(isReferenceBaseline, 0, {
            return Value(YGNodeIsReferenceBaseline(node));
        });

        INSTALL_HOST_FUN(setIsReferenceBaseline, 1, {
            YGNodeSetIsReferenceBaseline(node, arguments[0].getBool());
            return Value::undefined();
        });

        INSTALL_HOST_FUN(hasNewLayout, 0, {
            return Value(YGNodeGetHasNewLayout(node));
        });

        INSTALL_HOST_FUN(unsetDirtiedFunc, 0, {
            YGNodeSetDirtiedFunc(node, nullptr);
            return Value::undefined();
        });

        INSTALL_HOST_FUN(unsetMeasureFunc, 0, {
            YGNodeSetMeasureFunc(node, nullptr);
            return Value::undefined();
        });

        // #ifdef YGNodeStyleSetGap
        INSTALL_HOST_FUN(setGap, 2, {
            YGNodeStyleSetGap(node, static_cast<YGGutter>(arguments[0].getNumber()), arguments[1].getNumber());
            return Value::undefined();
        });

        INSTALL_HOST_FUN(getGap, 1, {
            auto gap = YGNodeStyleGetGap(node, static_cast<YGGutter>(arguments[0].getNumber()));
            SET_YGVALUE(gap);
        });

        INSTALL_HOST_FUN(setDirtiedFunc, 1, {
            auto dirtiedFunc = std::make_shared<Function>(arguments[0].asObject(runtime).asFunction(runtime));

            YGNodeSetDirtiedFunc(node, [](YGNodeConstRef node)
                                 {
            auto *context = static_cast<std::pair<std::shared_ptr<Function>, Runtime*> *>(YGNodeGetContext(node));
            if (!context)
            {
                return;
            }

            auto &dirtiedFunc = context->first;
            auto *runtime = context->second;
            if (dirtiedFunc && runtime)
            {
                dirtiedFunc->call(*runtime);
            } });

            YGNodeSetContext(node, new std::pair<std::shared_ptr<Function>, Runtime *>(dirtiedFunc, &runtime));
            return Value::undefined();
        })

        INSTALL_HOST_FUN(setMeasureFunc, 1, {
            auto measureFunc = std::make_shared<Function>(arguments[0].asObject(runtime).asFunction(runtime));

            YGNodeSetMeasureFunc(node, [](YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode) -> YGSize
                                 {
                        auto *context = static_cast<std::pair<std::shared_ptr<Function>, Runtime*> *>(YGNodeGetContext(node));
                        if (!context)
                        {   
                            return YGSize{width, height};
                        }

                        auto &measureFunc = context->first;
                        auto *runtime = context->second;

                        if (!measureFunc || !runtime)
                        {
                            return YGSize{width, height};
                        }

                        Value widthValue(static_cast<double>(width));
                        Value heightValue(static_cast<double>(height));
                        Value widthModeValue(static_cast<double>(widthMode));
                        Value heightModeValue(static_cast<double>(heightMode));

                        auto result = measureFunc->call(*runtime, widthValue, widthModeValue, heightValue, heightModeValue);

                        auto resultObj = result.asObject(*runtime);
                        float measuredWidth = resultObj.getProperty(*runtime, "width").asNumber();
                        float measuredHeight = resultObj.getProperty(*runtime, "height").asNumber();

                        return YGSize{measuredWidth, measuredHeight}; });

            YGNodeSetContext(node, new std::pair<std::shared_ptr<Function>, Runtime *>(measureFunc, &runtime));

            return Value::undefined();
        })

        std::uintptr_t nodePtr = reinterpret_cast<std::uintptr_t>(node);
        char buffer[20];
        std::snprintf(buffer, sizeof(buffer), "%lx", nodePtr);
        std::string nodeStr(buffer);
        nodeObject.setProperty(rt, "__node__", nodeStr);
    }
}

#endif // NODE_PROPERTIES_H
