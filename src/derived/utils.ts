import type { Node } from '../coreTypes';
import Yoga from '../index';
import { applyStyle, type NodeStyle } from './styleHandler';

export type NodeTree<T extends string> = {
  key: T;
  style?: NodeStyle;
  children?: NodeTree<T>[];
};

export type NodeTreeKeys<T> = T extends NodeTree<infer K> ? K : never;

export function createLayout<T extends string>(styles: NodeTree<T>) {
  return styles;
}

type TreeItem<T extends string> = NodeTree<T> | NodeTree<T>[];

function Layout<T extends string>(rootKey: T){
  'worklet';
  const config = Yoga.Config.create();
  config.setPointScaleFactor(0);
  const root = Yoga.Node.create(config);
  const layout = {
    [rootKey]: root,
  } as Record<T, Node>;
  return {
    layout,
    rootKey,
    getNode: (key: T) => {
      'worklet';
      return layout[key];
    },
    addNodeTo: (parentKey: T, key: T, index: number) => {
      'worklet';
      const parent = layout[parentKey];
      const child = Yoga.Node.create();
      parent.insertChild(child, index);
      layout[key] = child;
      return child;
    },
    free: () => {
      'worklet';
      root.freeRecursive();
    },
    forEach: (cb: (node: Node, key: T) => void) => {
      'worklet';
      for (const key in layout) {
        cb(layout[key], key);
      }
    },
  };
}

export function generateStyledLayout<T extends string>(layout: NodeTree<T>) {
  'worklet';
  const layoutTree = Layout(layout.key);
  applyStyle(layoutTree.layout[layout.key], layout.style);
  function _parse<U extends T>(
    treeItem: TreeItem<U>,
    index: number,
    isArray: boolean,
    parentKey: U | null
  ) {
    'worklet';
    if (isArray) {
      (treeItem as NodeTree<U>[]).forEach((o, i) => {
        _parse(o, i, false, parentKey);
      });
    } else {
      treeItem = treeItem as NodeTree<U>;
      if (parentKey !== null) {
        const addedNode = layoutTree.addNodeTo(parentKey, treeItem.key, index);
        applyStyle(addedNode, treeItem.style);
      }
      if (treeItem.children) {
        _parse(treeItem.children, 0, true, treeItem.key);
      }
    }
  
    return layoutTree;
  }
  
  _parse(layout, 0, false, null);

  return layoutTree;
}
